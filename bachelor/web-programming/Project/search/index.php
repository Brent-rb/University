<!DOCTYPE html>
<html>
<head>
	<script src="/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/styles/style.css" type="text/css" /> 
	<title>Search</title>
</head>
<body>
<?php
include "/home/brent/Documents/localhost/src/scripts/header.php";
?>
<div id="content">
	<div id="searchDiv">
		<!-- nog niet functioneel, en TODO: meer filter opties -->
		<form id="filterform">
			<h2>Search</h2>
			<h4>Naam</h4>
			<input type="text" name="name" />
			<h4>Organisator</h4>
			<input type="text" name="organisator" />
			<h4>Max prijs ticket</h4>
			<input type="number" name="price" />
			<h4>Genre</h4>
			<input type="text" name="genre" />
			<h4>Regio</h4>
			<input type="text" name="region" /><br />
			<h4>Hoofcategorie</h4>
			<select>
				<option value="hoofdcat1">Hoofdcat1</option>
				<option value="hoofdcat2">Hoofdcat2</option>
				<option value="hoofdcat3">Hoofdcat3</option>
				<option value="hoofdcat4">Hoofdcat4</option>
			</select>
			<!--gebaseerd op hoofdcat-->
			<h4>Subcategorie</h4>
			<select>
				<option value="subcat1">Subcat1</option>
				<option value="subcat2">Subcat2</option>
			</select>
			<button type="submit">Filter</button>
		</form>
	</div>
</div>
<footer>
Footer Notes
TODO
</footer>

</body>
</html>