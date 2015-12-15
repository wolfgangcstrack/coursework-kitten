(function() {
  function defer_jQuery(method) {
    if (window.jQuery)
       method(jQuery);
    else
      setTimeout(function() { defer_jQuery(method); }, 50);
  }

  function main($) {
    insert_common_includes();

    $(document).ready(function() {
      $('#tabs').tabs();
      $("#cis89a-form").validate({
        rules: {
          first:        { required: true },
          last:         { required: true },
          email:        { required: true },
          question:     { required: true }
        }
      });
    });
  }

  function insert_common_includes() {
    var cssURLs = [
    './css/theme.css',
    './css/bootstrap-social.css',
    'https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css',
    'https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css'
    ];

    function append_css(data) {
      $('<style type="text/css">\n' + data + '</style>').appendTo("head");
    }

    for (var i = 0; i < cssURLs.length; i++) {
      $.ajax({
        url: cssURLs[i],
        dataType: 'text',
        success: append_css
      });
    }
  }

  defer_jQuery(main);
})();