$("document").ready(function() {
  var navbar_links = '<a class="nav-link" href="#home-page">Home</a>' +
                     '<a class="nav-link" href="#favorites-page">Favorites</a>' +
                     '<a class="nav-link" href="#about-page">About</a>' +
                     '<a class="nav-link" href="#contact-page">Contact</a>';
  $('.aid-navbar').html(navbar_links);
});
$(document).ready(function() {
  $("#cis89a-form").validate({
    rules: {
      first:        { required: true },
      last:         { required: true },
      email:        { required: true },
      question:     { required: true }
    }
  });
});