<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<title>Hoofdcategorie Aanmaken</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div id="searchDiv">
		<?php 
		if(isset($_SESSION['rights']) && ($_SESSION['rights'] == "mod" || $_SESSION['rights'] == "admin")) {
		?>
		<form class="basic_form" method="POST" action="/~brentberghmans/src/scripts/createCat.php">
			<h2>Hoofdcategorie aanmaken</h2>
			<h4>Naam</h4>
			<input type='text' name='name' required/>
			<h4>Beschrijving</h4>
			<textarea name='description' required></textarea>
			<button type='submit'>Submit</button>
		</form>
		<?php
		}
		else
			echo "<div class='basic_textbox'>U heeft geen toegang</div>";
		?>
	</div>
</div>
<footer>
Footer Notes
TODO
</footer>

</body>
</html>