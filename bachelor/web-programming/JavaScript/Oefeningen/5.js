var voornaam = "";
var achternaam = "";
var password = "";
var control = "";
var email = "";
var vInOrde = false;
var aInOrde = false;
var pInOrde = false;
var cInOrde = false;
var eInOrde = false;

function checkVoornaam() {
	voornaam = document.getElementById("voornaam").value;
	voornaam.trim();
	if(voornaam.length > 30 || voornaam.length == 0)
		voornaamInvalid(1);
	for(var i = 0; i < voornaam.length; i++) {
		if(!((voornaam.charAt(i) >= 'a' && voornaam.charAt(i) <= 'z') || (voornaam.charAt(i) >= 'A' && voornaam.charAt(i) <= 'Z') || voornaam.charAt(i) == 'é' || voornaam.charAt(i) == 'è' || voornaam.charAt(i) == 'à'))
			voornaamInvalid(2);
	}

	voornaamValid();
	everythingValid();
}

function checkAchternaam() {
	achternaam = document.getElementById("achternaam").value;
	achternaam.trim();


	if(voornaam.length > 30 || voornaam.length == 0)
		achternaamInvalid(1);
	for(var i = 0; i < achternaam.length; i++) {
		if(!((achternaam.charAt(i) >= 'a' && achternaam.charAt(i) <= 'z') || (achternaam.charAt(i) >= 'A' && voornaam.charAt(i) <= 'Z') || achternaam.charAt(i) == 'é' || achternaam.charAt(i) == 'è' || achternaam.charAt(i) == 'à'))
			achternaamInvalid(2);
	}

	achternaamValid();
	everythingValid();
}

function checkPassword() {
	password = document.getElementById("password").value;
	if(password.length < 5)
		passwordInvalid();
	else
		passwordValid();
	everythingValid();
	checkControl();
}

function checkControl() {
	control = document.getElementById("pcontrol").value;

	if(control != password)
		controlInvalid();
	else
		controlValid();
	everythingValid();
}

function checkEmail() {
	email = document.getElementById("email").value;
	email.trim();

	var re = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
   
   	if(email.match(re))
		emailValid();
	else
		emailInvalid();
	everythingValid();
}

function voornaamValid() {
	document.getElementById("vorde").innerHTML = "De voornaam is in orde.";
	vInOrde = true;
}

function voornaamInvalid(int) {
	if(int == 1)
		document.getElementById("vorde").innerHTML = "De voornaam is te lang.";
	if(int == 2)
		document.getElementById("vorde").innerHTML = "Ongeldige karakters in voornaam.";
	vInOrde = false;
}

function achternaamValid() {
	document.getElementById("aorde").innerHTML = "De achternaam is in orde.";
	aInOrde = true;
}

function achternaamInvalid(int) {
	if(int == 1)
		document.getElementById("aorde").innerHTML = "De achternaam is te lang.";
	if(int == 2)
		document.getElementById("aorde").innerHTML = "Ongeldige karakters in achternaam.";
	aInOrde = false;
}

function passwordValid() {
	document.getElementById("porde").innerHTML = "Het wachtwoord is geldig";
	pInOrde = true;
}

function passwordInvalid() {
	document.getElementById("porde").innerHTML = "Het wachtwoord is te kort";
	pInOrde = false;
}

function controlValid() {
	document.getElementById("corde").innerHTML = "De wachtwoorden komen overeen.";
	cInOrde = true;
}

function controlInvalid() {
	document.getElementById("corde").innerHTML = "De wachtwoorden komen niet overeen.";
	cInOrde = false;
}

function emailValid() {
	document.getElementById("eorde").innerHTML = "De email is in orde.";
	eInOrde = true;
}

function emailInvalid() {
	document.getElementById("eorde").innerHTML = "De email is niet in orde.";
	eInOrde = false;
}

function everythingValid() {
	if(vInOrde && eInOrde && aInOrde && cInOrde && pInOrde)
		document.getElementById("submit").style.display = "block";
	else
		document.getElementById("submit").style.display = "none";
}
