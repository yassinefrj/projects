<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\User;
use Illuminate\Support\Facades\DB;
use Illuminate\Validation\Rules\Password;
use Illuminate\Support\Facades\Validator;

class UsersController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function __construct()
    {
        //todo : acceder quand on est admin
        return $this->middleware(['auth']);
    }

    /**
     * Retrieves the user list for the index page. 
     * This method is responsible for fetching the list of users to be displayed on the index page. 
     * If the authenticated user is an admin, it retrieves all users. Otherwise, it redirects to the 
     * file page with an access denied error message. 
     * @return \Illuminate\Contracts\View\View The rendered view of the users.index page.
     */
    public function index()
    { 
        //préciser le disque ou on veut créer le fichier
        //Storage::disk('sftp')->put('blabla/1', $content);
        if (auth()->user()->isAdmin) {
            //recuperer tous les users
            $users = User::all();
        } else {
            return redirect('/files')->with('error', "acces denied");
        }
        return view('users.index', compact('users'));
    }

   

    /**
     * Stores a new user in the database. This method is responsible for creating a new user
     *  and saving it in the database. If the authenticated user is an admin, the method validates the request data, 
     * including the name, email, and password fields. The password must meet certain criteria 
     * (minimum length, containing letters, mixed case, numbers, symbols, and being uncompromised). 
     * If the validation fails or the authenticated user is not an admin, the method redirects to 
     * the file page with an access denied error message. 
     * @param \Illuminate\Http\Request $request The HTTP request object containing the user data. 
     * @return \Illuminate\Http\RedirectResponse The redirect response to the users page with a success message.
     */
    public function store(Request $request)
    {
        if (auth()->user()->isAdmin) {
            $this->validate($request, [
                'name' => 'required|string|max:255',
                //email validate avec rfc,dns
                'email' => 'required|string|email:rfc,dns|max:255|unique:users',
                'password' => ['required', 'string', 'confirmed',
                Password::min(8)
                    ->letters()
                    ->mixedCase()
                    ->numbers()
                    ->symbols()
                    ->uncompromised()
                ],
            ]);
        } else {
            return redirect('/files')->with('error', "acces denied");
        }

        $user = new User;
        $user->name = $request->input('name');
        $user->email = $request->input('email');
        $user->password = $request->input('password');
        //l'admin a le choix
        if (isset($_POST["status"])) {
            $user->status = 1;
        } else {
            $user->status = 0;
        }

        if (isset($_POST["isAdmin"])) {
            $user->isAdmin = 1;
        } else {
            $user->isAdmin = 0;
        }
        if (isset($_POST["isDoctor"])) {
            $user->isDoctor = 1;
        } else {
            $user->isDoctor = 0;
        }
        if (isset($_POST["isPatient"])) {
            $user->isPatient = 1;
        } else {
            $user->isPatient = 0;
        }
        
        $user->save();

        return redirect('/users')->with('success', "User created successfuly.");
    }

    /**
     * Displays the edit form for a user. This method is responsible for displaying
     *  the edit form for a specific user. It performs additional security checks to ensure that the provided ID is
     *  valid and numeric, and if not, it returns a 404 error page. If the authenticated user is an admin, 
     * the method fetches the user with the corresponding ID from the database and passes it to the view. 
     * The view is then rendered, allowing the admin to modify the user's information. 
     * If the authenticated user is not an admin, the method redirects to the file page with an access denied error message. 
     * @param int $id The ID of the user to edit. 
     * @return \Illuminate\Contracts\View\View|\Illuminate\Http\RedirectResponse The view for editing the user or a redirect response in case of errors.
     */
    public function edit($id)
    {
        // sécurité supplémentaire ppour que ce soit vmt l'id => on passe par validator
        $validator = Validator::make(['id' => $id], [
            'id' => 'required|numeric'
        ]);
        
        if ($validator->fails()) {
            //le hacker est redirigé vers un epage d'erreur s'il tente d emofidier l'url pour acceder à un contact
            abort(404);
        }
        if (auth()->user()->isAdmin) {
            $user = User::findOrFail($id);   
            return view('users.edit', compact('user'));
        }else {
            return redirect('/files')->with('error', "acces denied");
        }
    }

    /**
     * This method updates a user's information by performing security checks
     * additional. It validates the user ID to prevent unauthorized access and redirects
     * In case of error. Only users with administrative privileges are allowed to perform
     * updates. Form fields are validated and errors are handled, ensuring data integrity.
     *
     * @param \Illuminate\Http\Request $request The HTTP request containing the form data. 
     * @param int $id The ID of the user to update.
     * @return \Illuminate\Http\RedirectResponse The redirect response.
     */
    public function update(Request $request, $id)
    {
        // sécurité supplémentaire ppour que ce soit vmt l'id => on passe par validator
        $validator = Validator::make(['id' => $id], [
            'id' => 'required|numeric'
        ]);
        
        if ($validator->fails()) {
            //le hacker est redirigé vers un epage d'erreur s'il tente de mofidier l'url pour acceder à un contact
            abort(404);
        }
        $user = User::findOrFail($id);
        if (auth()->user()->isAdmin) {
            $this->validate($request, [
                'name' => 'required|string|max:255',
                'email' => 'required|string|email:rfc,dns|max:255|unique:users,email,' . $user->id,
            ]);
        } else {
            return redirect('/files')->with('error', "acces denied");
        }

        $user->name = $request->input('name');
        $user->email = $request->input('email');
        if (isset($_POST["status"])) {
            $user->status = 1;
        } else {
            $user->status = 0;
        }
        if (isset($_POST["isAdmin"])) {
            $user->isAdmin = 1;
        } else {
            $user->isAdmin = 0;
        }
        if (isset($_POST["isDoctor"])) {
            $user->isDoctor = 1;
        } else {
            $user->isDoctor = 0;
        }
        if (isset($_POST["isPatient"])) {
            $user->isPatient = 1;
        } else {
            $user->isPatient = 0;
        }
        if (isset($_POST["password"]) && !empty($_POST["password"])) {
            $user->password = $request->input('password');
        }
        
        $user->save();
        return redirect('/users')->with('success',"User edited successfuly." );
    }



    /**
     * Removes a user from the database by performing security checks.
     *  Only administrators are allowed. Uses a database transaction to 
     * ensure data integrity.
     *
     * @param  $id The ID of the user to delete
     * @return \Illuminate\Http\RedirectResponse Redirect to users page with success or error message
     */
    public function destroy($id)
    {
        $validator = Validator::make(['id' => $id], [
            'id' => 'required|numeric'
        ]);
        
        if ($validator->fails()) {
            //le hacker est redirigé vers un epage d'erreur s'il tente d emofidier l'url pour acceder à un contact
            abort(404);
        }
        if (auth()->user()->isAdmin) {          
            DB::beginTransaction();
            try {
                //$id = (int) $id;
                $user = User::find($id);
                $user->delete();
                DB::commit();
                return redirect('/users')->with('success', "User deleted successfuly.");
            } catch (\Exception $ex) {
                DB::rollback();
                return redirect('/users')->with('error', "Fail to delete the user.");
            }
        }else {
            return redirect('/files')->with('error', "acces denied");
        }
    }
}
