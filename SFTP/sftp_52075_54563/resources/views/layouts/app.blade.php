<!DOCTYPE html>
<html lang="{{ app()->getLocale() }}">
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <!-- CSRF Token -->
        <meta name="csrf-token" content="{{ csrf_token() }}">

        <title>SFTP</title>

        <link rel="stylesheet" href="{{ asset('iconfont/material-icons.css') }}">
        <!-- Materialize css -->
        <link rel="stylesheet" href="{{ asset('materialize-css/css/materialize.min.css') }}">
        <!-- datatables -->
        <link rel="stylesheet" href="{{ asset('DataTables/datatables.min.css') }}">
        <link href="{{ asset('select2/select2.min.css') }}" rel="stylesheet" />
        <link rel="stylesheet" href="{{ asset('css/custom.css') }}">
        @if(app()->getLocale() != 'en')
        <link rel="stylesheet" href="{{ asset('/') }}css/custom_{{str_replace('_', '-', app()->getLocale())}}.css">
        @endif

        <!-- favicon -->
        <link rel="shortcut icon" type="image/x-icon" href="{{ asset('/') }}img/icon.png">
        <style>
            body {
                display: flex;
                min-height: 100vh;
                flex-direction: column;
            }
            main {
                flex: 1 0 auto;
            }
            .preloader-background {
                display: flex;
                align-items: center;
                justify-content: center;
                background-color: #eee;

                position: fixed;
                z-index: 100;
                top: 0;
                left: 0;
                right: 0;
                bottom: 0;
            }
        </style>
    </head>
    <body>

        @include('inc.spinner')
        <main>
            <div id="app">
                @include('inc.navbar')
                @yield('content')
                <!-- Floating Button -->
                @if(Auth::guest())
                @else
                <div class="fixed-action-btn">
                    <a href="#" class="btn btn-floating btn-large tooltipped" data-position="left" data-delay="50" data-tooltip="{{ trans('message.quickaccess') }}">
                        <i class="large material-icons">explore</i>
                    </a>
                    <ul>
                        <li class="hide-on-med-and-down">
                            <a href="" class="btn-floating btn-large button-collapse tooltipped" data-activates="slide-out" data-position="left" data-delay="50" data-tooltip="{{ trans('message.menu') }}"><i class="large material-icons">menu</i></a>
                        </li>
                    </ul>
                </div>
                @endif
            </div>
        </main>
        @include('inc.footer')

        <!-- Scripts -->
        @include('inc.scripts')
        <!-- Right click context-menu -->
        <script src="{{ asset('js/context-menu.js') }}"></script>
        <!-- MESSAGES -->
        @include('inc.messages')
    </body>
</html>
