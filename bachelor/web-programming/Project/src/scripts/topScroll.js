function checkScroll() {
	var rem = parseFloat(getComputedStyle(document.documentElement).fontSize);
	if(window.pageYOffset >= (rem * 7)) {
		document.getElementById("menubar").style.position = "fixed";
		document.getElementById("menubar").style.top = "0";
	}
	else {
		document.getElementById("menubar").style.position = "relative";
	}
}

window.onscroll = checkScroll;


