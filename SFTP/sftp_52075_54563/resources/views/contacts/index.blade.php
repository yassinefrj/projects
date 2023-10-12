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
                <h3 class="flow-text"><i class="material-icons">person</i> Contact
                    <a style="margin-right: 10px !important;" href="{{ url('/contacts') }}/create" class="btn waves-effect waves-light right tooltipped" data-position="left" data-delay="50" data-tooltip="add new contact">Add new contact</a>
                </h3>
                <div class="divider"></div>
            </div>
            <div class="card z-depth-2">
                <div class="card-content" style="overflow-x:auto;">
                    <table class="bordered centered highlight" id="myDataTable">
                        <thead>
                            <tr>
                                <th>requester</th>
                                <th>receiver</th>
                                <th>status</th>
                                <th>actions</th>
                            </tr>
                        </thead>
                        <tbody>
                            @if(count($contacts) > 0)
                            @foreach($contacts as $contact)
                            <tr>
                                <td>{{ $contact->requester->name }} - {{ $contact->requester->email }}</td>
                                <td>{{ $contact->receiver->name }} - {{ $contact->receiver->email }}</td>
                                <td>
                                    @if($contact->status == 0)
                                    <div class="teal lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">Request sent</div>
                                    @elseif($contact->status == 1)
                                    <div class="teal lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">Approved</div>
                                    @else
                                    <div class="red lighten-2" style="display: inline-block !important;padding:5px 10px;color:white !important">Rejected</div>
                                    @endif
                                </td>

                                <td>
                                    <!-- DELETE using link -->
                                    {!! Form::open(['action' => ['App\Http\Controllers\ContactController@destroy', $contact->id],
                                    'method' => 'DELETE',
                                    'id' => 'form-delete-contacts-' . $contact->id]) !!}

                                    @if($contact->status == 0 && $contact->receiver->id == $user->id)
                                    <a href="{{ url('/contacts') }}/approve/{{ $contact->id }}" class="center btn teal">Approve</a>
                                    <a href="{{ url('/contacts') }}/reject/{{ $contact->id }}" class="center btn red">Reject</a>
                                    @endif
                                    
                                    @if($contact->status == 2 && ($contact->requester->id == $user->id || $contact->receiver->id == $user->id ))
                                    <a href="{{ url('/contacts') }}/reset/{{ $contact->id }}" class="center btn teal">Send friend request</a>
                                    @endif

                                    <a href="" class="right data-delete" data-form="contacts-{{ $contact->id }}"><i class="material-icons">delete</i></a>
                                    {!! Form::close() !!}
                                </td>
                            </tr>
                            @endforeach
                            @else
                            <tr>
                                <td colspan="6"><h5 class="teal-text">No contact added</h5></td>
                            </tr>
                            @endif
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</div>
@endsection
