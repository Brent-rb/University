<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<title>Hoofdcategorie Aanpassen</title>
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
		<form class="basic_form" method="POST" action="/~brentberghmans/src/scripts/updateCat.php">
			<h2>Hoofdcategorie aanpassen</h2>
			<h4>Hoofdcategorie</h4>
			<select name="hoofdid">";
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
			$query = $conn->prepare("SELECT hoofdid, name FROM hoofdcat;");

			if($query->execute()) {
				while($row = $query->fetch(PDO::FETCH_BOTH)) {
					echo "<option value=\"" . $row['hoofdid'] . "\">" . $row['name'] . "</option>";
				}
			}
			?>
			</select>
			<h4>Nieuwe Naam</h4>
			<input type='text' name='name' />
			<h4>Nieuwe Description</h4>
			<textarea name='description'></textarea>
			<?php
			if($_SESSION['rights'] == "admin") {?>
				<h4>Verwijderen?</h4>
				<input type='checkbox' name='delete' />
			<?php
			}
			?>
			<button type='submit'>Update</button>
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