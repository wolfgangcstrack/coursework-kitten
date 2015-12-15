(function() {
  /**
   * All functions defined in this file besides defer_jQuery are called in
   * this main function. Any jQuery/DOM manipulation functions are called
   * within a $(document).ready callback function.
   */
  function main($) {
    // insert all common CSS stylesheets
    insert_common_includes();

    // jQuery/DOM related functions called in here
    $(document).ready(function() {
      execute_jquery_ui();
      execute_jquery_validation();
      execute_jquery_other();
    });
  }

  /**
   * This function uses jQuery and AJAX to dynamically insert CSS
   * stylesheets that can be considered common to a majority of the pages
   * on the website.
   */
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

  /**
   * This function executes any related jQuery UI functionality for the
   * page. Everything related to jQuery UI should be executed within here.
   */
  function execute_jquery_ui() {
    $('#tabs').tabs();
  }

  /**
   * This function executes any related jQuery validation functionality
   * for the page. Everything related to jQuery validation should be
   * executed within here.
   */
  function execute_jquery_validation() {
    $("#cs-175-form").validate({
      rules: {
        first:        { required: true },
        last:         { required: true },
        email:        { required: true },
        question:     { required: true }
      }
    });
  }

  /**
   * This function executes any other related jQuery functionality that is
   * not covered in its own function above. Everything else related to
   * jQuery that is not in the functions above should executed within
   * here.
   */
  function execute_jquery_other() {
    $('#home tr').hover(function() {
      $(this).addClass('tr_focus');
    }, function() {
      $(this).removeClass('tr_focus');
    });

    $('.nav-link').hover(function() {
      $(this).addClass('nav_link_focus');
    }, function() {
      $(this).removeClass('nav_link_focus');
    });
  }

  /**
   * This function is used to execute main ONLY after jQuery has been
   * successfully loaded to the document; jQuery is included in its own
   * script tag within the HTML document.
   */
  function defer_jQuery(method) {
    if (window.jQuery)
       method(jQuery);
    else
      setTimeout(function() { defer_jQuery(method); }, 50);
  }

  defer_jQuery(main);
})();