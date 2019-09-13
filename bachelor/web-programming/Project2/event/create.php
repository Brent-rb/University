<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<title>Create Evenement</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
<?php
if(isset($_SESSION['rights'])) {
	if($_SESSION['rights'] == "admin") {?>
		<form class="basic_form" action="/~brentberghmans/src/scripts/createEvent.php" method="POST" enctype="multipart/form-data" >
			<h2>Create Event</h2>
			<h4>Event name</h4>
			<input type="text" name="eventname"  required/>
			<h4>Organisator</h4>
			<input type="text" name="organisator" required/>
			<h4>Start datum</h4>
			<input type="date" name="startdate"  required/>
			<h4>Eind datum</h4>
			<input type="date" name="enddate" required/>
			<h4>Straat</h4>
			<input type="text" name="street" required/>
			<h4>Stad/Dorp</h4>
			<input type="text" name="city" required/>
			<h4>Postcode</h4>
			<input type="number" name="postcode"  required/>
			<h4>Description</h4>
			<h4>Voor een YouTube video te includen kan je [youtube]youtube.com/link[/youtube] gebruiken</h4>
			<textarea name="description" required></textarea>				
			<h4>Tags</h4>
			<input type="text" name="tags" required/>
			<h4>Prijs van tickets</h4>
			<textarea name="price" required></textarea>
			<h4>Website</h4>
			<input type="url" name="website" required/>
			<h4>Sponsor?</h4>
			<input type="checkbox" name="sponsor" />
			<h4>Subcategorie</h4>
			<select name="subcat" required>";
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
			<h4>Foto's</h4>
			<input type="file" id="file" name="files[]" multiple="multiple" accept="image/*" />
			<input type="submit" />
		</form>
	<?php
	}
	else
		echo "<div class='basic_textbox'>U heeft geen toegang!</div>";
}
else 
	echo "<div class='basic_textbox'>U heeft geen toegang!</div>";
?>
</div>
<footer>
Footer Notes
TODO
</footer>

</body>
</html>