<?php
$numReq = 0;
$user = auth()->user();
if (isset($user)) {
    $contacts = \App\Models\Contact::latest();
    $contacts->where(function($q) use ($user) {
        $q->where('status', '=', 0)
            ->where('receiver_id', $user->id);
    });
    $contacts = $contacts->get();
    $numReq = count($contacts);
}
$requests = $numReq;
?>
<div class="card">
    <ul class="collection">
        <li class="collection-item avatar">
            <a href="#" class="button-collapse tooltipped" data-activates="slide-out" data-position="right" data-delay="50" data-tooltip="menu"><i class="material-icons circle grey">menu</i></a>
        </li>
        
        @if($user->isAdmin)
        <li class="collection-item avatar">
            <a href="{{ url('/users') }}" class="tooltipped" data-position="right" data-delay="50" data-tooltip="users"><i class="material-icons circle green">person</i></a>
        </li>
        @endif
        <li class="collection-item avatar">
            <a href="{{ url('/files') }}" class="tooltipped" data-position="right" data-delay="50" data-tooltip="files"><i class="material-icons circle green">folder</i></a>
        </li>
        <li class="collection-item avatar">
            <a href="{{ url('/myfiles') }}" class="tooltipped" data-position="right" data-delay="50" data-tooltip="my medical record"><i class="material-icons circle green">folder</i></a>
        </li>
        <li class="collection-item avatar">
            <a href="{{ url('/contacts') }}" class="tooltipped" data-position="right" data-delay="50" data-tooltip="contacts"><i class="material-icons circle green">person</i></a>
        </li>
    </ul>
</div>
<!-- ======================================================================= -->
<ul id="slide-out" class="side-nav">
   
    @if($user->isAdmin)
    <li>
        <a href="{{ url('/users') }}" ><i class="material-icons">person</i> users</a>
    </li>
    @endif
    <li>
        <a href="{{ url('/files') }}"><i class="material-icons circle green">folder</i> all files</a>
    </li>
    <li>
        <a href="{{ url('/myfiles') }}" ><i class="material-icons circle green">folder</i> my medical record</a>
    </li>
    <li>
        <a href="{{ url('/contacts') }}"><i class="material-icons circle green">person</i> contacts</a>
    </li>
</ul>
