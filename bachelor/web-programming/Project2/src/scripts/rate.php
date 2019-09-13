<?php 
//Login info includen
include '/home/brentberghmans/secure/DB_INFO.php';

//Connectie maken met DB
try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	return "dberror";
}

$query = $conn->prepare("INSERT INTO ratings (userid, eventid, rating) VALUES (:userid, :eventid, :rating) ");
$query->bindValue(':userid', $_POST['userid']);
$query->bindValue(':eventid', $_POST['eventid']);
$query->bindValue(':rating', $_POST['rating']);
$query->execute();

header('Location: /~brentberghmans/event/?eventid=' . $_POST['eventid']);

?>