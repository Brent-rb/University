<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/generalStyle.css" type="text/css" /> 
	<title>Logout</title>
</head>
<body>
<?php
include "/home/brent/Documents/localhost/src/scripts/header.php";
?>
<div id="content">
	<?php
	session_start();
	if(isset($_SESSION['username'])) {
		session_destroy();
		echo "<div class=\"basic_textbox\">U bent succesvol uitgelogd, u wordt verwezen naar de pagina waar u van kwam.</div>";
	}
	else
		echo "<div class=\"basic_textbox\">U bent niet ingelogd, u wordt verwezen naar de pagina waar u van kwam.</div>";

	header('Location: /~brentberghmans/');
	die();
	?>
</div>
<footer>
Footer Notes
TODO
</footer>

</body>
</html>