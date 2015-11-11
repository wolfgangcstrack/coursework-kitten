$(document).ready(function() {
	$("#first").focus();
	
	$("#mm_webinput").validate({
		rules: {
		},
		messages: {
			email_2: {
				equalTo: "This entry must equal previous entry."
			},
		}
	}); // end validate
}); // end ready
