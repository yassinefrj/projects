<?php

namespace App\Http\Controllers;

use App\Models\File;
use App\Http\Requests\StoreFileRequest;
use App\Http\Requests\UpdateFileRequest;
use App\Models\Contact;
use App\Models\User;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Input;
use Illuminate\Support\Facades\Session;
use Illuminate\Support\Facades\Storage;
use Illuminate\Support\Str;
use Brainstud\FileVault\Facades\FileVault;
use Illuminate\Support\Facades\Crypt;
use phpseclib\Net\SFTP;


class FileController extends Controller
{
    public function __construct()
    {
        return $this->middleware(['auth']); //un user pas connecté ne peut pas accéder aux fonctions liées au folder.
    }

    /**
     * Display the list of files.
     * This method retrieves and displays the list of files based on the search query and file type filters.
     * It performs various checks based on the user's role to determine the files that can be accessed.
     * @param \Illuminate\Http\Request $request
     *     The HTTP request object containing the search query and file type filters.
     * @return \Illuminate\Contracts\View\View|\Illuminate\Http\RedirectResponse
     *     Returns a view to display the list of files or redirects to another page with an error message.
     */
    public function index(Request $request)
    {
        $user = auth()->user();
        /**
         * Admin has no access to any medical record
         */
        if ($user->isAdmin) {
            return redirect('/users')->with('error', "acces denied");
        }
        
        $files = File::with(['owner'])->latest(); //return tous les fichiers dans l'ordre décroissant en fonction de la date 

        $files->select('files.*')->distinct();

        $search = $request->input('search');
        $filetype = $request->input('filetype');

        if (!empty($filetype)) {
            if ($filetype == 'others') {
                //on filtre en fonction de ce que l'user veut
                $files->where(function ($q) {
                    $q->where('file_type', 'NOT LIKE', "%application/pdf%")
                        ->where('file_type', 'NOT LIKE', "%image%")
                        ->where('file_type', 'NOT LIKE', "%video%")
                        ->where('file_type', 'NOT LIKE', "%audio%")
                        ->where('file_type', 'NOT LIKE', "%text%")
                        ->where('file_type', 'NOT LIKE', "%application/vnd.openxmlformats%");
                });
            } else {
                $files->where(function ($q) use ($filetype) {
                    $q->where('file_type', 'LIKE', "%$filetype%");
                });
            }
        }
        //recherche 
        if (!empty($search)) {
            $files->where(function ($query) use ($search) {
                $query->where('title', 'LIKE', "%$search%");
            });
        }

        //au niveau des permissions : on ne peut voir que les fichiers qui nous appartiennent ou partagés avec nous
        if (!$user->isAdmin) {
            $files->where(function ($query) use ($user) {
                $query->orWhere(function ($q) use ($user) {
                    $q->where('file_owner', '=', $user->id);
                });

                $query->orWhere(function ($q) use ($user) {
                    $q->whereRaw(' CONCAT(",",shared_with,",") like "%,' . $user->email . ',%" ');
                });
            });
        }

        $files = $files->get();
        $typesearch = 1;
        return view('files.index', compact('files', 'filetype', 'typesearch', 'search'));
    }

    /**
     * Display the user's files.
     * This method retrieves and displays the files owned by the authenticated user.
     * It fetches the files and renders the view to display the user's files.
     * @return \Illuminate\Contracts\View\View
     *     Returns a view to display the user's files.
     */
    public function myfiles()
    {
        $user = auth()->user();
        $files = File::with(['owner'])->latest();
        $files->select('files.*')->distinct();

        $files->where(function ($q) use ($user) {
            $q->where('file_owner', '=', $user->id);
        });
        $files = $files->get();
        return view('files.myfiles', compact('files'));
    }


