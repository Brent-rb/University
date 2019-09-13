<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<title>Registreren</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<form class="basic_form" action="/~brentberghmans/src/scripts/reg.php" method="post" enctype="multipart/form-data">
		<h2>Registreren</h2>
		<h4>Username</h4>
		<input type="text" name="username" required />
		<h4>Password</h4>
		<input type="password" name="password" required />
		<h4>Herhaal passsword</h4>
		<input type="password" name="control" required />
		<h4>Voornaam</h4>
		<input type="text" name="voornaam" required />
		<h4>Achternaam</h4>
		<input type="text" name="achternaam" required />
		<h4>Geboorte datum</h4>
		<input type="date" name="birthdate" required />
		<h4>Straat</h4>
		<input type="text" name="street" required />
		<h4>Stad/Dorp</h4>
		<input type="text" name="city" required />
		<h4>Postcode</h4>
		<input type="number" name="postcode" required />
		<h4>Email</h4>
		<input type="email" name="email" required />
		<h4>Avatar</h4>
		<input type="file" name="avatar" /><br />
		<input type="submit" />
	</form>
</div>


<footer>
Footer Notes
TODO
</footer>

</body>
</html>