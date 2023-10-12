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
<!--<i class="material-icons">library_books</i>-->
<nav>
    <div class="nav-wrapper indigo darken-4">
        <a href="{{ url('/') }}" class="brand-logo hide-on-med-and-down">
           <i class="material-icons">library_books</i>
        </a>
        <a href="{{ url('/') }}" class="brand-logo center">
            SFTP
        </a>
        <a href="#" data-activates="mobile-demo" class="button-collapse">
            <i class="material-icons">menu</i>
        </a>
        <!-- Mobile View -->
        <ul class="side-nav" id="mobile-demo">
            @if(Auth::guest())
            <li><a href="{{ route('login') }}">Login</a></li>
            <li><a href="{{ route('register') }}">Register</a></li>
            @else
            @if($user->isAdmin)
            <li>
                <a href="{{ url('/users') }}" ><i class="material-icons">person</i> Users</a>
            </li>
            @endif      
            <li>
                <a href="{{ url('/files') }}"><i class="material-icons">folder</i> All files</a>
            </li>
            <li>
                <a href="{{ url('/myfiles') }}"><i class="material-icons">folder</i> My Medical Record</a>
            </li>
            <li>
                <a href="{{ url('/contacts') }}"><i class="material-icons">person</i> Contact</a>
            </li>
            <li class="divider"></li>
            <li>
                <a href="{{ route('logout') }}"
                   onclick="event.preventDefault();
                           document.getElementById('logout-form').submit();">
                    <i class="material-icons">radio_button_checked</i> Logout
                </a>

                <form id="logout-form" action="{{ route('logout') }}" method="POST" style="display: none;">
                    {{ csrf_field() }}
                </form>
            </li>
            @endif
        </ul>
        <!-- Desktop View -->
        <ul class="right">
            <!-- Authentication Links -->
            @if (Auth::guest())
            <li class="hide-on-med-and-down"><a href="{{ route('login') }}"> Login</a></li>
            <li class="hide-on-med-and-down"><a href="{{ route('register') }}"> Register</a></li>
            @else
            @if($requests != 0)
            <li class="hide-on-med-and-down">
                <a href="{{ url('/contacts') }}">friend requests<span class="new badge white-text">{{ $requests }}</span></a>
            </li>
            @endif
            <li class="hide-on-med-and-down">
                <a class="dropdown-button" href="#!" data-activates="dropdown1">{{ Auth::user()->name }}
                    <i class="material-icons right">arrow_drop_down</i>
                </a>
            </li>
            @endif
        </ul>
    </div>
</nav>
<!-- Dropdown Structure -->
<ul id="dropdown1" class="dropdown-content">
    <li>
        <a href="{{ route('logout') }}"
           onclick="event.preventDefault();
                   document.getElementById('logout-form1').submit();">
             Logout
        </a>

        <form id="logout-form1" action="{{ route('logout') }}" method="POST" style="display: none;">
            {{ csrf_field() }}
        </form>
    </li>
</ul>



