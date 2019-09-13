<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<title>Subcategorie</title>
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
		<form class="basic_form" method="POST" action="/~brentberghmans/src/scripts/createSubcat.php">
			<h2>Subcategorie aanmaken</h2>
			<h4>Hoofdcategorie</h4>
			<select name="hoofdid" required>
				<?php
				$query = $conn->prepare("SELECT hoofdid, name FROM hoofdcat;");

				if($query->execute()) {
					while($row = $query->fetch(PDO::FETCH_BOTH)) {
						echo "<option value=\"" . $row['hoofdid'] . "\">" . $row['name'] . "</option>";
					}
				}
				?>
			</select>
			<h4>Naam</h4>
			<input type='text' name='name' required/>
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