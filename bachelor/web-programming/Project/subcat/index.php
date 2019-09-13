<!DOCTYPE html>
<html>
<head>
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/style.css" type="text/css" /> 
	<title>Sub categorieen</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div id="filterbar">
		<!-- nog niet functioneel, en TODO: meer filter opties -->
		<form id="filterform" method="GET" action="index.php">
			<h2>Filters</h2>
			<h4>Naam</h4>
			<input type="text" name="name" />
			<h4>Tags</h4>
			<input type="text" name="tags" />
			<h4>Subcategorie</h4>
			<input type="text" name="subcat" />
			<h4>Stad/Dorp</h4>
			<input type="text" name="city" />
			<h4>Postcode</h4>
			<input type="text" name="postcode" /><br />
			<button type="submit">Filter</button>
		</form>
	</div>
	<!-- TODO probleem: linken naar het event, anchor gaat niet op de hele rij -->
	<!-- Possible optie: Verschillende functionaliteit koppellen aan elke kolom, bv: klikken op een organisator -> lijst van alle evenementen van die organisator + beschrijving etc... -->
	<!-- Probleem lettertype? &euro; kan niet gerenderd worden -->
	<div id="resultaten">
		<table>
			<tr>
				<th> </th>
				<th>Naam</th>
				<th>Organisator</th>
				<th>Start-Datum</th>
				<th>Eind-Datum</th>
				<th>Stad/Dorp</th>
				<th>Website</th>
				<th>Prijzen</th>
			</tr>
			<?php 
			include '/home/brentberghmans/secure/DB_INFO.php';

			try {
				$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
			}
			catch (PDOException $e) {
				echo "Failed to connect to the database.\n";
			}
			if(isset($_REQUEST['subid'])) {
				$query = $conn->prepare("SELECT name, organisator, eventid, startdate, enddate, city, website, price FROM event WHERE subid = :subid ;");
				$query->bindValue(':subid', (int)$_REQUEST['subid']);
			}
			else {
				$query = $conn->prepare("SELECT name, organisator, eventid, startdate, enddate, city, website, price FROM event ;");
			}

			if($query->execute()) {
				while($row = $query->fetch(PDO::FETCH_BOTH)) {
					//Fetching image
					$imagequery = $conn->prepare("SELECT imagepath FROM eventimages WHERE eventid = :eventid LIMIT 1 ;");
					$imagequery->bindValue(':eventid', (int)$row['eventid']);
					if($imagequery->execute()) 
						if($imagerow = $imagequery->fetch(PDO::FETCH_BOTH))
							$image = $imagerow['imagepath'];
						else
							$image = "/~brentberghmans/img/noimage.jpg";
					else
						echo "Failed to execute";
					echo "<tr><td><a href='/~brentberghmans/event/index.php?eventid=" . $row['eventid'] . "'><img src='" . $image . "' /></a></td>";
					echo "<td><a href='/~brentberghmans/event/index.php?eventid=" . $row['eventid'] . "'>" . $row['name'] . "</a></td>";
					echo "<td>" . $row['organisator'] . "</td>";
					echo "<td>" . date('d-m-Y H:i', strtotime($row['startdate'])) . "</td>";
					echo "<td>" . date('d-m-Y H:i', strtotime($row['enddate'])) . "</td>";
					echo "<td>" . $row['city'] . "</td>";
					echo "<td>" . $row['website'] . "</td>";
					echo "<td>" . $row['price'] . "</td></tr>";
				}
			}


			?>
		</table>
	</div>
</div>
<footer>
Footer Notes
TODO
</footer>

</body>
</html>