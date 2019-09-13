
function imageOverlay(e) {
	var imageDiv = document.getElementById('imageOverlay');
	imageDiv.innerHTML = "<span class=\"centerHelper\"></span><img src='" + e.getAttribute("src") + "' />";
	imageDiv.style.display = "inline-block";
}

function imageOverlayGone() {
	document.getElementById('imageOverlay').style.display = "none";
}