    /**
     * Display the file creation form.
     * This method retrieves the contacts of the authenticated user with an active status (1)
     * and renders the file creation form view. The contacts are used to populate the list of recipients
     * for the file being created.
     * @return \Illuminate\Contracts\View\View
     *     Returns a view to display the file creation form.
     */
    public function create()
    {
        $user = auth()->user();
        //$users = User::where('status', 1)->get();
        //$shared_users = User::select('email', 'name')->where('status', 1)->get()->toArray();
        //$files = File::with(['owner'])->latest(); //return tous les fichiers dans l'ordre decroissant en fonction de la date 
        //$files->select('files.*')->distinct();
        $contacts = Contact::with(['requester', 'receiver'])->where(function ($q) {
            $q->where('status', '=', 1);
        });
        $contacts->where(function ($query) use ($user) {
            $query->orWhere(function ($q) use ($user) {
                $q->where('receiver_id', '=', $user->id)
                    ->orWhere('requester_id', '=', $user->id);
            });
        });
        $contacts = $contacts->get();

        return view('files.create', compact('contacts'));
    }

    /**
     * Create a symmetric key.
     * This private method generates a symmetric key . It creates the key file
     * and stores it in the specified user folder path. The generated key is a 256-bit AES key.
     * @param  string  $filename
     *     The filename associated with the key.
     * @return 
     *     Returns the generated symmetric key.
     */
    private function createSymmetricKey($filename)
    {
        info("DEBUG - createSymmetricKey");
        // Génération de la clé symétrique côté serveur (Laravel)
        // $keyFilePath = 'C:/Users/HP/.ssh/symmetric_key_' . $filename . '.txt'; // Chemin du fichier de clé
        $userFolderPath = config('app.path_to_key');
        $keyFilePath = $userFolderPath . 'symmetric_key_' . $filename; // Chemin du fichier de clé

        // Génération de la clé symétrique
        $command = 'openssl rand -hex 32 > ' . $keyFilePath; // Génère une clé AES 256 bits
        exec($command);

        $symmetricKey = file_get_contents($keyFilePath);

        // info("DEBUG - createSymmetricKey  - v2 $key");

        return $symmetricKey;
    }



    private function cipherWithSymmetricKey(Request $request, $key, $iv)
    {
        $file = $request->file('name');

        if ($file) {
            info("DEBUG - cipherWithSymmetricKey - OK");
            $fileContents = file_get_contents($file->path()); // get the content file
            info("DEBUG - cipherWithSymmetricKey - contenu = $fileContents");

            $encryptedContent = openssl_encrypt($fileContents, 'AES-256-CBC', $key, OPENSSL_RAW_DATA, $iv); // Chiffrement du contenu du fichier avec cle symmetrique

            info("DEBUG - cipherWithSymmetricKey - encryptedContent = $encryptedContent");
            return $encryptedContent;

            // Utilisez le contenu du fichier selon vos besoins
        } else {
            // Gérer le cas où aucun fichier n'est présent dans la requête
            // send execption
        }
    }

    /**
     * Sign a file using a private key.
     * This function takes the provided data and signs it using the given private key. The data is signed
     * using the SHA256 algorithm. The resulting signature is then encoded in base64 format before being returned.
     * @param  string  $data
     *     The data to be signed.
     * @param  resource|string  $privateKey
     *     The private key used for signing. This can be either a resource handle or the path to the private key file
     * @return string
     *     Returns the base64-encoded signature.
     */
    function signFile($data, $privateKey) {
        // Signer les données avec la clé privée
        openssl_sign($data, $signature, $privateKey, OPENSSL_ALGO_SHA256);
    
        // Retourner la signature encodée en base64
        return base64_encode($signature);
    }

    /**
     * Verify the signature of a file using a public key.
     * This function takes the provided data, the signature (in base64 format), and the public key and verifies
     * the integrity of the data using the public key. The signature is first decoded from base64. Then, the data
     * is verified against the signature using the SHA256 algorithm and the specified public key. The function
     * returns a boolean value indicating whether the signature is valid (true) or not (false).
     * @param  string  $data
     *     The data to be verified.
     * @param  string  $signature
     *     The signature to be verified, encoded in base64 format.
     * @param  resource|string  $publicKey
     *     The public key used for verification. This can be either a resource handle or the path to the public key file.
     * @return bool
     *     Returns true if the signature is valid, false otherwise.
     */
    function verifySignature($data, $signature, $publicKey) {
    
        // Décoder la signature à partir de base64
        $signature = base64_decode($signature);
    
        // Vérifier la signature avec la clé publique
        $isValid = openssl_verify($data, $signature, $publicKey, OPENSSL_ALGO_SHA256);
    
        // Retourner le résultat de la vérification
        return $isValid === 1;
    }

