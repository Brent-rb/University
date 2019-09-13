<?php
include '/home/brentberghmans/secure/DB_INFO.php';

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	echo "Failed to connect to the database.\n";
}

if(isset($_POST['delete'])) {
	$query = $conn->prepare("DELETE FROM subcat WHERE subid = :subid ;");
	$query->bindValue(':subid', $_POST['subid']);
	$query->execute();
	
}
else {
	$query = $conn->prepare("UPDATE subcat SET name = :name, hoofdid = :hoofdid WHERE subid = :subid ;");
	$query->bindValue(':subid', $_POST['subid']);
	$query->bindValue(':name', htmlentities($_POST['name']));
	$query->bindValue(':hoofdid', $_POST['hoofdid']);
	$query->execute();
}


header('Location: /~brentberghmans/subcat/edit.php');


?>