@extends('layouts.app')

@section('content')
<div class="row">
    <div class="section">
        <div class="col m1 hide-on-med-and-down">
            @include('inc.sidebar')
        </div>
        <div class="col m11 s12">
            <div class="row">
                <h3 class="flow-text"><i class="material-icons">person</i> Users
                    <button data-target="modal1" class="btn modal-trigger right">Add new user</button>
                </h3>
                <div class="divider"></div>
            </div>
            <div class="card z-depth-2">
                <div class="card-content" style="overflow-x:auto;">
                    <table class="bordered centered highlight" id="myDataTable">
                        <thead>
                            <tr>
                                <th>name</th>
                                <th>email</th>
                                <th>status</th>
                                <th>admin</th>
                                <th>docteur</th>
                                <th>patient</th>
                                <th>actions</th>
                            </tr>
                        </thead>
                        <tbody>
                            @if(count($users) > 0)
                            @foreach($users as $user)
                            <tr>
                                <td>{{ $user->name }}</td>
                                <td>{{ $user->email }}</td>
                                <td>
                                    @if($user->status)
                                    <div class="teal lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">Activated</div>
                                    @else
                                    <div class="red lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">Desactivated</div>
                                    @endif
                                </td>

                                <td>
                                    @if($user->isAdmin)
                                    <div class="teal lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">YES</div>
                                    @else
                                    <div class="red lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">NO</div>
                                    @endif
                                </td>
                                <td>
                                    @if($user->isDoctor)
                                    <div class="teal lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">YES</div>
                                    @else
                                    <div class="red lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">NO</div>
                                    @endif
                                </td>
                                <td>
                                    @if($user->isPatient)
                                    <div class="teal lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">YES</div>
                                    @else
                                    <div class="red lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">NO</div>
                                    @endif
                                </td>
                                <td>
                                    <!-- DELETE using link -->
                                    {!! Form::open(['action' => ['App\Http\Controllers\UsersController@destroy', $user->id],
                                    'method' => 'DELETE',
                                    'id' => 'form-delete-users-' . $user->id]) !!}
                                    <a href="{{ url('/users') }}/{{ $user->id }}/edit" class="center"><i class="material-icons">mode_edit</i></a>
                                    <a href="" class="right data-delete" data-form="users-{{ $user->id }}"><i class="material-icons">delete</i></a>
                                    {!! Form::close() !!}
                                </td>
                            </tr>
                            @endforeach
                            @else
                            <tr>
                                <td colspan="6"><h5 class="teal-text">No user added</h5></td>
                            </tr>
                            @endif
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</div>
<!-- Modal -->
<!-- Modal Structure -->
<div id="modal1" class="modal">
    {!! Form::open(['action' => 'App\Http\Controllers\UsersController@store', 'method' => 'POST', 'class' => 'col s12']) !!}
    <div class="modal-content">
        <h4>Add user</h4>
        <div class="divider"></div>
        <div class="row">
            <div class="col m6 s12 input-field">
                <i class="material-icons prefix">account_circle</i>
                {{ Form::text('name','',['class' => 'validate', 'id' => 'name']) }}
                <label for="name">name</label>
            </div>
            <div class="col m6 s12 input-field">
                <i class="material-icons prefix">email</i>
                {{ Form::email('email','',['class' => 'validate', 'id' => 'email']) }}
                <label for="email">email</label>
            </div>
        </div>
        <div class="row">
            <div class="col m6 s12 input-field">
                <i class="material-icons prefix">vpn_key</i>
                {{ Form::password('password',['class' => 'validate', 'id' => 'password']) }}
                <label for="password">password</label>
            </div>
            <div class="col m6 s12 input-field">
                <i class="material-icons prefix">vpn_key</i>
                {{ Form::password('password_confirmation',['class' => 'validate', 'id' => 'password-confirm']) }}
                <label for="password-confirm">confirm password</label>
            </div>
        </div>
        <div class="row">
            <!-- Switch -->
            <div class="switch left">
                <h5>status</h5>
                <label>
                    <!-- par défaut, l'user est actif -->
                    desactivated
                    {{ Form::checkbox('status','1',true) }}
                    <span class="lever"></span>
                    activated
                </label>
            </div>
        </div>
        <div class="row">
            <!-- Switch -->
            <div class="switch left">
                <h5>is admin ?</h5>
                <label>
                    no
                    {{ Form::checkbox('isAdmin','') }}
                    <span class="lever"></span>
                    yes
                </label>
            </div>
        </div>
        <div class="row">
            <!-- Switch -->
            <div class="switch left">
                <h5>is doctor ?</h5>
                <label>
                    no
                    {{ Form::checkbox('isDoctor','') }}
                    <span class="lever"></span>
                    yes
                </label>
            </div>
        </div>
        <div class="row">
            <!-- Switch -->
            <div class="switch left">
                <h5>is patient ?</h5>
                <label>
                    no
                    {{ Form::checkbox('isPatient','') }}
                    <span class="lever"></span>
                    yes
                </label>
            </div>
        </div>
    </div>
    <div class="modal-footer">
        {{ Form::submit('submit',['class' => 'btn']) }}
    </div>
    {!! Form::close() !!}
</div>
@endsection
