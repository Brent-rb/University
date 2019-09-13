<?php
$correct = (checkName($_REQUEST['username'], 5));

if($correct)
	$correct = checkPassword($_REQUEST['password'], $_REQUEST['control'], 5);
if($correct)
	$correct = checkName($_REQUEST['voornaam'], 2);
if($correct)
	$correct = checkName($_REQUEST['achternaam'], 2);
if($correct)
	$correct = ($_REQUEST['age'] >= 13);
if($correct)
	$correct = checkStreet($_REQUEST['street'], 2);
if($correct)
	$correct = checkStreet($_REQUEST['city'], 2);
if($correct)
	$correct = ($_REQUEST['postcode'] > 0);
if($correct)
	$correct = checkMail($_REQUEST['email']);

if($correct) {
	$nameTaken = false;
	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
		echo "Connected<br />";
	}
	catch (PDOException $e) {
		echo "Failed to connect to the database.\n";
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

			$query = $conn->prepare("INSERT INTO userInfo (UserID, Voornaam, Achternaam, Leeftijd, Straat, Stad, Postcode, Email, avatar) VALUES (:id, :vnaam, :anaam, :age, :street, :city, :postcode, :email, :avatar);");
			$query->bindValue(':id', (int)$id);
			$query->bindValue(':vnaam', $_REQUEST['voornaam']);
			$query->bindValue(':anaam', $_REQUEST['achternaam']);
			$query->bindValue(':age', (int)$_REQUEST['age']);
			$query->bindValue(':street', $_REQUEST['street']);
			$query->bindValue(':city', $_REQUEST['city']);
			$query->bindValue(':postcode', $_REQUEST['postcode']);
			$query->bindValue(':email', $_REQUEST['email']);
			$query->bindValue(':avatar', $avatar);
			if($query->execute())
				echo "Succesfully added everything<br />";
			else
				print_r($conn->errorinfo());

		}
		else {
			echo "Error with uploading to database.";
			print_r($conn->errorInfo());
		}

	}
	else {
		echo "Duplicate name.\n";
	}

}
else {
	echo "Input is foutief.\n";
}

function uploadAvatar($id) {
	$valid_formats = array("jpg", "png", "gif", "bmp");
	$max_file_size = 1024*1000*20;
	$path = "/home/brentberghmans/public_html/img/avatars/";
	$default = "/~brentberghmans/img/avatars/default.jpg";

	echo "Started avatar upload.";
	$ext = pathinfo($_FILES['avatar']['name'], PATHINFO_EXTENSION);


	//Als er errors zijn of filesize is te groot of 
	if($_FILES['avatar']['error'] > 0 || $_FILES['avatar']['size'] > $max_file_size || !(in_array($ext, $valid_formats))) {
		echo "" . $_FILES['avatar']['error'] . "<br />";
		echo "Failed to upload avatar <br/>";
		return $default;
	}
	
	$realPath = $path . $id . "." . $ext;
	$htmlPath = "/~brentberghmans/img/avatars/" . $id . "." . $ext;

	if(move_uploaded_file($_FILES['avatar']['tmp_name'], $realPath)){
		echo "Uploaded avatar";
		return $htmlPath;
	}
	else {
		echo "Shit happened";
		return $default;
	}
}

function checkName($name, $length) {
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

//header('Location: /~brentberghmans/');
die();

?>
