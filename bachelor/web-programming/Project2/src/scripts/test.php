<?php
include '/home/brentberghmans/secure/DB_INFO.php';

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	return "Kon niet verbinden met de database.<br />";
}

$query = $conn->prepare("SELECT startdate FROM event;");
$query->execute();
$row = $query->fetch(PDO::FETCH_BOTH);

echo "SQL: " . strtotime($row['startdate']) . "<br />";
echo "PHP: " . mktime(0, 0, 0, 2, 16, 2015) . "<br />";
?>