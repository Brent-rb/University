<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<link rel="stylesheet" href="/~brentberghmans/styles/mainStyle.css" type="text/css" />
	<meta name="viewport" content="width=device-width" />
	<title>Home</title>
</head>
<body onload='initMoreLess()'>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<!-- TODO Sections toevoegen waarin de categorie staat, momenteel staat het in het veld voor de naam van het evenement -->
<!-- TODO Recente comments section die met AJAX continue update -->
<!-- Bedoeling: Een paar events uit een database halen aan de hand van rating, views, datum, ... en door op een pijltje te klikken naar het volgend evenement te gaan -->
<div id="content">
	<?php
	include '/home/brentberghmans/secure/DB_INFO.php';
	include '/home/brentberghmans/public_html/src/scripts/calendar.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		return "Kon niet verbinden met de database.<br />";
	}

	//Sponsor evenement
	$query = $conn->prepare("SELECT eventid, name, description FROM event WHERE sponsor = '1' AND startdate >= :startdate ORDER BY RANDOM() LIMIT 1;");
	$query->bindValue(':startdate', date("Y-m-d"));
	if($query->execute()) {
		$row = $query->fetch(PDO::FETCH_BOTH);
		if($row != null) 
			printPost($conn, "Gesponserd Evenement", $row['eventid'], $row['name'], $row['description'], true);

	}

	//Populair Event
	//Kijken welk evenement populair is deze maand
	$query = $conn->prepare("SELECT eventid FROM viewsMonth WHERE views >= ALL (SELECT views FROM viewsMonth) ORDER BY RANDOM() LIMIT 1;");
	$query->bindValue(':month', (int)date('m'));
	$query->bindValue(':year', (int)date('Y'));
	$query->bindValue(':month2', (int)date('m'));
	$query->bindValue(':year2', (int)date('Y'));
	if($query->execute()) {
		//Populaire event ophalen
		$row = $query->fetch(PDO::FETCH_BOTH);
		//Als er een populair event is deze week dan gaan we dit ophalen.
		if($row != null) {
			$query = $conn->prepare("SELECT eventid, name, description FROM event WHERE eventid = :eventid ;");
			$query->bindValue(':eventid', $row['eventid']);
			if($query->execute()) {
				$row = $query->fetch(PDO::FETCH_BOTH);
				if($row != null) 
					printPost($conn, "Meest bekeken deze maand", $row['eventid'], $row['name'], $row['description'], false);

			}
		}
	}

	//Opkomend evenement
	$query = $conn->prepare("SELECT eventid, name, description FROM event WHERE startdate >= :startdate ORDER BY startdate LIMIT 1;");
	$query->bindValue(':startdate', date("Y-m-d"));
	if($query->execute()) {
		$row = $query->fetch(PDO::FETCH_BOTH);
		if($row != null) 
			printPost($conn, "Opkomende Evenement", $row['eventid'], $row['name'], $row['description'], false);

	}


	//Id van de hoogste score ophalen
	$query = $conn->prepare("SELECT eventid, name, description FROM event WHERE startdate >= :startdate AND eventid IN (SELECT eventid FROM ratings GROUP BY eventid ORDER BY AVG(rating) LIMIT 1) LIMIT 1");
	$query->bindValue(':startdate', date("Y-m-d"));
	if($query->execute()) {
		$row = $query->fetch(PDO::FETCH_BOTH);
		if($row != null) 
			printPost($conn, "Hoogst Gerate", $row['eventid'], $row['name'], $row['description'], false);

	}


	function printPost($conn, $title, $eventid, $name, $description, $bigPost) {
		$imgquery = $conn->prepare("SELECT imagepath FROM eventImages WHERE eventid = :eventid LIMIT 1;");
		$imgquery->bindValue(':eventid', $eventid);
		if($imgquery->execute())
			$imgrow = $imgquery->fetch(PDO::FETCH_BOTH);

		if($bigPost) 
			echo "<div class='big_post'>";
		else
			echo "<div class='mid_post'>";

		echo "<a href='/~brentberghmans/event/?eventid=" . $eventid . "'><h3>" . $title . "</h3></a>";
		echo "<a href='/~brentberghmans/event/?eventid=" . $eventid . "'><h4>" . stripslashes($name) . "</h4></a>";
		if($imgrow != null)
			echo "<a href='/~brentberghmans/event/?eventid=" . $eventid . "'><img src='" . $imgrow['imagepath'] . "' alt='Evenement foto' /></a>";
		echo "<p>" . stripslashes($description) . "</p><div class='moreLess'></div></div>";
	}

	echo "<div class='mid_post'><a href='/~brentberghmans/calendar/?month=" . date('m') . "&amp;year=" . date('Y') . "'><h3>Events Deze Maand</h3></a>";
	printMonth($conn, (int)date('m'), (int)date('Y'));
	echo "</div>";
	?>
	<div class="clearFloat"></div>

</div>
<footer>
Footer Notes
TODO
</footer>

<script src='/~brentberghmans/src/scripts/moreLess.js' type='text/JavaScript'></script>
</body>
</html>