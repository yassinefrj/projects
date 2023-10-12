@extends('layouts.app')

@section('content')
<style>
    .card-content2 {
        padding: 10px 7px;
    }
    /* --- for right click menu --- */
    *,
    *::before,
    *::after {
        box-sizing: border-box;
    }
    .unshow {
        display: none;
    }
    [type="checkbox"].filled-in:not(:checked)+label:after{
        width: 15px !important;
        height: 15px !important;
    }
    #masterdoc+label:before, #masterdoc:not(.filled-in)+label:after{
        width: 15px !important;
        height: 15px !important;
    }
</style>

<div class="row" id="docContent">
    <div class="section">
        <div class="col m1 hide-on-med-and-down">
            @include('inc.sidebar')
        </div>
        <div class="col m11 s12">
            <div class="row">
                <h3 class="flow-text"><i class="material-icons">folder</i> files
                    <button class="btn red waves-effect waves-light right tooltipped delete_all" data-url="{{ url('filesDeleteMulti') }}" data-position="left" data-delay="50" data-tooltip="delete selected files"><i class="material-icons">delete</i></button>
                    <a style="margin-right: 10px !important;" href="{{ url('/files') }}/create" class="btn waves-effect waves-light right tooltipped" data-position="left" data-delay="50" data-tooltip="add new file"><i class="material-icons">file_upload</i></a>
                </h3>
                <div class="divider"></div>
            </div>
            <div class="card z-depth-2">
                <div class="card-content">
                    <!-- Switch -->
                    <div class="switch" style="margin-bottom: 2em;">
                        <label>
                            grid view
                            <input type="checkbox">
                            <span class="lever"></span>
                            table view
                        </label>
                    </div>
                    <div class="row" style="overflow-x: auto !important;">
                        <form action="" method="post" id="search-form">
                            {{ csrf_field() }}
                            <div class="row">
                                <input type="hidden" name="typesearch" value="{{$typesearch}}"/>
                                <div class="input-field mgdiv col m3 s6">
                                    <i class="material-icons prefix" style="color:#26a69a">info_outline</i>
                                    <div class="select-wrapper">
                                        <select name="filetype" id="sort">
                                            <option value="">select the file type</option>
                                            <option value="application/pdf" @if(isset($filetype) && $filetype === 'application/pdf') selected @endif>pdf</option>
                                            <option value="image" @if(isset($filetype) && $filetype === 'image') selected @endif>image</option>
                                            <option value="video" @if(isset($filetype) && $filetype === 'video') selected @endif>video</option>
                                            <option value="audio" @if(isset($filetype) && $filetype === 'audio') selected @endif>audio</option>
                                            <option value="text" @if(isset($filetype) && $filetype === 'text') selected @endif>text</option>
                                            <option value="application/vnd.openxmlformats-officedocument" @if(isset($filetype) && $filetype === 'application/vnd.openxmlformats-officedocument') selected @endif>office file</option>
                                            <option value="others" @if(isset($filetype) && $filetype === 'others') selected @endif>others</option>
                                        </select>
                                    </div>
                                </div>
                        
                                <div class="input-field col col m3 s6">
                                    <i class="material-icons prefix">search</i>
                                    <input type="text" name="search" id="search" value="{{$search}}" placeholder="search">
                                    <label for="search"></label>
                                </div>
                                <div class="input-field col col m3 s6">
                                    <p class="center">
                                        {{ Form::submit('search',['class' => 'btn waves-effect waves-light']) }}
                                    </p>
                                </div>
                            </div>
                        </form>
                    </div>
                    <!-- FOLDER View -->
                    <div id="folderView" style="overflow-x:auto;">
                        <br>
                        <div class="row">
                            @if(count($files) > 0)
                            @foreach($files as $file)
                            <div class="col m2 s6" id="tr_{{$file->reference}}">
                                <div class="card hoverable indigo lighten-5" data-id="{{ $file->reference }}">
                                    <input type="checkbox" class="filled-in sub_chk" id="chk_{{$file->reference}}" data-id="{{$file->reference}}">
                                    <label for="chk_{{$file->reference}}"></label>
                                        <div class="card-content2 center">
                                            @if(strpos($file->file_type, "image") !== false)
                                            <i class="material-icons">image</i>
                                            @elseif(strpos($file->file_type, "video") !== false)
                                            <i class="material-icons">ondemand_video</i>
                                            @elseif(strpos($file->file_type, "audio") !== false)
                                            <i class="material-icons">music_video</i>
                                            @elseif(strpos($file->file_type,"text") !== false)
                                            <i class="material-icons">description</i>
                                            @elseif(strpos($file->file_type,"application/pdf") !== false)
                                            <i class="material-icons">picture_as_pdf</i>
                                            @elseif(strpos($file->file_type, "application/vnd.openxmlformats-officedocument") !== false)
                                            <i class="material-icons">library_books</i>
                                            @else
                                            <i class="material-icons">folder_open</i>
                                            @endif
                                            <h6 style="white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">{{ $file->title }}</h6>
                                            <p>{{ $file->file_size }}</p>
                                        </div>
                                </div>
                            </div>
                            @endforeach
                            @else
                            <h5 class="teal-text" style="text-align: center !important;">No file uploaded</h5>
                            @endif
                        </div>
                    </div>
                    <!-- TABLE View -->
                    <div id="tableView" class="unshow" style="overflow-x:auto;">
                        <div class="row">
                            <table class="bordered centered highlight" id="myDataTable">
                                <thead>
                                    <tr>
                                        <th class="no-sort"><input type="checkbox" id="masterdoc"><label for="masterdoc"></label></th>
                                        <th>name</th>
                                        <th>owner</th>
                                        <th>created at</th>
                                        <th>actions</th>
                                    </tr>
                                </thead>
                                <tbody>
                                    @if(count($files) > 0)
                                    @foreach($files as $file)
                                    <tr id="tr_{{$file->reference}}">
                                        <td>
                                            <input type="checkbox" id="chktd_{{$file->reference}}" class="filled-in tdsub_chk" data-id="{{ $file->reference }}">
                                            <label for="chktd_{{ $file->reference }}"></label>
                                        </td>
                                        <td>{{ $file->title }}</td>
                                        <td>{{ $file->owner->name }}</td>
                                        <td>{{ $file->created_at->toDayDateTimeString() }}</td>

                                        <td>
                                         
                                            {!! Form::open() !!}
                                            <a href="{{ url('/files') }}/download/{{ $file->reference }}" class="tooltipped" data-position="left" data-delay="50" data-tooltip="download"><i class="material-icons">file_download</i></a>
                                            {!! Form::close() !!}
            
                                            @if( $file->file_owner == auth()->user()->id)
                                            {!! Form::open() !!}
                                            <a href="{{ url('/files') }}/edit/{{ $file->reference }}" class="tooltipped" data-position="left" data-delay="50" data-tooltip="edit"><i class="material-icons">mode_edit</i></a>
                                            {!! Form::close() !!}
                                            @endif

                                            <!-- DELETE using link -->
                                            @if( $file->file_owner == auth()->user()->id)
                                            {!! Form::open(['action' => ['App\Http\Controllers\FileController@destroy', $file->reference],
                                            'method' => 'DELETE', 'id' => 'form-delete-files-' . $file->reference]) !!}
                                            <a href="" class="data-delete tooltipped" data-position="left" data-delay="50" data-tooltip="delete file" data-form="files-{{ $file->reference }}"><i class="material-icons">delete</i></a>
                                            {!! Form::close() !!}
                                            @endif
                                        </td>
                                    </tr>
                                    @endforeach
                                    @else
                                    <tr>
                                        <td colspan="9"><h5 class="teal-text">No file uploaded</h5></td>
                                    </tr>
                                    @endif
                                </tbody>
                            </table>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
@endsection
