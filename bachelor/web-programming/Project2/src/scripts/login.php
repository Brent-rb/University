<?php
$answer = checkLogin($_REQUEST['username'], $_REQUEST['password']);

function checkLogin($username, $password) {
	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		return "Kon niet verbinden met de database.<br />";
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
				return "Succesvol ingelod. <br />";
			}
		}
		else
			return "Geen gebruiker gevonden met de gegeven gebruikersnaam.<br />";
	}	
	else {
		return "Kon niet verbinden met de database.<br />";
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