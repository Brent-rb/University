<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<link rel="stylesheet" href="/~brentberghmans/styles/calendarStyle.css" type="text/css" />
	<meta name="viewport" content="width=device-width" />
	<title>Kalender</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";

include '/home/brentberghmans/secure/DB_INFO.php';
include '/home/brentberghmans/public_html/src/scripts/calendar.php';

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	return "Kon niet verbinden met de database.<br />";
}

if(daySet()) {
	if(monthSet()) {
		if(yearSet())
			printDay($conn, (int)$_REQUEST['day'], (int)$_REQUEST['month'], (int)$_REQUEST['year']);
		else
			printDay($conn, (int)$_REQUEST['day'], (int)$_REQUEST['month'], (int)date('Y'));
	}
	else
		printDay($conn, (int)$_REQUEST['day'], (int)date('m'), (int)date('Y'));
}
else if(monthSet()) {
	if(yearSet()) 
		printMonth($conn, (int)$_REQUEST['month'], (int)$_REQUEST['year']);
	else
		printMonth($conn, (int)$_REQUEST['month'], (int)date('Y'));
}
else
	printMonth($conn, (int)date('m'), (int)date('Y'));


function yearSet() {
	return(isset($_REQUEST['year']) && $_REQUEST['year'] != null);
}

function monthSet() {
	return(isset($_REQUEST['month']) && $_REQUEST['month'] != null);
}

function daySet() {
	return(isset($_REQUEST['day']) && $_REQUEST['day'] != null);
}

?>
</body>
</html>
