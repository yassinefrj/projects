<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Contact extends Model
{
    use HasFactory;

    /**
     * The attributes that are mass assignable.
     *
     * @var array<int, string>
     */
    protected $fillable = [
        'requester_id',
        'receiver_id',
        'status', //relation entre les deux users.
    ];

    public function requester()
    {
        //fait le lien avec fk pour savoir qui est le requester
        return $this->belongsTo('App\Models\User', 'requester_id');
    }

    public function receiver()
    {
        //fait le lien avec fk pour savoir qui est le receiver
        return $this->belongsTo('App\Models\User', 'receiver_id');
    }

}
