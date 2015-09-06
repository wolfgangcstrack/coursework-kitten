(function($) {
  $(document).ready(function() {
    $(window).scroll(function(event) {
      var height = $(window).scrollTop();
      $nav = $('#navbar');
      if (height >= 100) {
        $nav.addClass('navbar-fixed-top');
      } else {
        $nav.removeClass('navbar-fixed-top');
      }
    });
  });
})(jQuery);
