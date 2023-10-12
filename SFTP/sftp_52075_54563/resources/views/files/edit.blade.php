@extends('layouts.app')

@section('content')
<?php 
$user = auth()->user();
?>
<div class="row">
    <div class="section">
        <div class="col m1 hide-on-med-and-down">
            @include('inc.sidebar')
        </div>
        <div class="col m11 s12">
            <div class="row">
                <h3 class="flow-text"><i class="material-icons">folder</i> Edit file
                </h3>
                <div class="divider"></div>
            </div>
            <div class="row">
                {!! Form::open(['action' => ['App\Http\Controllers\FileController@update',$file->reference], 'method' => 'PATCH', 'enctype' => 'multipart/form-data', 'class' => 'col s12']) !!}
                {{ csrf_field() }}
                <div class="col m6 s12">

                    <div class="card hoverable">
                        <div class="card-content" style="overflow-x:auto;">
                            <h5>General informations</h5>
                            <div style="min-height: 2px !important;"></div>
                            <div class="input-field">
                                <i class="material-icons prefix">folder</i>
                                {{ Form::text('title',$file->title,['class' => 'validate', 'id' => 'title']) }}
                                <label for="title">title</label>
                                @if ($errors->has('title'))
                                <span class="red-text"><strong>{{ $errors->first('title') }}</strong></span>
                                @endif
                            </div>                        
                            <br/>  
                        </div>
                    </div>
                </div>
                <div class="col m6 s12">
                    <div class="card hoverable">
                        <div class="card-content" style="overflow-x:auto;">
                            <h5>Manage permissions</h5>
                            <div class="input-field">
                                <div class="row">
                                    <div class="col m12 s12" style="padding-left:0px !important">
                                        <div style="min-height: 1px;"></div>
                                        <div class="input-field mgdiv">
                                            <div class="select-wrapper">
                                                <label for="shared_with" class="blue-text labelspecial">Shared with</label>
                                                <select multiple="multiple" name="shared_with[]" id="shared_with">
                                                    <option value="">Choose user</option>
                                                    @if(count($contacts) > 0)
                                                    @foreach($contacts as $contact)
                                                        @if($contact->receiver_id == $user->id)
                                                            <option value="{{ $contact->requester->email }}" {{ strpos(",".$file->shared_with.",", ",".$contact->requester->email.",") !== false ? 'selected' : '' }}>{{ $contact->requester->name." (".$contact->requester->email.")" }}</option>
                                                            
                                                            @else
                                                        <option value="{{ $contact->receiver->email }}" {{ strpos(",".$file->shared_with.",", ",".$contact->receiver->email.",") !== false ? 'selected' : '' }}>{{ $contact->receiver->name." (".$contact->receiver->email.")" }}</option>
                                                        @endif
                                                    @endforeach
                                                    @endif
                                                </select>
                                                @if ($errors->has('shared_with'))
                                                <span class="red-text"><strong>{{ $errors->first('shared_with') }}</strong></span>
                                                @endif
                                            </div>
                                        </div>
                                        <br>
                                            <div class="input-field">
                                                <p class="center">
                                                    <a class="btn waves-effect waves-light grey darken-4" href="{{ url('/files') }}">Back</a>
                                                    {{ Form::submit('Submit',['class' => 'btn waves-effect waves-light']) }}
                                                </p>
                                            </div>
                                    </div>
                                </div>

                            </div>
                        </div>
                    </div>
                </div>
                {!! Form::close() !!}
            </div>
        </div>
    </div>
</div>
@endsection
