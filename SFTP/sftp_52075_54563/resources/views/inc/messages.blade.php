@if(count($errors) > 0)
@foreach($errors->all() as $error)
<script>
    Materialize.toast("{{ $error }}", {{ @\Illuminate\Support\Facades\Config::get('app.timeout') }})
</script>
@endforeach
@endif

@if(session('success'))
<script>
            Materialize.toast("{{ @session('success') }}", {{ @\Illuminate\Support\Facades\Config::get('app.timeout') }});</script>
@endif

@if(session('error'))
<script>
            Materialize.toast("{{ @session('error') }}", {{ @\Illuminate\Support\Facades\Config::get('app.timeout') }});</script>
@endif

@if (Session::has('message.success'))
<script>
            Materialize.toast("{{ @Session::get('message.success') }}", {{ @\Illuminate\Support\Facades\Config::get('app.timeout') }});</script>
@endif

@if (Session::has('message.error'))
<script>
            Materialize.toast("{{ @Session::get('message.error') }}", {{ @\Illuminate\Support\Facades\Config::get('app.timeout') }});
</script>
@endif