    /**
     * The store method implements security measures, including file information validation,
     *  extension verification, AES-256-CBC encryption of files, secure key management, and digital
     *  signature. These measures ensure the confidentiality, integrity, and protection against
     *  malicious attacks of uploaded files in the application
     *
     * @param  \Illuminate\Http\Request  $request
     *     The request object containing the uploaded file and form data.
     *
     * @return \Illuminate\Http\RedirectResponse
     *     Redirects the user to the files index page with a success message if the file upload is successful.
     *     Otherwise, redirects back to the upload form with an error message.
     */
    public function store(Request $request)
    {

        info("DEBUG - Store");
        //1. get the user from the session
        $user = auth()->user();

        //2. check file given informations
        $this->validate($request, [
            'title' => 'required|string|max:255',
            'name' => 'required|max:50000', //c'est le file
        ]);
        info("DEBUG - Store - title & name OK");

        // 3. begin db transaction in case of error
        DB::beginTransaction();
        // 4. make filePath public
        $filePath = "";
        try {
            // 5. get the user id
            $user_id = $user->id;
            // 6. handle file upload
            if ($request->hasFile('name')) {
                // 7. get the file from the temporaly location
                info("DEBUG - Store - tmp = " . $request->file('name'));

                // 8. Get the file WITH EXTENSTION name to get the file WITHOUT EXTENSION NAME
                $fileNameWithExt = $request->file('name')->hashName();
                info("DEBUG - Store - fileNameWithExt =  " . $fileNameWithExt);
                // 9. Get the file WITHOUT EXTENSTION name
                $filename = pathinfo($fileNameWithExt, PATHINFO_FILENAME);
                info("DEBUG - Store - hash name =  " . $filename);

                //10. Get the file EXTENSION
                $extension = $request->file('name')->extension();
                info("DEBUG - Store - extension =  " . $extension);

                // 11. delete malicious file
                if (in_array($extension, ['php', 'js', 'c', 'cpp', 'py', 'exe', 'bat', 'dll', 'sh', 'jar', 'vbs', 'cmd', 'ps1', 'vb', 'reg', 'asm', 'cgi', 'pl', 'phar', 'hta', 'pif', 'scr', 'com', 'vbe', 'vbscript', 'wsf', 'app', 'ade', 'adp', 'bas', 'chm', 'class', 'cpl', 'crt', 'hlp', 'inf', 'ins', 'isp', 'jse', 'lnk', 'mdb', 'mde', 'msc', 'msi', 'msp', 'mst', 'ocx', 'pcd', 'pif', 'prg', 'sct', 'shb', 'sys', 'url', 'wsc', 'wsf', 'wsh'])) {
                    return redirect()->back()->withErrors('Something went wrong : could not upload file (extension is not ok )!');
                }

                // 12. generate a unique id of 128 bits and assign it to the FILE NAME

                $fileNameToStore = Str::uuid();
                info("DEBUG - Store - filenameToStore =  " . $fileNameToStore);

                // 13. make the file name more unique by using the current time
                $fileNameToStore = $filename . '_' . time() . '.' . $extension;
                $filename = $fileNameToStore;

                // 14. creation of symmetric key
                $symmetricKey = FileController::createSymmetricKey($filename);

                // 15. generation of a random IV for the file encryption
                $iv = random_bytes(16); // Génération du vecteur d'initialisation (IV)


                // 16. cipher the file with the symmetric key from his temporaly place

                $encryptedFile = openssl_encrypt($request->file('name')->getContent(), 'AES-256-CBC', $symmetricKey, OPENSSL_RAW_DATA, $iv);
                // info("DEBUG - request->file('name')->getContent() = " . $request->file('name')->getContent());
                info("DEBUG - encryptedFile = $encryptedFile");

                // 17. save the ciphered file

                info("DEBUG - Store - Storage sftp end");

                if (Storage::disk('sftp_' . $user->name)->put($fileNameToStore, $encryptedFile)) {
                    info("V. absil La sauvegarde a été effectuée avec succès.");
                } else {
                    info("V. absil La sauvegarde a échoué.");
                }

                // 18. save the iv
                $ivFileName = $filename . '_iv';
                if (Storage::disk('sftp_' . $user->name)->put($ivFileName, $iv)) {
                    // Le fichier a été sauvegardé avec succès sur le disque SFTP
                    info("V. absil iv save");
                } else {
                    // La sauvegarde a échoué
                    info("V. absil iv NOT save");
                }

                // 19. get the public key of the current user for symmetric key encryption
                $userPublicKey = $user->public_key;
                //ensuite stocke la cle public en db

                // 20. cipher the symmetric key with the user public key
                openssl_public_encrypt($symmetricKey, $encryptedSymmetricKey, $userPublicKey);

                // 21. save the ciphered symmetric key
                $symmetricKeyFileName = $filename . ' _symmetric_key_' . $user->name;

                if (Storage::disk('sftp_' . $user->name)->put($symmetricKeyFileName, $encryptedSymmetricKey)) {
                    // Le fichier a été sauvegardé avec succès sur le disque SFTP
                    info("V. absil symmetricKey save");
                } else {
                    // La sauvegarde a échoué
                    info("V. absil symmetricKey NOT save");
                }

                // 22. hash the original content
                $hash = hash('sha256', $request->file('name')->getContent());

                // 23. save the hash
                $hashFileName = $filename . '_hash';

                if (Storage::disk('sftp_' . $user->name)->put($hashFileName, $hash)) {
                    // Le fichier a été sauvegardé avec succès sur le disque SFTP
                    info("V. us symmetricKey save");
                } else {
                    // La sauvegarde a échoué
                    info("V. us symmetricKey NOT save");
                }

                // 24. sign the hash
                $privateKey = file_get_contents($user->private_key_path);
                $sign = FileController::signFile($hash,$privateKey);
                info("DEBUG - Store - sign =  " . $sign);

                // 23. save the signature of the hash

                $signFileName = $filename . '_sign';

                info("DEBUG - Store - signFileName =  " . $signFileName);

                if (Storage::disk('sftp_' . $user->name)->put($signFileName, $sign)) {
                    // Le fichier a été sauvegardé avec succès sur le disque SFTP
                    info("V. us signed hash save");
                } else {
                    // La sauvegarde a échoué
                    info("V. us signed hash NOT save");
                }


                // info("DEBUG - Store - fileNameToStore =  " . $fileNameToStore);
                $fileType = $request->file('name')->getClientMimeType();
                info("DEBUG - Store - fileType =  " . $fileType);
            }

            info("DEBUG - Store - Part 2");
            $file = new File;
            $file->title = $request->input('title');
            $file->file_owner = $user_id;
            // $file->name = $path; v i
            $file->name = $filename;
            info("DEBUG - Store - Part 2 file->name = filename = $filename");

            $file->file_type = $fileType;
            $size = $request->file('name')->getSize();
            if ($size >= 1000000) {
                $file->file_size = round($size / 1000000) . 'MB';
            } elseif ($size >= 1000) {
                $file->file_size = round($size / 1000) . 'KB';
            } else {
                $file->file_size = $size;
            }

            $shared_with = null;
            if (!empty($request->input('shared_with')) && count($request->input('shared_with')) > 0) {
                foreach ($request->input('shared_with') as $mail) {
                    if (!empty($shared_with)) {
                        $shared_with = $shared_with . "," . $mail;
                    } else {
                        $shared_with = $mail;
                    }
                }
            }
            $file->shared_with = $shared_with;
            $file->reference = Str::uuid();

            // save to db
            info("DEBUG - Store - save to DB");
            $file->save();
            DB::commit();
            info("DEBUG - Store - save OK");
            return redirect('/files')->with('success', "File uploaded successfully!");
        } catch (\Exception $ex) {
            DB::rollback();
            $errorMessage = $ex->getMessage();
            info("DEBUG - STORE EXCEPTION $errorMessage");
            return redirect()->back()->withErrors('Something went wrong : could not upload file!');
        }
    }


    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Models\File  $file
     * @return \Illuminate\Http\Response
     */
    public function edit($reference)
    {
        //changer le nom du fichier
        //changer les droits

        $file = File::with('owner')->where('reference', '=', $reference)->first();
        $user = auth()->user();
        if ($file->file_owner != $user->id) {
            return redirect('/files')->with('error', "Access denied!");
        }

        $contacts = Contact::with(['requester', 'receiver'])->where(function ($q) {
            $q->where('status', '=', 1);
        });
        $contacts->where(function ($query) use ($user) {
            $query->orWhere(function ($q) use ($user) {
                $q->where('receiver_id', '=', $user->id)
                    ->orWhere('requester_id', '=', $user->id);
            });
        });
        $contacts = $contacts->get();
        return view('files.edit', compact('file', 'contacts'));
    }

    
    /**
     *  In the "download" function,
     *  the file is downloaded only if the user is the owner or has appropriate 
     * permissions. The downloaded file is decrypted using a symmetric key, and
     *  its integrity is verified using a hash and digital signature.
     * @param $reference represents a unique reference associated with a file
     * @return returns an HTTP response that allows you to download the contents of a
     *  file specified by its reference 
     * otherwise it returns an error if the security checks failed
     */
    public function download($reference)
    {
        //pour telecharger un fichier soit on est proprio ou on a des droits

        
        $user = auth()->user();
        $files = File::with(['owner'])->where('reference', '=', $reference)->latest(); //return tous les fichiers dans l'ordre decroissant en fonction de la date 
        $files->select('files.*')->distinct();

        //au niveau des permissions : on peut voir que les fichiers qui nous appartiennent ou soit partager avec nous
        if (!$user->isAdmin) {
            $files->where(function ($query) use ($user) {
                $query->orWhere(function ($q) use ($user) {
                    $q->where('file_owner', '=', $user->id);
                });

                $query->orWhere(function ($q) use ($user) {
                    $q->whereRaw(' CONCAT(",",shared_with,",") like "%,' . $user->email . ',%" ');
                });
            });
        }

        $files = $files->get();
        if (count($files) > 0) {
            $file = $files[0];
        } else {
            return redirect('/files')->with('error', 'Access denied!');
        }

        //1. get file name
        $filename2 = $file->name;
        info("DEBUG download filename2 = $filename2");

        //2. get file content
        $encryptedFile = Storage::disk('sftp_' . $user->name)->get($filename2); //download au niveau du code serveur-->dossier storage
        info("DEBUG download encryptedFile = $encryptedFile");
        //3. get iv
        $ivFileName = $filename2 . '_iv';
        $iv = Storage::disk('sftp_' . $user->name)->get($ivFileName);
        info("DEBUG download iv = $iv");
        //4. get the ciphered symmetric key
        $cipheredSymmetricKeyFileName = $filename2 . ' _symmetric_key_' . $user->name;
        $cipheredSymmetricKey = Storage::disk('sftp_' . $user->name)->get($cipheredSymmetricKeyFileName);
        info("DEBUG download cipheredSymmetricKey = $cipheredSymmetricKey");

        //5. get the private key (can be done only in local and need the password of the private key in a real context)
        $privateKey = file_get_contents($user->private_key_path);
        // info("DEBUG download privateKey = $privateKey");

        // 6. decrypt the ciphered symmetric key
        openssl_private_decrypt($cipheredSymmetricKey, $symmetricKey, $privateKey);
        info("DEBUG download symmetricKey = $symmetricKey");

        // 7. decrypt the file
        $decryptedContent = openssl_decrypt($encryptedFile, 'AES-256-CBC', $symmetricKey, OPENSSL_RAW_DATA, $iv);
        // info("DEBUG download decryptedContent = $decryptedContent");

        // 8. hash the decrypted file
        $hash = hash('sha256', $decryptedContent);

        // 9. get the hashed the original hashed file
        $hashFileName = $filename2 . '_hash';
        $originalHash =  Storage::disk('sftp_' . $user->name)->get($hashFileName);
        
        
        info("DEBUG download hash = $hash");
        info("DEBUG download originalHash = $originalHash");


        // 11. check the signature

        $signFileName = $filename2 . '_sign';
        $sign =  Storage::disk('sftp_' . $user->name)->get($signFileName);
        info("DEBUG download signature = $sign");


        $owner = User::where('id', $file->file_owner)->first();
        info("DEBUG download owner = " . $owner);

        info("DEBUG download owner->public_key = " . $owner->public_key);

        if (!FileController::verifySignature($originalHash,$sign,$owner->public_key)){
            return redirect('/files')->with('error', 'SIGNATURE MISMATCH !');
        }
        
        // 10. compare the hash
        if ($hash === $originalHash) {
            return response()->streamDownload(function () use ($filename2, $decryptedContent) {
                echo $decryptedContent;
            }, $filename2);
        } else {
            return redirect('/files')->with('error', 'CORRUPTED FILE !');
        }        
        
    }

