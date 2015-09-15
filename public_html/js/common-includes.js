/*
This script takes away the repetitiveness of copy/pasting common link and
script tags (considering this class is not about using a dynamic backend
language like Python or PHP).
*/

(function() {
  var cssURLs = [
    // local
    'css/theme.css',
    'css/bootstrap-social.css',
    // remote
    'https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css',
    'https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css'
  ];

  var jsURLs = [
    // local
    'js/navbar-scroll.js',
    // remote
    'https://code.jquery.com/jquery-2.1.4.min.js'
  ];

  var loadCSS = function(url) {
    var stylesheet = document.createElement('link');
    stylesheet.href = url;
    stylesheet.rel = 'stylesheet';
    stylesheet.type = 'text/css';
    document.getElementsByTagName('head')[0].appendChild(stylesheet);
  };

  var loadJS = function(url) {
    var script = document.createElement('script');
    script.src = url;
    script.type = 'text/javascript';
    script.charset = 'utf-8';
    document.getElementsByTagName('head')[0].appendChild(script);
  };

  cssURLs.forEach(function(url) { loadCSS(url); });
})();
