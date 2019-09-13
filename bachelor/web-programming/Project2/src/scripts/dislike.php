<?php
include '/home/brentberghmans/secure/DB_INFO.php';

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	return "Kon niet verbinden met de database.<br />";
}

$query = $conn->prepare("DELETE FROM likes WHERE eventid = :eventid AND userid = :userid;");

$query->bindValue(':eventid', $_POST['eventid']);
$query->bindValue(':userid', $_POST['userid']);

if($query->execute())
	header('Location: ' . $_REQUEST['url']);
else
	print_r($conn->errorInfo());

?>

