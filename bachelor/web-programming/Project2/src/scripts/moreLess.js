
function initMoreLess() {
	var array = document.getElementsByClassName("moreLess");
	var tempArray;

	for(var i = 0; i < array.length; i++) {
		array[i].innerHTML = "<a onclick='more(this)'>Toon meer</a>";
	}

	array = document.getElementsByClassName("mid_post");

	for(var i = 0; i < array.length - 1; i++) {
		tempArray = array[i].getElementsByTagName("p");
		for(var j = 0; j < tempArray.length; j++) {
			tempArray[j].style.maxHeight = "200px";
		}
	}

	array = document.getElementsByClassName("big_post");
	for(var i = 0; i < array.length; i++) {
		tempArray = array[i].getElementsByTagName("p");
		for(var j = 0; j < tempArray.length; j++) {
			tempArray[j].style.maxHeight = "200px";
		}
	}

	array = document.getElementsByTagName("iframe");
	for(var i = 0; i < array.length; i++) {
		array[i].style.display = "none";
	}
}


function more(element) {
	var parent = element.parentNode.parentNode;
	var array = parent.getElementsByTagName("p");

	for(var i = 0; i < array.length; i++)
		array[i].style.maxHeight = "none";

	var array = parent.getElementsByTagName("iframe");
	for(var i = 0; i < array.length; i++)
		array[i].style.display = "inline-block";

	element.parentNode.innerHTML = "<a onclick='less(this)'>Toon Minder</a>";
}

function less(element) {
	var parent = element.parentNode.parentNode;
	var array = parent.getElementsByTagName("p");

	for(var i = 0; i < array.length; i++)
		array[i].style.maxHeight = "200px";

	var array = parent.getElementsByTagName("iframe");
	for(var i = 0; i < array.length; i++)
		array[i].style.display = "none";

	element.parentNode.innerHTML = "<a onclick='more(this)'>Toon Meer</a>";
}