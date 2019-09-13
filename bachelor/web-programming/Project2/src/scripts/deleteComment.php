<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<meta name="viewport" content="width=device-width" />
	<title>Delete comment</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div class='basic_textbox'>
		<?php

		

		if(!isset($_SESSION['rights']) || ($_SESSION['rights'] != "mod" && $_SESSION['rights'] != "admin")) {
			echo "Geen toegang";
			return;
		}

		include '/home/brentberghmans/secure/DB_INFO.php';

		//Connectie maken met DB
		try {
			$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
		}
		catch (PDOException $e) {
			return "dberror";
		}

		$query = $conn->prepare("DELETE FROM comments WHERE commentid = :commentid ;");
		$query->bindValue(':commentid', $_POST['commentid']);

		if($query->execute())
			header('Location: /~brentberghmans/event/?eventid=' . $_POST['eventid']);
		else {
			echo "Er is iets mis gegaan bij het aanpassen";
			print_r($conn->errorInfo());
		}




		?>

	</div>
</div>
</body>
</html>

