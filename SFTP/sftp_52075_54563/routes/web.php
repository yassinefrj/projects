<?php

use Illuminate\Support\Facades\Route;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Session;
use App\Http\Controllers\CaptchaServiceController;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/


//maximum of 10 requests for guests, 60 for authenticated users (one minute)
Route::group(['middleware' => ['XssSanitization','throttle:10|60,1']], function () {
    Route::get('/', function() {
        if (Auth::check()) {
            return redirect('/files');
        }
        return view('auth.login');
    });
    
    Route::get('/home', function () {
        if (Auth::check()) {
            return redirect('/files');
        }
        return view('auth.login');
    });
Auth::routes();
// users
Route::resource('users', App\Http\Controllers\UsersController::class);
//le store, update, ... est généré automatiquement
Route::resource('contacts', App\Http\Controllers\ContactController::class);
// files
Route::resource('files', App\Http\Controllers\FileController::class);
Route::get('files/download/{reference}', 'App\Http\Controllers\FileController@download');
Route::delete('filesDeleteMulti', 'App\Http\Controllers\FileController@deleteMulti');
Route::get('myfiles', 'App\Http\Controllers\FileController@myfiles');
Route::get('files/edit/{reference}', 'App\Http\Controllers\FileController@edit');
//patch quand on fait un update
Route::patch('files/update/{reference}', 'App\Http\Controllers\FileController@update')->name("files.update");
Route::delete('files/delete/{reference}', 'App\Http\Controllers\FileController@delete');
//contacts
Route::get('contacts/approve/{id}', 'App\Http\Controllers\ContactController@approve');
Route::get('contacts/reject/{id}', 'App\Http\Controllers\ContactController@reject');
Route::get('contacts/reset/{id}', 'App\Http\Controllers\ContactController@reset');

Route::post('files', 'App\Http\Controllers\FileController@index')->name("files.search");
Route::post('files/store', 'App\Http\Controllers\FileController@store')->name("files.store");
});

Route::post('/flash', 'App\Http\Controllers\FileController@flash');
//captcha
Route::get('/reload-captcha', [CaptchaServiceController::class, 'reloadCaptcha']);