    /**
     * Update the specified resource in storage.
     * 
     * The "update" method handles secure file updates by protecting the symmetric
     *  key used for file encryption. It uses encryption techniques to securely share
     *  the symmetric key with authorized users, ensuring the confidentiality and
     *  integrity of the encrypted files.
     *
     * @param  \App\Http\Requests\UpdateFileRequest  $request
     * @param  \App\Models\File  $file
     * @return \Illuminate\Http\Response returns a redirect to the "/files" page with a 
     * success message if the file update is successful. Otherwise, it returns
     *  a redirect to the previous page with an error message if the file update fails.
     */
    public function update(Request $request, $reference)
    {
        info("DEBUG update begin");
        $user = auth()->user();
        $file = File::where('reference', '=', $reference)->first();
        //checker si user est proprietaire du fichier
        if ($file->file_owner != $user->id) {
            return redirect('/files')->with('error', 'Access denied');
        }

        $this->validate($request, [
            'title' => 'required|string|max:255'
        ]);

        DB::beginTransaction();
        try {
            $file->title = $request->input('title');
            //1. recuperer la cle symmetrique qui a permis de chiffer le fichier

            $filename2 = $file->name;
            info("DEBUG update filename2 = $filename2");

            $cipheredSymmetricKeyFileName = $filename2 . ' _symmetric_key_' . $user->name;
            $cipheredSymmetricKey = Storage::disk('sftp_' . $user->name)->get($cipheredSymmetricKeyFileName);
            info("DEBUG update cipheredSymmetricKey = $cipheredSymmetricKey");

            //2. dechiffrer la cle symmetrique

            $privateKey = file_get_contents($user->private_key_path);
            openssl_private_decrypt($cipheredSymmetricKey, $symmetricKey, $privateKey);
            info("DEBUG update symmetricKey = $symmetricKey");

            // la
            $shared_with = null;
            if (!empty($request->input('shared_with')) && count($request->input('shared_with')) > 0) {
                info("DEBUG update 1er if ok");

                foreach ($request->input('shared_with') as $mail) {
                    info("DEBUG update foreach ok");

                    if (!empty($shared_with)) {
                        $shared_with = $shared_with . "," . $mail;
                    } else {
                        info("DEBUG else ok");
                        $shared_with = $mail;

                        info("DEBUG update mail = $mail");

                        //3. recuperer la cle public de la personne avec qui je partage
                        $friend = User::where('email', '=', $mail)->first();
                        info("DEBUG update friend = " . $friend->name);

                        $userPublicKey = $friend->public_key;

                        //4. chiffrer la cle symmetrique avec (3)
                        openssl_public_encrypt($symmetricKey, $encryptedSymmetricKey, $userPublicKey);

                        //5. sauvegarder la 2e cle symmetrique. CQFD
                        $symmetricKeyFileName = $filename2 . ' _symmetric_key_' . $friend->name;

                        if (Storage::disk('sftp_' . $user->name)->put($symmetricKeyFileName, $encryptedSymmetricKey)) {
                            // Le fichier a été sauvegardé avec succès sur le disque SFTP
                            info("DEBUG update V. absil symmetricKey save");
                        } else {
                            // La sauvegarde a échoué
                            info("DEBUG update V. absil symmetricKey NOT save");
                        }
                    }
                }
            }
            info("DEBUG update fin 1er if ok");

            $file->shared_with = $shared_with;
            // save to db
            $file->save();
            DB::commit();
            return redirect('/files')->with('success', 'File edited successfully!');
        } catch (\Exception $ex) {
            DB::rollback();
            return redirect()->back()->withErrors('Failed to edit the file.');
        }
    }

