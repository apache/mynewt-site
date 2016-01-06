$('.show-sidebar').click(function() {

    $('.sidebar-container').toggle();
    $(this).toggleClass('active');
    
    if ($('.sidebar-container').is(':visible')) {

        $(this).text('Close Docs Menu');

    } else {

        $(this).text('Docs Menu');

    }

});