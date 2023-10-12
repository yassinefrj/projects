@extends('layouts.app')

@section('content')
<div class="row">
    <div class="section">
        <div class="col m1 hide-on-med-and-down">
            @include('inc.sidebar')
        </div>
        <div class="col m11 s12">
            <div class="row">
                <h3 class="flow-text"><i class="material-icons">mode_edit</i> edit user</h3>
                <div class="divider"></div>
            </div>
            <div class="row">
                <div class="col m8 offset-m2 s12">
                    {!! Form::open(['action' => ['App\Http\Controllers\UsersController@update', $user->id], 'method' => 'PATCH', 'enctype' => 'multipart/form-data']) !!}
                    {{ csrf_field() }}
                    <div class="card hoverable">
                        <div class="card-content">
                            <div class="input-field">
                                <i class="material-icons prefix">account_circle</i>
                                {{ Form::text('name',$user->name,['class' => 'validate', 'id' => 'name']) }}
                                <label for="name" class="blue-text"> current name</label>
                            </div>
                            <div class="input-field">
                                <i class="material-icons prefix">email</i>
                                {{ Form::email('email',$user->email,['class' => 'validate', 'id' => 'email']) }}
                                <label for="email" class="blue-text">current email</label>
                            </div>
                            <div class="input-field">
                                <i class="material-icons prefix">vpn_key</i>
                                {{ Form::password('password',['id' => 'password']) }}
                                <label for="password" class="blue-text">password (Leave blank if no need to change)</label>
                            </div>
                            <div class="row">
                                <!-- Switch -->
                                <div class="switch left">
                                    <h5>status</h5>
                                    <label>
                                        @if($user->status)
                                        desactivated
                                        {{ Form::checkbox('status','1',true) }}
                                        <span class="lever"></span>
                                        activate
                                        @else
                                        desactivated
                                        {{ Form::checkbox('status','') }}
                                        <span class="lever"></span>
                                        activated
                                        @endif
                                    </label>
                                </div>
                            </div>
                            <div class="row">
                                <!-- Switch -->
                                <div class="switch left">
                                    <h5>isAdmin ?</h5>
                                    <label>
                                        @if($user->isAdmin)
                                        No
                                        {{ Form::checkbox('isAdmin','1',true) }}
                                        <span class="lever"></span>
                                        Yes
                                        @else
                                        No
                                        {{ Form::checkbox('isAdmin','') }}
                                        <span class="lever"></span>
                                        Yes
                                        @endif
                                    </label>
                                </div>
                            </div>
                            <div class="row">

                                <div class="switch left">
                                    <h5>isDoctor ?</h5>
                                    <label>
                                        @if($user->isDoctor)
                                        No
                                        {{ Form::checkbox('isDoctor','1',true) }}
                                        <span class="lever"></span>
                                        Yes
                                        @else
                                        No
                                        {{ Form::checkbox('isDoctor','') }}
                                        <span class="lever"></span>
                                        Yes
                                        @endif
                                    </label>
                                </div>
                            </div>

                            <div class="row">

                                <div class="switch left">
                                    <h5>isPatient ?</h5>
                                    <label>
                                        @if($user->isPatient)
                                        No
                                        {{ Form::checkbox('isPatient','1',true) }}
                                        <span class="lever"></span>
                                        Yes
                                        @else
                                        No
                                        {{ Form::checkbox('isPatient','') }}
                                        <span class="lever"></span>
                                        Yes
                                        @endif
                                    </label>
                                </div>
                            </div>

                        </div>
                        <br>
                        <div class="row">
                            <div class="input-field">
                                <p class="center">
                                    <a class="btn waves-effect waves-light grey darken-4" href="{{ url('/users') }}">back</a>
                                    {{ Form::submit('save changes', ['class' => 'btn waves-effect waves-light']) }}
                                </p>
                            </div>
                        </div>
                    </div>
                </div>
                {!! Form::close() !!}
            </div>
        </div>
    </div>
</div>
</div>
@endsection