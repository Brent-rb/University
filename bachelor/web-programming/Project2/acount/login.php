<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<link rel="stylesheet" href="/~brentberghmans/styles/loginStyle.css" type="text/css" />
	<title>Login</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<form class="basic_form" action="/~brentberghmans/src/scripts/login.php" method="post">
		<h2>Inloggen</h2>
		<h4>Username</h4>
		<input type="text" name="username" required />
		<h4>Password</h4>
		<input type="password" name="password" required /><br />
		<input type="submit" />
	</form>
</div>


<footer>
Footer Notes
TODO
</footer>

</body>
</html>