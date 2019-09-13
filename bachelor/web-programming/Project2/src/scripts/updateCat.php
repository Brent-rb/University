<?php
include '/home/brentberghmans/secure/DB_INFO.php';

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	echo "Failed to connect to the database.\n";
}

if(isset($_POST['delete'])) {
	$query = $conn->prepare("DELETE FROM hoofdcat WHERE hoofdid = :hoofdid ;");
	$query->bindValue(':hoofdid', $_POST['hoofdid']);
	$query->execute();
}
else {
	if($_POST['description'] != null)
		$query = $conn->prepare("UPDATE hoofdcat SET name = :name, description = :description WHERE hoofdid = :hoofdid ;");
	else
		$query = $conn->prepare("UPDATE hoofdcat SET name = :name WHERE hoofdid = :hoofdid ;");
	$query->bindValue(':hoofdid', $_POST['hoofdid']);
	$query->bindValue(':name', htmlentities($_POST['name']));
	if($_POST['description'] != null)
		$query->bindValue(':description', htmlentities($_POST['description']));
	if($query->execute())
		echo "Aanpassen gelukt.<br />";
	else
		echo "Aanpassen mislukt.<br />";
}


header('Location: /~brentberghmans/hoofdcat/edit.php');


?>