    /**
     * Securely deletes a file stored on the specified disk. 
     * This method follows a secure deletion process to ensure that the file's content 
     * cannot be recovered. It overwrites the file's content with random data, deletes 
     * the file from the disk, and securely deletes any traces of the file. 
     * @param diskName The name of the disk where the file is stored. 
     * @param filePath The path to the file that needs to be securely deleted.
     */
    function secureFileDeletion($diskName, $filePath)
{
    $disk = Storage::disk($diskName);
    
    // Récupérer le fichier chiffré
    $encryptedFile = $disk->get($filePath);
    
    // Effacer le contenu du fichier avec des données aléatoires
    $fileSize = $disk->size($filePath);
    $disk->put($filePath, random_bytes($fileSize));
    
    // Suppression du fichier
    $disk->delete($filePath);
    
    // Effacer le fichier chiffré du cache de stockage
    $disk->put($filePath, $encryptedFile);
    $disk->delete($filePath);
}


    /**
     * Deletes a file securely. 
     * This method securely deletes a file by performing the following steps: 
     * Verifies that the file belongs to the authenticated user. 
     * Retrieves the encrypted file from the storage. Performs a secure
     *  file deletion by overwriting the file's content with random data. 
     * Deletes the file from the storage and the database. 
     * @param reference The reference of the file to be deleted. 
     * @return Redirect response indicating the success or failure of the operation.
     */
    public function destroy($reference)
    {
        info("DEBUG - DESTROY");
        //verifier que le fichier appartient bien aux user
        $user = auth()->user();
        DB::beginTransaction();
        try {
            $file = File::where('reference', '=', $reference)->first();
            if ($file->file_owner == $user->id) {
                $encryptedFile = Storage::disk('sftp_' . $user->name)->get($file->name); //download au niveau du code serveur-->dossier storage
                FileController::secureFileDeletion('sftp_' . $user->name, $file->name);

                // Storage::disk('sftp_' . $user->name)->delete($file->name); //suppression au niveau du serveur
                $file->delete(); //suppression au niveau de la bd
                DB::commit();
                return redirect('/files')->with('success', 'File deleted successfully!');
            } else {
                return redirect('/files')->with('error', 'Access denied!');
            }
        } catch (\Exception $ex) {
            $errorMessage = $ex->getMessage();
            info("DEBUG - DESTROY EXCEPTION $errorMessage");
            DB::rollback();
            return redirect()->back()->with('error', 'Failed to delete file!');
        }
    }


