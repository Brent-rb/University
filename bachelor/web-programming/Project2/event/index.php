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
	<meta name="viewport" content="width=device-width" />
	<title>Evenement</title>
</head>
<body onload='disableAnchors(this)'>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="imageOverlay" onclick="imageOverlayGone()"><span class="centerHelper"></span></div>
<div id="content">
	<?php 
	//Als er een eventid is meegegeven -> info uit db ophalen
	if(isset($_REQUEST['eventid'])) {
		//Login info includen
		include '/home/brentberghmans/secure/DB_INFO.php';

		//Connectie maken met DB
		try {
			$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
		}
		catch (PDOException $e) {
			return "dberror";
		}

		//Query voorbereiden
		$query = $conn->prepare("SELECT * FROM event WHERE eventid = :eventid ;");
		//Query invullen
		$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
		//Query uitvoeren en informatie opslaan
		if($query->execute())
			$eventInfo = $query->fetch(PDO::FETCH_BOTH);

		//Als het id bestaat 
		if(isset($eventInfo) && $eventInfo != null) {
			//Nieuwe query maken voor images op te halen van dit event
			$query = $conn->prepare("SELECT * FROM eventimages WHERE eventid = :eventid ;");
			$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
			if($query->execute())
				//Images ophalen
				while($row = $query->fetch(PDO::FETCH_BOTH))
					$images[] = $row['imagepath'];

			//Admin opties:
			if(isset($_SESSION['rights'])) {
				echo "<div class='adminOptions'>";
				if($_SESSION['rights'] == "admin" || $_SESSION['rights'] == "mod")
					echo "<form action='edit.php' method='POST'><input type='hidden' name='eventid' value='" . $eventInfo['eventid'] . "' /><button type='submit'>Edit</button></form>";
				if($_SESSION['rights'] == "admin")
					echo "<form action='/~brentberghmans/src/scripts/deleteEvent.php' method='POST'><input type='hidden' name='eventid' value='" . $eventInfo['eventid'] . "' /><button type='submit'>Delete</button></form>";
				echo"</div>";
			}


			//Titel uitprinten
			echo "<div id=\"event\"><h2>" . stripslashes($eventInfo['name']) . "</h2>";
			
			//Images uitprinten (als ze bestaan)
			if(isset($images)) {
				echo "<a class='changeImageFallback' href='" . $images[0] . "'><div id=\"bigimage\"><img alt='evenement afbeelding groot' onclick=\"imageOverlay(this)\" src=\"". $images[0] . "\" /></div></a><div id=\"thumbnails\">";
				//Voor elke image een thumbnail maken
				foreach($images as $image) 
					echo "<a class='changeImageFallback' href='" . $image . "'><img alt='evenement afbeeldingen klein' class='thumbnail' onclick=\"changeBigImage(this)\" src=\"" . $image . "\" /></a>";
				echo "</div>";
			}

			//Description printen
			echo "<div id=\"eventDescription\">";
			echo "<p>" . stripslashes($eventInfo['description']) . "</p>";

			//Zijdelingse informatie printen
			echo "<table><tr><td>Prijzen:</td><td>" . stripslashes($eventInfo['price']) . "</td></tr>";
			echo "<tr><td>Straat:</td><td>" . stripslashes($eventInfo['street']) . "</td></tr>";
			echo "<tr><td>Gemeente:</td><td>" . stripslashes($eventInfo['city']) . "</td></tr>";
			echo "<tr><td>Postcode:</td><td>" . stripslashes($eventInfo['postcode']) . "</td></tr>";
			date_default_timezone_set('CET');
			echo "<tr><td>Start datum:</td><td>" . date('d-m-Y', strtotime($eventInfo['startdate'])) . "</td></tr>";
			echo "<tr><td>Eind datum: </td><td>" . date('d-m-Y', strtotime($eventInfo['enddate'])) . "</td></tr>";
			$website = stripslashes($eventInfo['website']);
			echo "<tr><td>Website:</td><td><a href=\"" . $website . "\">" . $website . "</a></td></tr>";
			echo "<tr><td>Organisator:</td><td>" . $eventInfo['organisator'] . "</td></tr>";
			echo "<tr><td>Views:</td><td>" . $eventInfo['views'] . "</td></tr>";

			$subquery = $conn->prepare("SELECT AVG(rating) FROM ratings WHERE eventid = :eventid GROUP BY eventid");
			$subquery->bindValue(':eventid', $eventInfo['eventid']);
			$subquery->execute();
			$rating = $subquery->fetch(PDO::FETCH_BOTH);
			if($rating != null )
				echo "<tr><td>Rating:</td><td>" . sprintf("%1.2f", $rating['avg']) . "/5</td></tr>"; 

			if(isset($_SESSION['userid'])) {
				$scoreQuery = $conn->prepare("SELECT * FROM ratings WHERE userid = :userid AND eventid = :eventid ;");
				$scoreQuery->bindValue(':userid', $_SESSION['userid']);
				$scoreQuery->bindValue(':eventid', $eventInfo['eventid']);
				if($scoreQuery->execute()) {
					$scoreRow = $scoreQuery->fetch(PDO::FETCH_BOTH);
					if($scoreRow == null)
						$rated = false;
					else
						$rated = true;
				}

				
				echo "<tr><td>Jouw Score:</td>";
				if($rated)
					echo "<td>" . $scoreRow['rating'] . "/5</td>";
				else {
					echo "<td><form action='/~brentberghmans/src/scripts/rate.php' method='POST'><input type='hidden' name='userid' value='" . $_SESSION['userid'] . "' /><input type='hidden' name='eventid' value='". $eventInfo['eventid'] . "' /><input name='rating' type='range' min='0' max='5' value='3' /><button type='submit'>Score!</button></form></td>";
				}
			}

			//Controleren of de gebruiker al gesubbed is
			if(isset($_SESSION['userid'])) { 
				$likeQuery = $conn->prepare("SELECT * FROM likes WHERE userid = :userid AND eventid = :eventid ;");
				$likeQuery->bindValue(':userid', $_SESSION['userid']);
				$likeQuery->bindValue(':eventid', $eventInfo['eventid']);
				if($likeQuery->execute()) {
					$likeRow = $likeQuery->fetch(PDO::FETCH_BOTH);
					if($likeRow == null)
						$liked = false;
					else
						$liked = true;
				}

				
				echo "<tr><td>Aangeraden:</td>";
				if($liked)
					echo "<td>Ja <form action='/~brentberghmans/src/scripts/dislike.php?url=/~brentberghmans/event/?eventid=" . $eventInfo['eventid'] ."' method='POST'>";
				else
					echo "<td>Nee <form action='/~brentberghmans/src/scripts/like.php?url=/~brentberghmans/event/?eventid=" . $eventInfo['eventid'] ."' method='POST'>";

				echo "<input type='hidden' name='eventid' value='" . $eventInfo['eventid'] . "' />
				<input type='hidden' name='userid' value='" .  $_SESSION['userid'] . "' />";

				if($liked)
					echo "<button type='submit'>Dislike</button>";
				else
					echo "<button type='submit'>Like</button>";
				echo "</form></tr>";	
			}
			echo"</table>"; 

			//Clearfloat voor float te clearen --> anders layout bug
			echo "<div class=\"clearFloat\"></div></div>";
			//Comments ophalen
			echo "<div id=\"eventComments\">";

			//Comments tabel joinen met gebruikers informatie, zo kunnen we een avatar en naam bij de comment posten
			$query = $conn->prepare("SELECT username, content, postdate, avatar, commentid, comments.userid FROM comments JOIN users ON comments.userid = users.userid JOIN userinfo ON users.userid = userinfo.userid WHERE eventid = :eventid ORDER BY comments.postdate ;");
			$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
			//Als de query uitvoert -> comments afprinten
			if($query->execute()) {
				while($row = $query->fetch(PDO::FETCH_BOTH)) {
					echo "
					<div class=\"comment\">
						<div class=\"userbox\">
							<img alt='avatar' src=\"" . $row['avatar'] . "\" />
							<a href='/~brentberghmans/acount/?userid=" . $row['userid'] . "'><h3>" . $row['username'] . "</h3></a>
							<h4>" . date('d-m-Y', strtotime($row['postdate'])) . "</h4>
						</div>
						<article class=\"comment_content\">" . stripslashes($row['content']) . "</article>";
					if(isset($_SESSION['rights']) && ($_SESSION['rights'] == "mod" || $_SESSION['rights'] == "admin")) {
						echo "<form action='editComment.php' method='POST'>";
						echo "<input type='hidden' name='commentid' value='" . $row['commentid'] . "' />";
						echo "<button type='submit'>Edit</button></form>";
					}
					if(isset($_SESSION['rights']) && ($_SESSION['rights'] == "admin")) {
						echo "<form action='/~brentberghmans/src/scripts/deleteComment.php' method='POST'>";
						echo "<input type='hidden' name='commentid' value='" . $row['commentid'] . "' />";
						echo "<input type='hidden' name='eventid' value='" . $eventInfo['eventid'] . "' />";
						echo "<button type='submit'>Delete</button></form>";
					}	
					echo "<span class=\"clearFloat\"></span>
					</div>";
				}
			}
			else
				echo "<p>Kon de comments niet laden</p>";
			
			//Als iemand ingelogd is, mag hij een comment plaatsen
			if(isset($_SESSION['userid'])) {
				echo "<div class=\"comment\">
						<form action=\"/~brentberghmans/src/scripts/uploadComment.php?url=/~brentberghmans/event/index.php?eventid=" . $eventInfo['eventid'] . "#eventComments\" method=\"POST\">
						<textarea name=\"content\"></textarea>
						<input type=\"hidden\" name=\"eventid\" value=\"" . $eventInfo['eventid'] . "\" />
						<input type=\"hidden\" name=\"userid\" value=\"" . $_SESSION['userid'] . "\" />
						<input type=\"submit\"></input>
						</form>
					</div>";
			}
			//Divs aflsuiten
			echo "</div></div>";

			//Views updaten van huidig evenement
			$query = $conn->prepare("UPDATE event SET views = views + 1 WHERE eventid = :eventid ;");
			$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
			if(!$query->execute())
				print_r($conn->errorInfo());

			//Kijken of er voor deze maand al een viewsMonth is aangemaakt.
			$query = $conn->prepare("SELECT * FROM viewsMonth WHERE eventid = :eventid AND month = :month AND year = :year ;");
			$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
			$query->bindValue(':month', (int)date('m'));
			$query->bindValue(':year', (int)date('Y'));
			if($query->execute()) {
				//Rij ophalen
				$row = $query->fetch(PDO::FETCH_BOTH);
				//Als de rij leeg is moeten we voor deze maand een views/month aanmaken.
				if($row == null) {
					$query = $conn->prepare("INSERT INTO viewsMonth (eventid, month, year, views) VALUES (:eventid, :month, :year, :views);");
					$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
					$query->bindValue(':month', (int)(date('m')));
					$query->bindValue(':year', (int)(date('Y')));
					$query->bindValue(':views', 1);
					$query->execute();
				}
				//Zo niet moeten we deze rij updaten
				else {
					$query = $conn->prepare("UPDATE viewsMonth SET views = views + 1 WHERE eventid = :eventid AND month = :month AND year = :year");
					$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
					$query->bindValue(':month', (int)(date('m')));
					$query->bindValue(':year', (int)(date('Y')));
					$query->execute();
				}
			}
		}
		else
			echo "<div class='basic_textbox'>Het opgegeven evenement is niet gevonden.</div>";
	}
	else 
		echo "<div class=\"basic_textbox\">Selecteer een evenement</div>";
	?>
</div>
<footer>
Footer Notes
TODO
</footer>
<script src="/~brentberghmans/src/scripts/bigImage.js" type="text/JavaScript"></script>
<script src="/~brentberghmans/src/scripts/imageChooser.js" type="text/JavaScript"></script>
</body>
</html>