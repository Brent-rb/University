
<?php
include '/home/brentberghmans/secure/DB_INFO.php';

//Connectie maken
try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	echo "Failed to connect to the database.\n";
}

if(isset($_POST['name'])) {
	$query = $conn->prepare("INSERT INTO subcat(name, hoofdid) VALUES (:name, :hoofdid)");
	$query->bindValue(':name', htmlentities($_POST['name']));
	$query->bindValue(':hoofdid', $_POST['hoofdid']);
	if($query->execute())
		header('Location: /~brentberghmans/subcat/create.php');
	else {
		echo "Categorie toevoegen is mislukt.<br />";
		print_r($conn->errorInfo());
	}
}
?>