
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
	$query = $conn->prepare("INSERT INTO hoofdcat(name, description) VALUES (:name, :description)");
	$query->bindValue(':name', htmlentities($_POST['name']));
	$query->bindValue(':description', htmlentities($_POST['description']));
	if($query->execute())
		header('Location: /~brentberghmans/hoofdcat/create.php')
	else {
		echo "Categorie toevoegen is mislukt.<br />";
		print_r($conn->errorInfo());
	}
}
?>