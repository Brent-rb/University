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
		<?php
		if(isset($_SESSION['rights']) && ($_SESSION['rights'] == "admin" || $_SESSION['rights'] == "mod"))
			echo "<th>Mod Acties</th>";
		?>
	</tr>
	<?php 
	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		echo "Failed to connect to the database.\n";
	}

	$prepare = getPrepare();
	$query = $conn->prepare($prepare);
	$query = fillPrepare($query);

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
			echo "<tr><td><a href='/~brentberghmans/event/index.php?eventid=" . $row['eventid'] . "'><img alt='evenement afbeelding' src='" . $image . "' /></a></td>";
			echo "<td><a href='/~brentberghmans/event/index.php?eventid=" . $row['eventid'] . "'>" . $row['name'] . "</a></td>";
			echo "<td>" . $row['organisator'] . "</td>";
			echo "<td>" . date('d-m-Y', strtotime($row['startdate'])) . "</td>";
			echo "<td>" . date('d-m-Y', strtotime($row['enddate'])) . "</td>";
			echo "<td>" . $row['city'] . "</td>";
			echo "<td><a href='". $row['website'] . "'>" . $row['website'] . "</a></td>";
			echo "<td>" . $row['price'] . "</td>";
			if(isset($_SESSION['rights'])) {
				if($_SESSION['rights'] == "admin" || $_SESSION['rights'] == "mod")
					echo "<td><form action='/~brentberghmans/event/edit.php' method='POST'><input type='hidden' name='eventid' value='" . $row['eventid'] . "'/><button type='submit'>Edit</button></form>";
				if($_SESSION['rights'] == "admin")
					echo "<form action='/~brentberghmans/src/scripts/deleteEvent.php' method='POST'><input type='hidden' name='eventid' value='" . $row['eventid'] . "'/><button type='submit'>Delete</button></form>";
				echo "</td>";
			}
			echo "</tr>";
		}
	}


	function getPrepare() {
		$string = "SELECT name, organisator, eventid, startdate, enddate, city, website, price FROM event ";
		$nothingset = true;

		if(isset($_REQUEST['name']) && $_REQUEST['name'] != null) {
			$string = $string . "WHERE name LIKE :name";
			$nothingset = false;
		}


		if(isset($_REQUEST['tags']) && $_REQUEST['tags'] != null) {
			if($nothingset) {
				$string = $string . "WHERE tags LIKE :tags";
				$nothingset = false;
			}
			else {
				$string = $string . " AND tags LIKE :tags";
			}
		}

		if(isset($_REQUEST['organisator']) && $_REQUEST['organisator'] != null) {
			if($nothingset) {
				$string = $string . "WHERE organisator LIKE :organisator";
				$nothingset = false;
			}
			else {
				$string = $string . " AND organisator LIKE :organisator";
			}
		}

		if(isset($_REQUEST['subid']) && $_REQUEST['subid'] != 0) {
			if($nothingset) {
				$string = $string . "WHERE subid = :subid";
				$nothingset = false;
			}
			else {
				$string = $string . " AND subid = :subid";
			}
		}

		if(isset($_REQUEST['city']) && $_REQUEST['city'] != null) {
			if($nothingset) {
				$string = $string . "WHERE city = :city";
				$nothingset = false;
			}
			else {
				$string = $string . " AND city = :city";
			}
		}

		if(isset($_REQUEST['postcode']) && $_REQUEST['postcode'] != null) {
			if($nothingset) {
				$string = $string . "WHERE postcode = :postcode";
				$nothingset = false;
			}
			else {
				$string = $string . " AND postcode = :postcode";
			}
		}

		return $string;
	}

	function fillPrepare($query) {
		if(isset($_REQUEST['name']) && $_REQUEST['name'] != null) {
			$query->bindValue(':name', "%" . $_REQUEST['name'] . "%");
		}

		if(isset($_REQUEST['tags']) && $_REQUEST['tags'] != null) {
			$query->bindValue(':tags', "%" . $_REQUEST['tags'] . "%");
		}

		if(isset($_REQUEST['organisator']) && $_REQUEST['organisator'] != null) {
			$query->bindValue(':organisator', "%" . $_REQUEST['organisator'] . "%");
		}

		if(isset($_REQUEST['subid']) && $_REQUEST['subid'] != null) {
			$query->bindValue(':subid', $_REQUEST['subid']);
		}

		if(isset($_REQUEST['city']) && $_REQUEST['city'] != null) {
			$query->bindValue(':city', $_REQUEST['city']);
		}

		if(isset($_REQUEST['postcode']) && $_REQUEST['postcode'] != null) {
			$query->bindValue(':postcode', $_REQUEST['postcode']);
		}

		return $query;
	}

	?>
</table>