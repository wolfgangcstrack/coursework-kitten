$(document).ready(function() {
	var img_elements = $("#image_scroll img");
	var src_array = [];

	// store all image src in an array
	for (var i = 0; i < img_elements.length; i++) {
		var offset_index = i + img_elements.length;
		src_array[i] = $(img_elements[i]).attr('src');
		src_array[offset_index] = $(img_elements[i]).attr('id');
	}

	// set images in proper (different) format for scrolling
	$("#image_scroll img").each(function(index) {
		$(this).attr('src', src_array[index]);
		$(this).attr('id', "scroll-image-"+index);
	});

	// scrolling power!!!!!!!
	$("#right-scroll-button").click(function() {
		$("#image_scroll img").each(function(index) {
			var img_num = parseInt($(this).attr('id').slice(-1)) + 1;
			
			if (img_num >= src_array.length) {
				img_num = 0;
			}

			$(this).attr('src', src_array[img_num]);
			$(this).attr('id', "scroll-image-"+img_num);
		});
	});
});
