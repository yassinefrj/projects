<?php

namespace Database\Seeders;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use App\Models\User;

class UsersTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        // créée un admin par défaut
        $root = new User();
        $root->name = 'usersftp';
        $root->email = 'usersftp@gmail.com';
        $root->password = 'Usersftp1!';
        $root->status = true;
        $root->isAdmin = true;
        $root->save();

        // //créée un medecin par défaut
        // $doctor = new User();
        // $doctor->name = 'yassinefrj';
        // $doctor->email = 'yassinefrj@gmail.com';
        // $doctor->password = 'upbaVC#?GP!*4:h!';
        // $doctor->status = true;
        // $doctor->isDoctor = true;
        // $doctor->save();

        // //créée un patient par défaut
        // $patient = new User();
        // $patient->name = 'ibrahim';
        // $patient->email = 'ibrahim@gmail.com';
        // $patient->password = 'K!)U&[$}6Wk!U^{';
        // $patient->status = true;
        // $patient->isPatient = true;
        // $patient->save();
    }
}
