<?php

if(isset($_POST['eventid']))
	$answer = deleteEvent();
else
	$answer = "Geen evenement doorgekregen.";

function deleteEvent() {
	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		return "Kon niet verbinden met de database.<br />";
	}

	$query = $conn->prepare("SELECT realpath FROM eventimages WHERE eventid = :eventid ;");
	$query->bindValue(':eventid', $_POST['eventid']);
	if($query->execute()) {
		while($row = $query->fetch(PDO::FETCH_BOTH)) {
			unlink($row['realpath']);
		}
	}

	$query = $conn->prepare("DELETE FROM event WHERE eventid = :eventid ;");
	$query->bindValue(':eventid', $_POST['eventid']);
	if($query->execute())
		return "Succesvol evenement verwijdert.";
	else
		return print_r($conn->errorInfo()) . "<br />Evenement niet kunnen verwijderen.<br />";
}
?>


<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<meta http-equiv='refresh' content='5;url=/~brentberghmans' />
	<title>Delete Event</title>
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