    /**
     * allows multiple files to be deleted based on references provided in the HTTP
     * request. It performs deletion of files at the storage server and database
     * level, verifying that the current user is the owner of the files. It returns
     * a status indicating the success or failure of the operation, along with a 
     * corresponding message and redirect URL.
     * @param $request The HTTP request containing the references of the files to be deleted. 
     * @return An array with the status, message, and redirect URL indicating the success or failure of the operation.
     * 
     */
    public function deleteMulti(Request $request)
    {
        DB::beginTransaction();
        try {
            $references = $request->references;
            $files = File::whereIn('reference', explode(",", $references))->get();
            foreach ($files as $file) {
                if ($file->file_owner == auth()->user()->id) {
                    Storage::disk('sftp')->delete($file->name . '.enc'); //suppression au niveau du serveur
                    $file->delete(); //au niveau de db

                } else {
                    throw new \Exception('Failed to delete');
                }
            }
            DB::commit();
            return ['status' =>
            'success', 'message' => 'file deleted successfully', 'redirect_url' => '/files'];
        } catch (\Exception $ex) {
            DB::rollback();
            return ['status' => 'error', 'message' => 'Fail to delete file', 'redirect_url' => '/files'];
        }
    }


    /**
     * Flashes a message to the session. This method allows storing a temporary message in the session,
     *  typically for displaying feedback or notifications to the user. The message is associated
     * with a specific status, which can be used for styling or categorizing the message. 
     * @param Request $request The HTTP request object containing the status and message data.
     * @return array An array containing the status and message that were flashed to the session.
     */
    public function flash(Request $request)
    {
        Session::flash('message.' . $request->input('status'), $request->input('message'));
        return ['status' => $request->input('status'), 'message' => $request->input('message')];
    }
}
