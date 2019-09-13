<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<link rel="stylesheet" href="/~brentberghmans/styles/eventStyle.css" type="text/css" />
	<title>Edit evenement</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
<?php
if(isset($_SESSION['rights']) && isset($_REQUEST['eventid'])) {
	if($_SESSION['rights'] == "admin" || $_SESSION['rights'] == "mod") {

		//Login info includen
		include '/home/brentberghmans/secure/DB_INFO.php';

		//Connectie maken met DB
		try {
			$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
		}
		catch (PDOException $e) {
			return "dberror";
		}

		//Pre-fill informatie ophalen 
		$query = $conn->prepare("SELECT * FROM event WHERE eventid = :eventid ;");
		$query->bindValue(':eventid', $_REQUEST['eventid']);

		if($query->execute()) 
			$row = $query->fetch(PDO::FETCH_BOTH);

		?>
		<form class="basic_form" action="/~brentberghmans/src/scripts/updateEvent.php" method="POST" enctype="multipart/form-data" >
			<h2>Edit Event</h2>
			<h4>Event name</h4>
			<input type="text" name="eventname" <?php echo "value='" . stripslashes($row['name']) . "'"; ?>  required/>
			<h4>Organisator</h4>
			<input type="text" name="organisator" <?php echo "value='" . stripslashes($row['organisator']) . "'"; ?> required/>
			<h4>Start datum</h4>
			<input type="date" name="startdate" <?php echo "value='" . date('Y-m-d', strtotime($row['startdate'])) . "'"; ?> required/>
			<h4>Eind datum</h4>
			<input type="date" name="enddate" <?php echo "value='" . date('Y-m-d', strtotime($row['enddate'])) . "'"; ?> required/>
			<h4>Straat</h4>
			<input type="text" name="street" <?php echo "value='" . stripslashes($row['street']) . "'"; ?> required/>
			<h4>Stad/Dorp</h4>
			<input type="text" name="city" <?php echo "value='" . stripslashes($row['city']) . "'"; ?> required/>
			<h4>Postcode</h4>
			<input type="number" name="postcode" <?php echo "value='" . $row['postcode'] . "'"; ?> required/>
			<h4>Description</h4>
			<textarea name="description" required><?php echo str_replace("<br />", "", stripslashes($row['description'])); ?></textarea>				
			<h4>Tags</h4>
			<input type="text" name="tags" <?php echo "value='" . stripslashes($row['tags']) . "'" ;?> required/>
			<h4>Prijs van tickets</h4>
			<textarea name="price" required><?php echo stripslashes($row['price']);?></textarea>
			<h4>Website</h4>
			<input type="url" name="website" <?php echo "value='" . stripslashes($row['website']) . "'" ?> required/>
			<h4>Sponsor?</h4>
			<input type="checkbox" name="sponsor" <?php if($row['sponsor'] == '1') echo "checked"; ?> />
			<h4>Subcategorie</h4>
			<select name="subcat" required>";
			<?php

			//Query voorbereiden
			$query = $conn->prepare("SELECT subid, name FROM subcat;");

			if($query->execute()) {
				while($subrow = $query->fetch(PDO::FETCH_BOTH)) {
					if($row['subid'] != $subrow['subid'])
						echo "<option value=\"" . $subrow['subid'] . "\">" . $subrow['name'] . "</option>";
					else
						echo "<option value=\"" . $subrow['subid'] . "\" selected>" . $subrow['name'] . "</option>";
				}
			}
			?>
			</select>
			<h4>Foto's</h4>
			<input type="file" id="file" name="files[]" multiple="multiple" accept="image/*" />
			<input type="hidden" name="eventid" <?php echo "value='" . $_REQUEST['eventid'] . "'"; ?> />
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