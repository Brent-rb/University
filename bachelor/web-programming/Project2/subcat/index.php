<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<link rel="stylesheet" href="/~brentberghmans/styles/subcatStyle.css" type="text/css" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<meta name="viewport" content="width=device-width" />
	<title>Sub categorieen</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div id="filterbar">
		<form id="filterform" method="GET" action="index.php">
			<h2>Filters</h2>
			<h4>Naam</h4>
			<input onkeyup="updateResults()" type="text" name="name" />
			<h4>Tags</h4>
			<input onkeyup="updateResults()" type="text" name="tags" />
			<h4>Organisator</h4>
			<input onkeyup="updateResults()" type="text" name="organisator" />

			<h4>Subcategorie</h4>
			<select onchange='updateResults()' name="subid">
				<option value="0" selected>Default</option>
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
			<input onkeyup="updateResults()" type="text" name="city" />
			<h4>Postcode</h4>
			<input onkeyup="updateResults()" type="number" name="postcode" /><br />
			<button type="submit">Filter</button>
		</form>
	</div>
	<!-- TODO probleem: linken naar het event, anchor gaat niet op de hele rij -->
	<!-- Possible optie: Verschillende functionaliteit koppellen aan elke kolom, bv: klikken op een organisator -> lijst van alle evenementen van die organisator + beschrijving etc... -->
	<!-- Probleem lettertype? &euro; kan niet gerenderd worden -->
	<div id="resultaten">
		<?php
		include '/home/brentberghmans/public_html/src/scripts/getEventTable.php';
		?>	
	</div>
</div>
<footer>
Footer Notes
TODO
</footer>
<script src='/~brentberghmans/src/scripts/resultAjax.js' type="text/JavaScript"></script>
</body>
</html>