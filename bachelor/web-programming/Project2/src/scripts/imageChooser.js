
function disableAnchors(e) {
	var array = document.getElementsByClassName('changeImageFallback');

	for(var i = 0; i < array.length; i++) {
		array[i].removeAttribute("href");
	}
}

function changeBigImage(e) {
	document.getElementById('bigimage').innerHTML = "<img onclick=\"imageOverlay(this)\" src='" + e.getAttribute("src") + "' />";
}