<!DOCTYPE html>
<html>
<head>
	<title>Db</title>
</head>
<body>
<?php
try {
	$db_conn = new PDO("mysql:host=localhost;dbname=webpro", "root", "waxar");
}
catch (PDOException $e) {
	print "Error: ". $e->getMessage() . "\n";
	die();
}

$query = $db_conn->prepare("SELECT * FROM test");
$result_succes=$query->execute();
if($result_succes) {
	while($row = $query->fetch(PDO::FETCH_BOTH))
		echo $row['name'] . $row['age'];
}
else
die("Execute query error, because: " . $db_conn->errorInfo());

$db_conn = NULL;

?>
</body>
</html>