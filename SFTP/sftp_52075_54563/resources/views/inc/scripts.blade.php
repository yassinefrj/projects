<!-- JQuery -->
<script src="{{ asset('js/jquery-3.2.1.min.js') }}"></script>
<!-- Materialize css -->
<script src="{{ asset('materialize-css/js/materialize.min.js') }}" charset="utf-8"></script>
<script src="{{ asset('select2/select2.min.js') }}" charset="utf-8"></script>

<script type="text/javascript">
var initswitch = 0;
$(".dropdown-button").dropdown();
// side nav
$(".button-collapse").sideNav();
// select
//$('select').material_select();

// modal
$('#modal1').modal();
// modal for help
$('#modal2').modal();
// DELETE using link
$(function () {
    $('.data-delete').on('click', function (e) {
        if (!confirm('Are you sure you want to delete?'))
            return;
        e.preventDefault();
        $('#form-delete-' + $(this).data('form')).submit();
    });
});

// search
$(function () {
    $('#search').keypress(function (e) {
        if (e.which == 13) {
            console.log('enter pressed');
            e.preventDefault();
            $('#search-form').submit();
        }
    })
});</script>

<!-- data tables -->
<script src="{{ asset('DataTables/datatables.min.js') }}" charset="utf-8"></script>
<script type="text/javascript">
$(document).ready(function () {
    $('#myDataTable').DataTable({
//"dom": '<"right"i><"left"f><"bottom"p><"clear">',
        "language": {
            "lengthMenu": "_MENU_",
            "paginate": {
                "next": ">>",
                "previous": "<<",
            },
        },
        "order": [],
        "aLengthMenu": [
            [5, 10, 15, 50, -1],
            [5, 10, 15, 50, "All"]
        ],
        "iDisplayLength": 10,
        "columnDefs": [{
                "targets": 'no-sort',
                "orderable": false
            }]
    });
});</script>
<!-- for spinner -->
<script>
    document.addEventListener("DOMContentLoaded", function () {
        $('.preloader-background').delay(1000).fadeOut('slow');
        $('.preloader-wrapper')
                .delay(1000)
                .fadeOut();
    });</script>
<!-- sideNav -->
<script>
    $('.button-collapse').sideNav({
        menuWidth: 300, // Default is 300
        edge: 'left', // Choose the horizontal origin
        closeOnClick: true, // Closes side-nav on <a> clicks, useful for Angular/Meteor
        draggable: true, // Choose whether you can drag to open on touch screens,
    }
    );</script>
<!-- enable/disable based on checkbox -->
<script type="text/javascript">
    
    $(document).ready(function () {
        
        if ($("#shared_with").length) {
            $("#shared_with").select2({
                tags: true,
            });
        }
    });
</script>
<!-- collapsible -->
<script>
    $(document).ready(function () {
        
        $('.collapsible').collapsible();
        if ($('.switch').length) {
            if (initswitch == 0) {
                initswitch = 1;
            } else {
                initswitch = 0;
            }
            if ($("#docContent").length > 0) {
                $(".switch").find("input[type=checkbox]").prop('checked', true);
            }
            $("#folderView").toggleClass('unshow');
            $("#tableView").toggleClass('unshow');
        }
    });</script>
<!-- for checkbox multiple delete -->
<script type="text/javascript">
    //redirect after ajax call
    function redirectWithFlashMessage(redirect_url, status, message) {
        $.ajax({
            type: 'POST',
            url: '/flash',
            headers: {'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')},
            data: {'status': status, 'message': message}
        }).done(function () {
            window.location.href = redirect_url;
        });
    }
    $(document).ready(function () {

        $('#master').on('click', function (e) {
            if ($(this).is(':checked', true))
            {
                $(".sub_chk").prop('checked', true);
            } else {
                $(".sub_chk").prop('checked', false);
            }
        });
        $('#masterdoc').on('click', function (e) {
            if ($(this).is(':checked', true))
            {
                $(".tdsub_chk").prop('checked', true);
            } else {
                $(".tdsub_chk").prop('checked', false);
            }
        });
        $('.delete_all').on('click', function (e) {
            var allVals = [];
            $(".sub_chk:checked").each(function () {
                allVals.push($(this).attr('data-id'));
            });
            if ($("#docContent").length > 0) {
                if (initswitch == 1) {
                    allVals = [];
                    $(".tdsub_chk:checked").each(function () {
                        allVals.push($(this).attr('data-id'));
                    });
                }
            }
            if ($("#docContent1").length > 0) {
                allVals = [];
                $(".tdsub_chk:checked").each(function () {
                    allVals.push($(this).attr('data-id'));
                });
            }
            if (allVals.length <= 0)
            {
                alert("Please select.");
            } else {

                var check = confirm("Are you sure you want to delete these?");
                if (check == true) {
                    var join_selected_values = allVals.join(",");
                    $.ajax({
                        url: $(this).data('url'),
                        type: 'DELETE',
                        headers: {'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')},
                        data: 'references=' + join_selected_values,
                        success: function (data) {
                            if (data.status == "success") {
                                $(".sub_chk:checked").each(function () {
                                    $(this).parents("tr").remove();
                                });
                                redirectWithFlashMessage(data.redirect_url, data.status, data.message)
                            } else if (data.status == "error") {
                                redirectWithFlashMessage(data.redirect_url, data.status, data.message)

                            } else {
                                alert('Whoops Something went wrong!!');
                            }
                        },
                        error: function (data) {
                            alert('Whoops Something went wrong!!');
                        }
                    });
                    $.each(allVals, function (index, value) {
                        $('table tr').filter("[data-row-id='" + value + "']").remove();
                    });
                }
            }
        });

        $(document).on('confirm', function (e) {
            var ele = e.target;
            e.preventDefault();
            $.ajax({
                url: ele.href,
                type: 'DELETE',
                headers: {'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')},
                success: function (data) {
                    if (data['success']) {
                        $("#" + data['tr']).slideUp("slow");
                    } else if (data['error']) {
                        alert('Whoops Something went wrong!!');
                    } else {
                        alert('Whoops Something went wrong!!');
                    }
                },
                error: function (data) {
                    alert('Whoops Something went wrong!!');
                }
            });
            return false;
        });
    });</script>
<!-- switch -->
<script type="text/javascript">
    $(".switch").find("input[type=checkbox]").on("change", function () {
        if (initswitch == 0) {
            initswitch = 1;
        } else {
            initswitch = 0;
        }
        if ($(this).prop('checked')) {
            $("#folderView").toggleClass('unshow');
            $("#tableView").toggleClass('unshow');
        } else {
            $("#folderView").toggleClass('unshow');
            $("#tableView").toggleClass('unshow');
        }
    });
</script>

<script type="text/javascript">
    $('#reload').click(function () {
        $.ajax({
            type: 'GET',
            url: 'reload-captcha',
            success: function (data) {
                $(".captcha span").html(data.captcha);
            }
        });
    });
</script>