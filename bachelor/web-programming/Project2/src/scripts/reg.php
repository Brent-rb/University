<?php
$answer = "";
$correct = true;

if((checkUserName($_REQUEST['username'], 5))) {

}
else {
	$correct = false;
	$answer .= "Gebruikersnaam is fout, enkel alfanumerieke karakters, minimum 5 letters.<br />";
}

if(checkPassword($_REQUEST['password'], $_REQUEST['control'], 5)) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "Wachtwoord is fout of wachtwoorden komen niet overeen, enkel alfanumerieke karakters (en _) en minimaal 5 letters.<br />";
}

if(checkName($_REQUEST['voornaam'], 2)) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "Voornaam is fout, enkel alfanumerieke karakters en spaties, minstens 2 letters.<br />";
}

if(checkName($_REQUEST['achternaam'], 2)) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "Achternaam is fout, enkel alfanumerieke karakters en spaties, minstens 2 letters.<br />";
}

if((int)calAge($_REQUEST['birthdate']) >= 13) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "Geboortedatum incorrect, u moet minimaal 13 jaar zijn.<br />";
}

if(checkStreet($_REQUEST['street'], 2)) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "De straat is fout, enkel alfanumerieke karakters en spaties, minstens 2 letters.<br />";
}

if(checkStreet($_REQUEST['city'], 2)) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "De stad is fout, enkel alfanumerieke karakters en spaties, minstens 2 letters.<br />";
}

if($_REQUEST['postcode'] > 0) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "Postcode is fout.<br />";
}

if(checkMail($_REQUEST['email'])) {
	$correct &= true;
}
else {
	$correct = false;
	$answer .= "Email is fout.<br />";
}

if($correct) {
	$nameTaken = false;
	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		$answer = $answer . "Kon niet verbinden met de database.<br />";
		die();
	}

	$query = $conn->query('SELECT username FROM users');

	$fetch = $query->fetchAll(PDO::FETCH_BOTH);

	foreach($fetch as $row) {
		if($_REQUEST['username'] == $row['username'])
			$nameTaken = true;
	}
	
	if(!$nameTaken) {

		
		$salt = mcrypt_create_iv(32, MCRYPT_DEV_URANDOM);

		$hashed = crypt($_REQUEST['password'], $salt);

		$hashed = base64_encode($hashed);
		$salt = base64_encode($salt);
		
		$query = $conn->prepare("INSERT INTO users (Username, Password, Salt, Rights) VALUES (:username, :password, :salt, :user) RETURNING UserID;");
		$query->bindValue(':username', $_REQUEST['username']);
		$query->bindValue(':salt', $salt);
		$query->bindValue(':password', $hashed);
		$rights = "user";
		$query->bindValue(':user', $rights);
		
		if($query->execute()) {
			$id = $conn->lastInsertId('users_userid_seq');
			
			if(isset($_FILES))
				$avatar = uploadAvatar($id);
			else
				$avatar = "/~brentberghmans/img/avatars/default.jpg";

			$query = $conn->prepare("INSERT INTO userInfo (UserID, Voornaam, Achternaam, geboorte, Straat, Stad, Postcode, Email, avatar) VALUES (:id, :vnaam, :anaam, :geboorte, :street, :city, :postcode, :email, :avatar);");
			$query->bindValue(':id', (int)$id);
			$query->bindValue(':vnaam', $_REQUEST['voornaam']);
			$query->bindValue(':anaam', $_REQUEST['achternaam']);
			$query->bindValue(':geboorte', $_REQUEST['birthdate']);
			$query->bindValue(':street', $_REQUEST['street']);
			$query->bindValue(':city', $_REQUEST['city']);
			$query->bindValue(':postcode', $_REQUEST['postcode']);
			$query->bindValue(':email', $_REQUEST['email']);
			$query->bindValue(':avatar', $avatar);
			if($query->execute())
				$answer = $answer . "Succesvol geregistreerd.<br />";
			else
				$answer = $answer . "Er is iets misgegaan bij het uploaden van de gegevens. Probeer later nog eens.<br />";

		}
		else {
			$answer = $answer . "Kon de gegeven query niet uitvoeren.<br />";
		}

	}
	else {
		$answer = $answer . "De opgegeven username is al bezet.<br />";
	}

}

function uploadAvatar($id) {
	$valid_formats = array("jpg", "png", "gif", "bmp");
	//$max_file_size = 1024*1000*20;
	$path = "/home/brentberghmans/public_html/img/avatars/";
	$default = "/~brentberghmans/img/avatars/default.jpg";
	$ext = pathinfo($_FILES['avatar']['name'], PATHINFO_EXTENSION);


	//Als er errors zijn of filesize is te groot. if($_FILES['avatar']['error'] > 0 || $_FILES['avatar']['size'] > $max_file_size || !(in_array($ext, $valid_formats))) {
	if($_FILES['avatar']['error'] > 0 || !(in_array($ext, $valid_formats))) {
		return $default;
	}
	
	$realPath = $path . $id . "." . $ext;
	$htmlPath = "/~brentberghmans/img/avatars/" . $id . "." . $ext;

	if(move_uploaded_file($_FILES['avatar']['tmp_name'], $realPath)){
		return $htmlPath;
	}
	else {
		return $default;
	}
}

function checkName($name, $length) {
	$regexp = "/^[a-zA-Z0-9 ]{" . $length . ",}$/";
	return preg_match($regexp, $name);
}


function checkUserName($name, $length) {
	$regexp = "/^[a-zA-Z0-9]{" . $length . ",}$/";
	return preg_match($regexp, $name);
}


function checkPassword($password, $control, $length) {
	$regexp = "/^[a-zA-Z0-9_]{" . $length . ",}$/";
	return (preg_match($regexp, $password) && ($password == $control));
}

function checkMail($mail) {
	$regexp = "/^[^0-9][A-z0-9_]+([.][A-z0-9_]+)*[@][A-z0-9_]+([.][A-z0-9_]+)*[.][A-z]{2,4}$/";
	return preg_match($regexp, $mail);
}

function checkStreet($name, $length) {
	$regexp = "/^[a-zA-Z0-9 ]{" . $length . ",}$/";
	return preg_match($regexp, $name);
}

function calAge($dob){
	//timestamp omzetten naar datum
    $dob = date("Y-m-d", strtotime($dob));
    //Datum object aanmaken voor nu en voor de geboortedatum
    $dobObject = new DateTime($dob);
    $nowObject = new DateTime();
    //Verschil berekenen
    $diff = $dobObject->diff($nowObject);
    //Leeftijd teruggeven.
    return $diff->format('%y');

}
?>

<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<meta http-equiv='refresh' content='5;url=/~brentberghmans/' />
	<title>Registreren</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div class="basic_textbox">
		<?php
		echo $answer;
		echo "<a href='/~brentberghmans/'>U wordt doorverwezen naar de start pagina, klik hier als dit niet gebeurd in 5 seconden.</a>";
		?>
	</div>
</div>
</body>
</html>