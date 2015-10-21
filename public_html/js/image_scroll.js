$(document).ready(function() {
	var img_array = [];

	$("#image_scroll img").each(function(index) {
		img_array[index] = {};
		img_array[index][$(this).attr("src")] = $(this).attr("id");
	});

	$("#right-scroll-button").click(function() {
		$img1 = $("#image_scroll img:eq(0)");
		$img2 = $("#image_scroll img:eq(1)");
		$img3 = $("#image_scroll img:eq(2)");

		var first_src = $img1.attr("src");
		var first_id = $img1.attr("id");

		$img1.attr("src", $img2.attr("src"));
		$img1.attr("id",  $img2.attr("id"));
		$img2.attr("src", $img3.attr("src"));
		$img2.attr("id",  $img3.attr("id"));
		$img3.attr("src", first_id);
		$img3.attr("id",  first_src);
	});
});
