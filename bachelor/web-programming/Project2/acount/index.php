<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<link rel="stylesheet" href="/~brentberghmans/styles/acountStyle.css" type="text/css" />
	<meta name="viewport" content="width=device-width" />
	<title>Profiel</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<?php

	include '/home/brentberghmans/secure/DB_INFO.php';

	//Connectie maken
	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		echo "Failed to connect to the database.\n";
	}

	if(isset($_SESSION['userid']) && isset($_GET['userid']) && $_SESSION['userid'] != $_GET['userid']) {
		$query = $conn->prepare("SELECT * FROM followers WHERE baseid = :baseid AND targetid = :targetid ;");
		$query->bindValue(':baseid', $_SESSION['userid']);
		$query->bindValue(':targetid', $_GET['userid']);
		if($query->execute())
			$row = $query->fetch(PDO::FETCH_BOTH);
		else
			print_r($conn->errorInfo());
		if(!isset($row) || $row['baseid'] == null) {
			echo "<form action='/~brentberghmans/src/scripts/follow.php' method='post'>";
		}
		else 
			echo "<form action='/~brentberghmans/src/scripts/unfollow.php' method='post'>";
		echo "<input name='baseid' value='" . $_SESSION['userid'] . "' hidden /><input name='targetid' value='" . $_GET['userid']. "' hidden />"; 
		if(!isset($row) || $row['baseid'] == null) {
			echo "<button type='submit'>Follow</button></form>";
		}
		else
			echo "<button type='submit'>Unfollow</button></form>";
	}
	?>
	<div id="profile">
		<?php
		if(!isset($_GET['userid']) || $_GET['userid'] == null) {
			echo "<form class='basic_form' action='index.php' method='GET'>";
			echo "<h4>Selecteer een gebruiker</h4>";
			echo "<select name='userid'>";


			//Query voorbereiden
			$query = $conn->prepare("SELECT username, userid FROM users ORDER BY username;");

			if($query->execute()) {
				while($row = $query->fetch(PDO::FETCH_BOTH)) {
					echo "<option value=\"" . $row['userid'] . "\">" . $row['username'] . "</option>";
				}
			}

			echo "</select><input type='submit' /></form>";

		}
		else {
			$query = $conn->prepare("SELECT * FROM userInfo JOIN users ON userInfo.userid = users.userid WHERE userInfo.userid = :userid ;");
			$query->bindValue(':userid', (int)$_GET['userid']);
			$row = "";
			if($query->execute()) {
				if($row = $query->fetch(PDO::FETCH_BOTH)) {
					echo "<img alt='avatar' src='" . $row['avatar'] . "' /><table><tr><td>Username:</td><td>". $row['username'] ."</td></tr><tr><td>Voornaam:</td><td>". $row['voornaam'] ."</td></tr><tr><td>Achternaam:</td><td>". $row['achternaam'] ."</td></tr><tr><td>Leeftijd:</td><td>". calcAge($row['geboorte']) ."</td></tr><tr><td>Woonplaats:</td><td>" . $row['straat'] . " " . $row['stad'] . " " . $row['postcode'] . "</td></tr><tr><td>Email:</td><td>". $row['email'] ."</td></tr></table>";
				}

			}
			else {
				print_r($conn->errorInfo());
				echo "<div class=\"basic_textbox\">Verbinding maken met database mislukt, probeer later nog eens.</div>";
			}

			$query = $conn->prepare("SELECT name, likes.eventid, startdate, enddate FROM likes JOIN event ON likes.eventid = event.eventid WHERE userid = :userid ;");
			$query->bindValue(':userid', $row['userid']);
			if($query->execute()) {
				$now = time();
				echo "<h4>Deze persoon raad de volgende evenementen aan:</h4>";
				echo "<ul>";
				while($row = $query->fetch(PDO::FETCH_BOTH)) {
					if($now < strtotime($row['startdate']) || $now < strtotime($row['enddate']))
						echo "<li class='green'><a href='/~brentberghmans/event/?eventid=" . $row['eventid'] . "'>" . $row['name'] .  "</a></li>"; 
					else
						echo "<li class='red'><a href='/~brentberghmans/event/?eventid=" . $row['eventid'] . "'>" . $row['name'] .  "</a></li>"; 
				}
				echo "</ul>";
			}
			else {
				echo "<div class=\"basic_textbox\">Verbinding maken met database mislukt, probeer later nog eens.</div>";
				print_r($conn->errorInfo());
			}
		}


		function calcAge($dob) {
			//timestamp omzetten naar datum
		    $dob = date("Y-m-d", strtotime($dob));
		    //Datum object aanmaken voor nu en voor de geboortedatum
		    $dobObject = new DateTime($dob);
		    $nowObject = new DateTime();
		    //Verschil berekenen
		    $diff = $dobObject->diff($nowObject);
		    //Leeftijd teruggeven.
		    return $diff->format('%y');
		}
		?>
	</div>
</div>
<footer>
Footer Notes
TODO
</footer>

</body>
</html>