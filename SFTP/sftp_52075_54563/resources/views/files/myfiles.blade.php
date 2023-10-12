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
    [type="checkbox"].filled-in:not(:checked)+label:after{
        width: 15px !important;
        height: 15px !important;
    }
    #masterdoc+label:before, #masterdoc:not(.filled-in)+label:after{
        width: 15px !important;
        height: 15px !important;
    }
</style>
<div class="row" id="docContent1">
    <div class="section">
        <div class="col m1 hide-on-med-and-down">
            @include('inc.sidebar')
        </div>
        <div class="col m11 s12">
            <div class="row">
                <h3 class="flow-text"><i class="material-icons">folder</i> My Medical Record
                    <button class="btn red waves-effect waves-light right tooltipped delete_all" data-url="{{ url('documentsDeleteMulti') }}" data-position="left" data-delay="50" data-tooltip="{{ trans('message.delectselecteddoc') }}"><i class="material-icons">delete</i></button>
                    @can('upload documents')
                    <a style="margin-right: 10px !important;" href="{{ url('/documents') }}/create" class="btn waves-effect waves-light right tooltipped" data-position="left" data-delay="50" data-tooltip="{{ trans('message.uploadnew') }}"><i class="material-icons">file_upload</i></a>
                    @endcan
                </h3>
                <div class="divider"></div>
            </div>
            <div class="card z-depth-2">
                <div class="card-content">
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
