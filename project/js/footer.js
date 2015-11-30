(function() {
  function main($) {
    $(document).ready(function() {
      $('body').append(
        '<footer>' +
          '<hr class="divider">' +
          '<p class="email">' +
            '<div class="left-column text-bold vertical-center">Questions? <a href="#contact">Contact.</a></div>' +
          '</p>' +
          '<div class="right-column text-right text-gray text-bold">' +
            '<p>' +
              '<a href="#" class="btn btn-social-icon btn-linkedin" title="LinkedIn">' +
                '<i class="fa fa-linkedin"></i>' +
              '</a>' +
              '<a href="#" class="btn btn-social-icon btn-github" title="GitHub">' +
                '<i class="fa fa-github"></i>' +
              '</a>' +
              '<a href="#" class="btn btn-social-icon btn-bitbucket" title="BitBucket">' +
                '<i class="fa fa-bitbucket"></i>' +
              '</a>' +
              '<a href="#" class="btn btn-social-icon btn-facebook" title="Facebook">' +
                '<i class="fa fa-facebook"></i>' +
              '</a>' +
            '</p>' +
          '</div>' +
      '</footer>' +
      '<br><br>'
      );
    });
  }

  defer_jQuery(main); // global function in common-includes.js
})();
