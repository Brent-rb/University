<!DOCTYPE html>
<html>
<head>
	<script src="/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/styles/style.css" type="text/css" /> 
	<title>Home</title>
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