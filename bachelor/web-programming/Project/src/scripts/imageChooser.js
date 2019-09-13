
function changeBigImage(e) {
	document.getElementById('bigimage').innerHTML = "<img onclick=\"imageOverlay(this)\" src='" + e.getAttribute("src") + "' />";
}