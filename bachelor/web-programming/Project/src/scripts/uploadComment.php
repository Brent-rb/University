<?php
include '/home/brentberghmans/secure/DB_INFO.php';

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	return "dberror";
}

$query = $conn->prepare("INSERT INTO comments(userid, eventid, content) VALUES ( :userid , :eventid , :content );");
$query->bindValue(':userid', $_REQUEST['userid']);
$query->bindValue(':eventid', $_REQUEST['eventid']);
$query->bindValue(':content', addslashes($_REQUEST['content']));

if($query->execute())
	header('Location: ' . $_REQUEST['url']);
else
	echo 'Error';

?>