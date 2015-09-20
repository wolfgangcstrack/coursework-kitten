(function() {
  // function defer_jQuery(method) {
  //   if (window.jQuery)
  //      method(jQuery);
  //   else
  //     setTimeout(function() { defer_jQuery(method); }, 50);
  // }
  function main($) {
    $(document).ready(function() {
      $('body').append(
        '<footer>' +
          '<hr class="divider">' +
          '<p class="email">' +
            '<div class="left-column text-bold vertical-center">Email Me: <a href="mailto:wolfgangcstrack@gmail.com">wolfgangcstrack@gmail.com</a></div>' +
          '</p>' +
          '<div class="right-column text-right text-gray text-bold">' +
            '<p>' +
              '<a href="https://www.linkedin.com/in/wolfgangcstrack" class="btn btn-social-icon btn-linkedin" title="LinkedIn">' +
                '<i class="fa fa-linkedin"></i>' +
              '</a>' +
              '<a href="https://github.com/vulfgang" class="btn btn-social-icon btn-github" title="GitHub">' +
                '<i class="fa fa-github"></i>' +
              '</a>' +
              '<a href="https://bitbucket.org/vulfgang/" class="btn btn-social-icon btn-bitbucket" title="BitBucket">' +
                '<i class="fa fa-bitbucket"></i>' +
              '</a>' +
              '<a href="https://www.facebook.com/wolfgangchristian.strack" class="btn btn-social-icon btn-facebook" title="Facebook">' +
                '<i class="fa fa-facebook"></i>' +
              '</a>' +
            '</p>' +
          '</div>' +
      '</footer>' +
      '<br><br>'
      );
    });
  }

  defer_jQuery(main);
})();
