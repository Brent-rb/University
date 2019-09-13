<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<meta name="viewport" content="width=device-width" />
	<title>Zoeken</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div id="searchDiv">
		<!-- nog niet functioneel, en TODO: meer filter opties -->
		<form class="basic_form" method="GET" action="/~brentberghmans/subcat/index.php">
			<h2>Filters</h2>
			<h4>Naam</h4>
			<input type="text" name="name" />
			<h4>Tags</h4>
			<input type="text" name="tags" />
			<h4>Organisator</h4>
			<input type="text" name="organisator" />
			<h4>Subcategorie</h4>
			<select name="subid">
			<?php
			include '/home/brentberghmans/secure/DB_INFO.php';

			//Connectie maken met DB
			try {
				$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
			}
			catch (PDOException $e) {
				return "dberror";
			}

			//Query voorbereiden
			$query = $conn->prepare("SELECT subid, name FROM subcat;");

			if($query->execute()) {
				while($row = $query->fetch(PDO::FETCH_BOTH)) {
					echo "<option value=\"" . $row['subid'] . "\">" . $row['name'] . "</option>";
				}
			}
			?>
			</select>
			<h4>Stad/Dorp</h4>
			<input type="text" name="city" />
			<h4>Postcode</h4>
			<input type="number" name="postcode" /><br />
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