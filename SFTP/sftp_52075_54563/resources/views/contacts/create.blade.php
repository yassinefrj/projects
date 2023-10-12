@extends('layouts.app')

@section('content')
<div class="row">
    <div class="section">
        <div class="col m1 hide-on-med-and-down">
            @include('inc.sidebar')
        </div>
        <div class="col m11 s12">
            <div class="row">
                <h3 class="flow-text"><i class="material-icons">add</i> Add contact</h3>
                <div class="divider"></div>
            </div>
            <div class="row">
                <div class="col m8 offset-m2 s12">
                    {!! Form::open(['action' => ['App\Http\Controllers\ContactController@store'], 'method' => 'POST']) !!}
                    {{ csrf_field() }}
                    <div class="card hoverable">
                        <div class="card-content">
                            <div class="input-field">
                                <i class="material-icons prefix">email</i>
                                {{ Form::email('email',$email,['class' => 'validate', 'id' => 'email']) }}
                                <label for="email" class="blue-text">current email</label>
                            </div>
                            <br>
                            <div class="row">
                                <div class="input-field">
                                    <p class="center">
                                        <a class="btn waves-effect waves-light grey darken-4" href="{{ url('/contacts') }}">back</a>
                                        {{ Form::submit('submit', ['class' => 'btn waves-effect waves-light']) }}
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
