<?php

namespace App\Http\Controllers;

use App\Models\Contact;
use App\Models\User;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Validator;

class ContactController extends Controller
{

    public function __construct()
    {
        return $this->middleware(['auth']); //un user pas connecter ne peut pas accéder aux fonctions liée au folder.
    }

    /**
     * Display a listing of the resource.
     * This method retrieves the authenticated user and fetches the contact information.
     * If the user is an admin, it retrieves all contacts with their requester and receiver details.
     * If the user is not an admin, it retrieves contacts where the user is either the requester or the receiver,
     * along with their requester and receiver details.
     * Finally, it returns the 'contacts.index' view, passing the contacts data to the view
     * @return \Illuminate\View\View
     * Returns the 'contacts.index' view with the contacts data.
     */
    public function index()
    {
        $user = auth()->user();
        $contacts = [];
        if($user->isAdmin){
            $contacts = Contact::with(['requester','receiver'])->get();
        }else{
            $contacts = Contact::with(['requester','receiver'])->where('requester_id', '=', $user->id)->orWhere('receiver_id', '=', $user->id)->get();
        }
        return view('contacts.index', compact('contacts'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        $email = null;
        return view('contacts.create', compact('email'));
    }

    /**
     *
     * This method is responsible for storing a new contact based on the provided request data.
     * It validates the request data, ensuring that the 'email' field is required.
     * It then retrieves the authenticated user and the email from the request.
     * It searches for a receiver user with the specified email and a status of 1 (active).
     * If a valid receiver is found, it checks if there is already an invitation sent between the requester and receiver.
     * If an invitation exists, it redirects to the contact creation page with an error message.
     * If no invitation exists, it creates a new contact with the requester and receiver IDs and a status of 0 (pending).
     * Finally, it redirects to the contact index page with a success message if the contact is saved, or redirects
     * back to the contact creation page with an error message if the contact could not be saved.
     *
     *
     * @param  \Illuminate\Http\Request  $request
     * The request object containing the contact information.
     * @return \Illuminate\Http\Response Returns a redirect response to either the contact index page or the contact creation page.
     */
    public function store(Request $request)
    {
        $this->validate($request, [
            'email' => 'required'
        ]);
        $user =  auth()->user();
        $email = $request->input('email'); 
        // à ne pas confondre avec le status de contacts qui est une relation entre 2 personnes (ici c'est activé par un admin ou pas)
        $receiver = User::where('email', $email)->where('status','=', 1)->first();
        if(isset($receiver)){
            //vérifie si l'utilisateur a envoyé une invitation 
            $checkContact = Contact::where('requester_id','=',$user->id)->where('receiver_id', '=', $receiver->id)->first();
            $checkContact2 = Contact::where('requester_id','=',$receiver->id)->where('receiver_id', '=', $user->id)->first();
            if(isset($checkContact) || isset($checkContact2)){
                return redirect('/contacts/create')->with('error', 'You already sent an invitation for this user');
            }else{
                $contact = new Contact;
                $contact->requester_id = auth()->user()->id;
                $contact->receiver_id = $receiver->id;
                $contact->status = 0;
                $contact->save();
                return redirect('/contacts')->with('success', 'Invitation sent');
            } 
        }else{
            return redirect('/contacts/create')->with('error', 'This contact does not exist. Try again.');
        }
    }


    /**
     * Delete a contact.
     *
     * This method is responsible for deleting a contact based on the provided contact ID.
     * It performs additional security checks by validating the ID using the Validator class.
     * If the validation fails, it aborts the request with a 404 error.
     * It retrieves the contact using the provided ID.
     * It then checks if the authenticated user is either the receiver or the requester of the contact,
     * and if the contact exists.
     * If the conditions are met, it deletes the contact and commits the database transaction.
     * It redirects to the contact index page with a success message if the contact is deleted.
     * If the conditions are not met, it redirects to the contact index page with an error message.
     * If any exception occurs during the process, it rolls back the database transaction and redirects
     * to the contact index page with an error message.
     * @param  int  $id
     *     The ID of the contact to be deleted.
     * @return \Illuminate\Http\RedirectResponse
     *     Returns a redirect response to the contact index page.
     */
    public function destroy($id)
    {
        DB::beginTransaction();
        try {
            //sécurité supplémentaire pour "id", on passe par validator
            $validator = Validator::make(['id' => $id], [
                'id' => 'required|numeric'
            ]);
            
            if ($validator->fails()) {
                abort(404);
            }
            
            $contact = Contact::find($id);
            $user=auth()->user();
            //sécurité supp -> il faut que celui qui supprime soir soit le receiver soit le requester
            // ET il faut qu'il existe
            if(isset($contact)){
                if(($contact->receiver_id == $user->id) || ($contact->requester_id == $user->id)){
                    $contact->delete();
                    DB::commit();
                    return redirect('/contacts')->with('success', 'Contact deleted successfully!');
                }else{
                    return redirect('/contacts')->with('error', 'access denied');
                }
            } 
        } catch (\Exception $ex) {
            DB::rollback();
            return redirect('/contacts')->with('error', 'Failed to delete contact!');
        }
    }

    /**
     * Approve a contact request.
     * This method approves a contact request based on the provided contact ID.
     * @param int $id
     *     The ID of the contact request to be approved.
     * @return \Illuminate\Http\RedirectResponse
     *     Returns a redirect response to the contact index page.
     */
    public function approve($id)
    {
        $user = auth()->user();
        //il faut etre receiver
        //premier arg : pour creer l'objet
        //et le second : quel requirements (ne prend que les keys)
        $validator = Validator::make(['id' => $id], [
            'id' => 'required|numeric'
        ]);
        
        if ($validator->fails()) {
            //le hacker est redirigé vers un epage d'erreur s'il tente de modifier l'url pour accéder à un contact
            abort(404);
        }
        
        $contact = Contact::find($id);
        //on vérifie si le contact existe (au cas ou l'user met un id qui n'existe pas)
        if(isset($contact)){
            if(($contact->receiver_id == $user->id) && ($contact->status == 0)){
                $contact->status = 1; //on accepte la demande
                $contact->save();
            }else{
                return redirect('/contacts')->with('error', 'access denied');
            }
        }
        return redirect('/contacts')->with('success', 'contact added successfully');
    }

    /**
     * Reject a contact request.
     * This method rejects a contact request based on the provided contact ID.
     * @param int $id
     *     The ID of the contact request to be rejected.
     * @return \Illuminate\Http\RedirectResponse
     *     Returns a redirect response to the contact index page.
     */
    public function reject($id)
    {
        $user = auth()->user();
        //il faut etre receiver
        //sécurité supplémentaire pour "id", on passe par validator
        $validator = Validator::make(['id' => $id], [
            'id' => 'required|numeric'
        ]);
        
        if ($validator->fails()) {
            //le hacker est redirigé vers une page d'erreur s'il tente de modifier l'url pour accéder à un contact
            abort(404);
        }
        $contact = Contact::find($id);
        if(isset($contact)){
            //
            if(($contact->receiver_id == $user->id) && ($contact->status == 0)){
                $contact->status = 2; //on refuse la demande
                $contact->save();
            }else{
                return redirect('/contacts')->with('error', 'access denied');
            }
        }
        return redirect('/contacts')->with('success', 'contact rejected');
    }

    /**
     * Reset a rejected contact request.
     * This method resets a rejected contact request based on the provided contact ID.
     * @param int $id
     *     The ID of the contact request to be reset.
     * @return \Illuminate\Http\RedirectResponse
     *     Returns a redirect response to the contact index page.
     */
    public function reset($id)
    {
        $user = auth()->user();      
        //sécurité supplémentaire pour "id", on passe par validator
         $validator = Validator::make(['id' => $id], [
            'id' => 'required|numeric'
        ]);
        
        if ($validator->fails()) {
            //le hacker est redirigé vers un epage d'erreur s'il tente d emofidier l'url pour acceder à un contact
            abort(404);
        }
          //il faut etre receiver
        $contact = Contact::find($id);
        if(isset($contact)){
            if(($contact->receiver_id == $user->id || $contact->requester_id == $user->id ) && ($contact->status == 2)){
                $contact->status = 0; //on renvoie une invitation
                $contact->save();
            }else{
                return redirect('/contacts')->with('error', 'access denied');
            }
        }
        return redirect('/contacts')->with('success', 'invitation has been resent');
    }

}
