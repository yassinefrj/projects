<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::table('users', function (Blueprint $table) {
            //on ajoute un champ à la tableau user qui est un boolean
            //status etant le nom de la colonne et par defaut c'est 0.
            $table->boolean('status')->default(0);
            $table->boolean('isAdmin')->default(0);
            $table->boolean('isPatient')->default(0);
            $table->boolean('isDoctor')->default(0);
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::table('users', function (Blueprint $table) {
            $table->dropColumn('status');
            $table->dropColumn('isAdmin');
            $table->dropColumn('isPatient');
            $table->dropColumn('isDoctor');
        });
    }
};
