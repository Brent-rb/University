<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<link rel="stylesheet" href="/~brentberghmans/styles/hoofdcatStyle.css" type="text/css" />
	<meta name="viewport" content="width=device-width" />
	<title>Hoofd categorieen</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<!-- TODO probleem: Variabel aantal categorieen -> oplossing met AJAX/PHP ? big_cat.width = (100 / aantal categorieen) + "%"; ? -->
<div id="content">

	<?php
	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		echo "Failed to connect to the database.\n";
	}

	if(!isset($_REQUEST['hoofdid']))
		$query = $conn->prepare('SELECT * FROM hoofdcat ;');
	else {
		$query = $conn->prepare('SELECT * FROM hoofdcat WHERE hoofdid = :hoofdid ;');
		$query->bindValue(':hoofdid', (int)$_REQUEST['hoofdid']);
	}

	if($query->execute()) {
		while($row = $query->fetch(PDO::FETCH_BOTH)) {
			echo "<section class='big_cat'><h2>" . $row['name'] . "</h2><p>" . $row['description'] . "</p><ul>";

			$subquery = $conn->prepare('SELECT * FROM subcat WHERE hoofdid = :hoofdid ;');
			$subquery->bindValue(':hoofdid', $row['hoofdid']);

			if($subquery->execute()) {
				while($subrow = $subquery->fetch(PDO::FETCH_BOTH)) {
					echo "<li><a href='/~brentberghmans/subcat/index.php?subid=" . $subrow['subid'] . "'>" . $subrow['name'] . "</a></li>";
				}
			}

			echo "</ul></section>";
		}
	}

	?>
</div>
<footer>
Footer Notes
TODO
</footer>

</body>
</html>