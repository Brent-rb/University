<?php

$inlog = checkLogin($_REQUEST['username'], $_REQUEST['password']);

function checkLogin($username, $password) {
	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		return "dberror";
	}

	$query = $conn->prepare("SELECT * FROM users WHERE Username = :username ;");
	$query->bindValue(':username', $username);

	if($query->execute()) {
		if($row = $query->fetch(PDO::FETCH_BOTH)) {
			$salt = base64_decode($row['salt']);
			$db_password = base64_decode($row['password']);
			$rights = $row['rights'];
			$id = $row['userid'];

			if(crypt($password, $salt) == $db_password) {
				startSession($username, $id, $rights);
				return "succes";
			}
		}
		else
			return "inerror";
	}	
	else {
		return "dberror";
	}
}


function startSession($username, $id, $rights) {
	if(isset($_SESSION['userid']))
		session_destroy();
	session_start();

	$_SESSION['userid'] = $id;
	$_SESSION['username'] = $username;
	$_SESSION['rights'] = $rights;
}

if($inlog == "dberror")
	echo "Could not connect to DB<br />";
else if($inlog == "inerror")
	echo "Username or password is incorrect<br />";
else if($inlog == "succes")
	echo "Succesvol ingelogd.<br />";

header("Location: /~brentberghmans/");
die();

?>