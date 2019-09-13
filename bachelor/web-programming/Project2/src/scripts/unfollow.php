<?php
session_start();

if(!isset($_SESSION['userid']))
	if(isset($_POST['targetid']))
		header('Location: /~brentberghmans/acount/?userid=' . $_POST['targetid']);
	else
		header('Location: /~brentberghmans/acount/');

include '/home/brentberghmans/secure/DB_INFO.php';

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	return "Kon niet verbinden met de database.<br />";
}

$query = $conn->prepare("DELETE FROM followers WHERE baseid = :baseid AND targetid = :targetid;");
$query->bindValue(':baseid', $_POST['baseid']);
$query->bindValue(':targetid', $_POST['targetid']);

if($query->execute()) {
	header('Location: /~brentberghmans/acount/?userid=' . $_POST['targetid']);
}
else {
	print_r($conn->errorInfo());
}

?>