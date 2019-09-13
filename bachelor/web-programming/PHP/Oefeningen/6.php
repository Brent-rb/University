<!DOCTYPE html>
<html>
<head>
	<style>
	#table {
		width: 100%;
		background-color: grey;
	}

	#table tr:first-child {
		background-color: white;
		font-size: 20px;
	}
	</style>
	<title>Oef6</title>
</head>
<body>
<table id="table" border="1px">
	<tr>
		<td>Voornaam</td>
		<td>Achternaam</td>
		<td>Leeftijd</td>
	</tr>
<?php
try {
	$db_conn = new PDO("mysql:host=localhost;dbname=webpro", "root", "waxar");
}
catch (PDOException $e) {
	print "Error: ". $e->getMessage() . "\n";
	die();
}

$query = $db_conn->prepare("SELECT * FROM oef6");
$result_succes=$query->execute();
if($result_succes) {
	while($row = $query->fetch(PDO::FETCH_BOTH)) {
		echo "<tr>";
		echo "<td>" . $row['voornaam'] . "</td>";
		echo "<td>" . $row['achternaam'] . "</td>";
		echo "<td>" . $row['leeftijd'] . "</td>";
		echo "</tr>";
	}

}
else
die("Execute query error, because: " . $db_conn->errorInfo());

$db_conn = NULL;

?>
</table>
</body>
</html>