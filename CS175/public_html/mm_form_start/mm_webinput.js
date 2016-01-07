$(document).ready(function() {
  $("#first").focus();
  $("#mm_webinput").validate({
    rules: {
      first:      { required: true },
      last:       { required: true },
      "class":    { required: true },
      semester:   { required: true },
      year:       { required: true },
      instructor: { required: true },
      software:   { required: true },
      ID_number: {
        required: true,
        digits: true,
        rangelength: [6,6]
      },
      email: {
        required: true,
        email: true
      },
      email_2: {
        equalTo: "#email"
      },
      phone: {
        required: true,
        phoneUS: true
      }
    },

    messages: {
      email_2: {
        equalTo: "The emails you have entered do not match."
      },
      ID_number: {
        rangelength: "Please enter an ID of 6 digits"
      }
    }
  }); // end validate
}); // end ready
