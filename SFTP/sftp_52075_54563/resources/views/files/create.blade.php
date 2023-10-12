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
                <h3 class="flow-text"><i class="material-icons">folder</i> Upload file
                    <a href="{{ url('/files') }}/create" class="btn waves-effect waves-light right tooltipped" data-position="left" data-delay="50" data-tooltip="upload file"><i class="material-icons">file_upload</i> upload file</a>
                </h3>
                <div class="divider"></div>
            </div>
            <div class="row">
                {!! Form::open(['action' => 'App\Http\Controllers\FileController@store', 'method' => 'POST', 'enctype' => 'multipart/form-data', 'class' => 'col s12']) !!}
                {{ csrf_field() }}
                <div class="col m6 s12">

                    <div class="card hoverable">
                        <div class="card-content" style="overflow-x:auto;">
                            <h5>General informations</h5>
                            <div style="min-height: 2px !important;"></div>
                            <div class="input-field">
                                <i class="material-icons prefix">folder</i>
                                {{ Form::text('title','',['class' => 'validate', 'id' => 'title']) }}
                                <label for="title">title</label>
                                @if ($errors->has('title'))
                                <span class="red-text"><strong>{{ $errors->first('title') }}</strong></span>
                                @endif
                            </div>
                            <br>
                            
                            <div class="file-field input-field">
                                <div class="btn white">
                                    <span class="black-text">choose file</span>
                                    {{ Form::file('name') }}
                                    @if ($errors->has('name'))
                                    <span class="red-text"><strong>{{ $errors->first('name') }}</strong></span>
                                    @endif
                                </div>
                                <div class="file-path-wrapper">
                                    <input class="file-path validate" type="text">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="col m6 s12">
                    <div class="card hoverable">
                        <div class="card-content" style="overflow-x:auto;">
                            <h5>Click on upload to upload your file :</h5>
                            <div class="input-field">
            
                                <div class="row">
                                    <div class="col m12 s12" style="padding-left:0px !important">
                                        <div style="min-height: 1px;"></div>
                                        <!-- <div class="input-field mgdiv">
                                            <div class="select-wrapper">
                                                <label for="shared_with" class="blue-text labelspecial">shared with</label>
                                                <select multiple="multiple" name="shared_with[]" id="shared_with">
                                                    <option value="">Choose users</option>
                                                    @if(count($contacts) > 0)
                                                    @foreach($contacts as $contact)
                                                        @if($contact->receiver_id == $user->id)
                                                            <option value="{{ $contact->requester->email }}" >{{ $contact->requester->name." (".$contact->requester->email.")" }}</option>
                                                        @else
                                                        <option value="{{ $contact->receiver->email }}" >{{ $contact->receiver->name." (".$contact->receiver->email.")" }}</option>
                                                        @endif
                                                    @endforeach
                                                    @endif
                                                </select>
                                                @if ($errors->has('shared_with'))
                                                <span class="red-text"><strong>{{ $errors->first('shared_with') }}</strong></span>
                                                @endif

                                            </div>

                                        </div> -->
                                        <br>
                                        <div class="input-field">
                                            <p class="center">
                                                <a class="btn waves-effect waves-light grey darken-4" href="{{ url('/files') }}">back</a>
                                                {{ Form::submit('upload',['class' => 'btn waves-effect waves-light']) }}
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
