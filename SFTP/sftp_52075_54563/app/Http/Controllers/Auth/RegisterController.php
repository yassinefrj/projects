<?php

namespace App\Http\Controllers\Auth;

use App\Http\Controllers\Controller;
use App\Providers\RouteServiceProvider;
use App\Models\User;
use Illuminate\Foundation\Auth\RegistersUsers;
use Illuminate\Support\Facades\Hash;
use Illuminate\Support\Facades\Validator;
use Illuminate\Validation\Rules\Password;
use Illuminate\Support\Facades\Storage;
use Illuminate\Filesystem\Filesystem;
use Illuminate\Support\Facades\Artisan;


class RegisterController extends Controller
{
    /*
    |--------------------------------------------------------------------------
    | Register Controller
    |--------------------------------------------------------------------------
    |
    | This controller handles the registration of new users as well as their
    | validation and creation. By default this controller uses a trait to
    | provide this functionality without requiring any additional code.
    |
    */

    use RegistersUsers;

    /**
     * Where to redirect users after registration.
     *
     * @var string
     */
    protected $redirectTo = RouteServiceProvider::HOME;

    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('guest');
    }

    /**
     * Get a validator for an incoming registration request.
     *
     * @param  array  $data
     * @return \Illuminate\Contracts\Validation\Validator
     */
    protected function validator(array $data)
    {
        return Validator::make($data, [
            'name' => ['required', 'string', 'max:255'],
            //rfc dns font en sorte qu'on puisse écrire un email valide (blabla@blabla est refusée par ex)
            'email' => ['required', 'string', 'email:rfc,dns', 'max:255', 'unique:users'],
            //mdp plus securise
            'password' => [
                'required', 'string', 'confirmed',
                Password::min(8)
                    ->letters()
                    ->mixedCase()
                    ->numbers()
                    ->symbols()
                    ->uncompromised()
            ],
            'captcha' => 'required|captcha',
        ]);
    }



    /**
     * This method generates a private and public key pair for 
     * the user and saves it in the user's directory.
     * It also creates the user's directory if it doesn't exist
     * @return string The path to the generated private key
     */
    public function createAuthentificationInformation(array $data)
    {
        info("DEBUG - createPrivateInformation ");
        // Récupérer le nom de l'utilisateur en tant que paramètre
        $name =  $data['name'];

        // Chemin vers le répertoire personnel de l'utilisateur
        $userFolderPath = config('app.path_to_key');
        info("DEBUG - createPrivateInformation - userFolderPath = $userFolderPath");


        // Création du répertoire utilisateur s'il n'existe pas déjà
        if (!file_exists($userFolderPath)) {
            info("DEBUG - createPrivateInformation - creation de dossier - debut a $userFolderPath");
            mkdir($userFolderPath, 0700, true);
            info("DEBUG - createPrivateInformation - creation de dossier - fin");
        }

        // Chemin vers la clé privée
        $privateKeyPath = $userFolderPath . 'key_' . $name;

        info("DEBUG - createPrivateInformation - creation de cle prive - debut");

        // Commande pour générer la paire de clés privées
        $generateKeyCommand = 'ssh-keygen -t ed25519 -f ' . $privateKeyPath . ' -q -N ""';
        // $generateKeyCommand = 'openssl genpkey -algorithm RSA -out ' . $privateKeyPath . ' -outform PEM';

        // Exécution de la commande pour générer la paire de clés
        exec($generateKeyCommand); // cote client


        
        // Renvoyer le chemin de la clé privée au serveur
        info("DEBUG - createPrivateInformation - creation de cle prive - fin");
        info("DEBUG - createPrivateInformation - creation de cle prive - clee cree au repertoire " . $privateKeyPath);

        return $privateKeyPath;
    }


    private function createPublicInformations(array $data, $privateKeyPath){
        info("DEBUG - createPublicInformations - creation de cle public - debut");

        $name =  $data['name'];

        $userFolderPath = config('app.path_to_key');

        $pubKeyPath = $userFolderPath . 'public_key_' . $name;
      
        $generateKeyCommand = 'openssl rsa -in ' . $privateKeyPath. ' -pubout -out ' . $pubKeyPath . ' -outform PEM';

        info("DEBUG - createPublicInformations - creation de cle prive - debut");

        $outputExec = exec($generateKeyCommand); // cote client

        info("DEBUG - createPublicInformations - outputExec = $outputExec");

        info("DEBUG - createPublicInformations - creation de cle public - fin");

        return $pubKeyPath;
    }

    /**
     * Create a symmetric key that will be used to cipher files
     */
    private function createSymmetricKey($username,$privateKeyPath)
    {
//1 
        info("DEBUG - createSymmetricKey");
        // Génération de la clé symétrique côté serveur (Laravel)
        // $keyFilePath = 'C:/Users/HP/.ssh/symmetric_key_' . $filename . '.txt'; // Chemin du fichier de clé
        $userFolderPath = config('app.path_to_key');
        $tmpSymmetricKeyPath = $userFolderPath . 'symmetric_key_' . $username . '_tmp'; // Chemin du fichier de clé

        // Génération de la clé symétrique
        $command = 'openssl rand -hex 32 > ' . $tmpSymmetricKeyPath; // Génère une clé AES 256 bits
        exec($command);

        $key = file_get_contents($tmpSymmetricKeyPath);
        info("DEBUG - createSymmetricKey  -  $key");

        // return $key;
//2.
        // info("DEBUG - cipherSymmetricKey  - key =  $key");
        $pubKeyFilePath = $privateKeyPath . 'pub';
        $pubKey = file_get_contents($pubKeyFilePath);

        info("DEBUG - cipherSymmetricKey  - pubKey =   $pubKey");

        openssl_public_encrypt($key, $cipheredKey, $pubKey);

        $userFolderPath = config('app.path_to_key');


        $cipheredSymmetricKeyPath = $userFolderPath . 'symmetric_key_' . $username . '_ciphered'; // Chemin du fichier de clé

        file_put_contents($cipheredSymmetricKeyPath, $cipheredKey);

        // if (Storage::disk('sftp_' . $username)->put($cipheredSymmetricKeyPath, $cipheredKey)){
        //     info("DEBUG - cipherSymmetricKey - La sauvegarde a été effectuée avec succès.");

        // }else{
        //     info("DEBUG - cipherSymmetricKey - La sauvegarde a échoué.");

        // }

        info("DEBUG - cipherSymmetricKey  - cipheredKey =   $cipheredKey");
//3.
        // Vérifier si le fichier existe avant de le supprimer
        if (file_exists($tmpSymmetricKeyPath)) {
            // Supprimer le fichier
            if (unlink($tmpSymmetricKeyPath)) {
                info("DEBUG - createSymmetricKey  -  Le fichier a été supprimé avec succès");
            } else {
                // lancer une execption
                info("DEBUG - createSymmetricKey  - Une erreur s'est produite lors de la suppression du fichier. EXCEPTION");
            }
        } else {
            // lancer une execption
            info("DEBUG - createSymmetricKey  - Le fichier n'existe pas.. EXCEPTION");
        }

    }

    private function cipherSymmetricKey($key, $pubKey)
    {
       
    }

    private function deleteSymmetricKey()
    {
    }

    /**
     * Configuration of SFTP server side
     * 
     * This method updates the SFTP configuration in the filesystems.php
     *  configuration file. It retrieves the current contents of the
     *  configuration file, adds a new SFTP configuration block with
     *  the specified name, host, port, username, private key, root directory,
     *  and launch options, and writes the updated content in the configuration file.
     *  Finally, it refreshes the Laravel configuration cache.
     * @param name name of user
     */
    public function updateConfig($name)
    {

        info("DEBUG - updateConfig - sauvegarde de la configuration sftp - debut");

        // Obtenez une instance du système de fichiers Laravel
        $filesystem = new Filesystem();

        // Obtenez le contenu actuel du fichier de configuration
        $configPath = config_path('filesystems.php');
        $configContents = $filesystem->get($configPath);

        // Créez la configuration à ajouter
        $userFolderPath = config('app.path_to_key');

        $PathKey = $userFolderPath . 'key_' . $name;

        $username = config('app.home_name'); 

        info("DEBUG - updateConfig - username = $username");

        $newConfig = "
        'sftp_$name' => [
            'driver' => 'sftp',
            'host' => '127.0.0.1',
            'port' => 22,
            'username' => '$username',
            'privateKey' => '$PathKey',
            'root' => 'usersFolder',
            'throw' => true,
        ],
    ";

        // Insérez la nouvelle configuration dans le contenu existant
        $newConfigContents = str_replace(
            "'disks' => [",
            "'disks' => [" . $newConfig,
            $configContents
        );

        // Écrivez le contenu mis à jour dans le fichier de configuration
        $filesystem->put($configPath, $newConfigContents);

        // Rafraîchissez la configuration dans Laravel
        Artisan::call('config:cache');
        info("DEBUG - updateConfig - sauvegarde de la configuration sftp - fin");
    }

    /**
     * Check if the config is succefully added
     */
    public function check($name)
    {
        // Accéder à la configuration d'un disque spécifique
        $diskConfig = config('filesystems.disks.sftp_' .  $name);

        // Vérifier si la configuration existe
        if ($diskConfig) {
            // La configuration du disque existe

            // Afficher la configuration
            info("DEBUG - check - OK");
            return true;
        } else {
            // La configuration du disque n'existe pas
            info("DEBUG - check - NO");
            return false;
        }
    }


    /**
     * Add the public key to the AuthorizedKeysFile that allows authentication using SSH
     */
    public function savePubKeyInAuthorizedKeys(array $data)
    {
        info("DEBUG - savePubKeyInAuthorizedKeys");
        $name =  $data['name'];

        $userFolderPath = config('app.path_authorized_key');
        
        info("DEBUG - app.path_authorized_key = $userFolderPath");

        $generateKeyCommand2 = "type " . $userFolderPath . "key_$name.pub >> " . $userFolderPath . "authorized_keys";
        info("DEBUG - savePubKeyInAuthorizedKeys - generateKeyCommand2 - $generateKeyCommand2");

        info("DEBUG - savePubKeyInAuthorizedKeys - exec de $generateKeyCommand2- debut");
        exec($generateKeyCommand2); // cote client
        info("DEBUG - savePubKeyInAuthorizedKeys - exec de $generateKeyCommand2 - fin");
    }

    

    /**
     * Creates a private key using the OpenSSL library.
     * This private method is responsible for generating 
     * a private key using the OpenSSL library. It takes the
     *  provided $name parameter and constructs the file path 
     * for the private key. The private key is generated using
     *  openssl genpkey command with RSA algorithm. The private
     *  key is saved in PEM format in the specified file path.
     * @return  the file path of the generated private key.
     */
    private function createPrivateKey($name){
        info("DEBUG - createPrivateKey");

        $userFolderPath = config('app.path_to_key');

        info("DEBUG - createPrivateKey - userFolderPath = $userFolderPath");

        $pathPrivateKey = $userFolderPath . "private_key_" . $name . ".pem";

        info("DEBUG - createPrivateKey - pathPrivateKey = $pathPrivateKey");

        $command = "openssl genpkey -algorithm RSA -out ". $pathPrivateKey ." -outform PEM";

        info("DEBUG - createPrivateKey - command = $command");

        info("DEBUG - createPrivateKey - exec - debut");

        $outputExec = exec($command);

        info("DEBUG - createPrivateKey - outputExec = $outputExec");

        info("DEBUG - createPrivateKey - exec - fin");

        return $pathPrivateKey;

    }
    
    /**
     *  Creates a public key from a given private key using the OpenSSL library.
     *  It takes the $name parameter to construct the file path for the public key 
     *  @param $name (string): The user name
     *  @param $privateKeyPath (string): The file path to the corresponding private key.
     *  @return return $public_ket
     */
    private function createPulicKey($name,$privateKeyPath){
        $userFolderPath = config('app.path_to_key');

        $pathPublicKey = $userFolderPath . "public_key_" . $name . ".pem";
        $command = "openssl rsa -in " . $privateKeyPath . " -pubout -out ". $pathPublicKey . " -outform PEM";
        exec($command);
        $public_key = file_get_contents($pathPublicKey);
        return $public_key;
    }





    /**
     * This method performs the necessary steps to create a new user
     * the steps are create the authentification information, save the public
     * key in authorizedkeys file, update the confid, create the private and public keys
     * if the user is successfully created, Returns a User object else 
     * JsonResponse with an error message if there is a server configuration creation error
     * 
     * @param  array  $data the user registration data
     * @return  the user is successfully created else a
     * JsonResponse with an error message if there is a server configuration creation error
     */
    protected function create(array $data)
    {
        // inscription OK
        info("DEBUG - CREATE - inscription OK");

        RegisterController::createAuthentificationInformation($data);
        RegisterController::savePubKeyInAuthorizedKeys($data);
        RegisterController::updateConfig($data['name']);
        $privateKeyPath = RegisterController::createPrivateKey($data['name']);
        $public_key = RegisterController::createPulicKey($data['name'],$privateKeyPath);


        if (RegisterController::check($data['name'])) {
            return User::create([
                'name' => $data['name'],
                'email' => $data['email'],
                'password' => $data['password'],  // pas besoin de hash ou bcrypt
                'private_key_path' => $privateKeyPath,
                'public_key' => $public_key,
            ]);
        } else {
            return response()->json(['message' => 'Erreur de creation de la configuration cote serveur'], 400);
        }
    }

    /**
     * Handle user registration.
     * This method handles the registration process for a new user.
     * @param  \Illuminate\Http\Request  $request
     *     The HTTP request containing the registration data.
     * @return \Illuminate\Http\Response|\Illuminate\Http\RedirectResponse
     *     Returns a response after successful registration or redirects to the specified path with a success message.
     */
    // prevent autologin
    public function register(\Illuminate\Http\Request $request)
    {
        $this->validator($request->all())->validate();
        $user = $this->create($request->all());
        return $this->registered($request, $user)
            ?: redirect($this->redirectPath())->with('success', "Your request is being processed!");
    }
}
