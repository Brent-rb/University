function onSub() {
	var num1 = parseInt(document.getElementById("numberOne").value);
	var num2 = parseInt(document.getElementById("numberTwo").value);
	
	document.getElementById("outputField").innerHTML = "Uitkomst is: " + (num1 + num2);
}
