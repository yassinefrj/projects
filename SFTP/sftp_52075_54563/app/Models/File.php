<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class File extends Model
{
    use HasFactory;
    
    /**
     * The attributes that are mass assignable.
     *
     * @var array<int, string>
     */
    protected $fillable = [
        'file_owner',
        'name',
        'title',
        'reference',
        'file_size',
        'file_type',
        'shared_with',
    ];

    public function owner()
    {
        return $this->belongsTo('App\Models\User', 'file_owner');
    }

}
