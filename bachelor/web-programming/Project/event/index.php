<!DOCTYPE html>
<html>
<head>
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/style.css" type="text/css" /> 
	<title>Home</title>
</head>
<body>
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
		if(isset($eventInfo)) {
			//Nieuwe query maken voor images op te halen van dit event
			$query = $conn->prepare("SELECT * FROM eventimages WHERE eventid = :eventid ;");
			$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
			if($query->execute())
				//Images ophalen
				while($row = $query->fetch(PDO::FETCH_BOTH))
					$images[] = $row['imagepath'];

			//Titel uitprinten
			echo "<div id=\"event\"><h2>" . stripslashes($eventInfo['name']) . "</h2>";
			
			//Images uitprinten (als ze bestaan)
			if(isset($images)) {
				echo "<div id=\"bigimage\"><img onclick=\"imageOverlay(this)\" src=\"". $images[0] . "\" /></div><div id=\"thumbnails\">";
				//Voor elke image een thumbnail maken
				foreach($images as $image) 
					echo "<img class='thumbnail' onclick=\"changeBigImage(this)\" src=\"" . $image . "\" />";
				echo "</div>";
			}


			echo "<div id=\"eventDescription\">";
		 	
			echo "<p>" . stripslashes($eventInfo['description']) . "</p>";

			echo "<table><tr><td>Prijzen:</td><td>" . stripslashes($eventInfo['price']) . "</td></tr>";
			echo "<tr><td>Straat:</td><td>" . stripslashes($eventInfo['street']) . "</td></tr>";
			echo "<tr><td>Gemeente:</td><td>" . stripslashes($eventInfo['city']) . "</td></tr>";
			echo "<tr><td>Postcode:</td><td>" . stripslashes($eventInfo['postcode']) . "</td></tr>";

			date_default_timezone_set('CET');

			echo "<tr><td>Start datum:</td><td>" . date('d-m-Y', strtotime($eventInfo['startdate'])) . "</td></tr>";
			echo "<tr><td>Eind datum: </td><td>" . date('d-m-Y', strtotime($eventInfo['enddate'])) . "</td></tr>";
			$website = stripslashes($eventInfo['website']);
			echo "<tr><td>Website:</td><td><a href=\"" . $website . "\">" . $website . "</a></td></tr>";
			echo "<tr><td>Organisator:</td><td>" . $eventInfo['organisator'] . "</td></tr></table>"; 

			echo "<div class=\"clearFloat\"></div></div>";
			echo "<div id=\"eventComments\">";

			$query = $conn->prepare("SELECT username, content, postdate, avatar FROM comments JOIN users ON comments.userid = users.userid JOIN userinfo ON users.userid = userinfo.userid WHERE eventid = :eventid ;");
			$query->bindValue(':eventid', (int)$_REQUEST['eventid']);
			if($query->execute()) {
				while($row = $query->fetch(PDO::FETCH_BOTH)) {
					echo "
					<div class=\"comment\">
						<div class=\"userbox\">
							<img src=\"" . $row['avatar'] . "\" />
							<h3>" . $row['username'] . "</h3>
							<h4>" . date('d-m-Y', strtotime($row['postdate'])) . "</h4>
						</div>
						<article class=\"content\">" . stripslashes($row['content']) . "</article>
						<span class=\"clearFloat\"></span>
					</div>";
				}
			}
			else
				print_r($conn->errorInfo());
			
			if(isset($_SESSION['userid'])) {
				echo "<div class=\"comment\">
						<form action=\"/~brentberghmans/src/scripts/uploadComment.php?url=/~brentberghmans/event/index.php?eventid=" . $_REQUEST['eventid'] . "#eventComments\" method=\"POST\">
						<textarea name=\"content\"></textarea>
						<input type=\"hidden\" name=\"eventid\" value=\"" . $_REQUEST['eventid'] . "\" />
						<input type=\"hidden\" name=\"userid\" value=\"" . $_SESSION['userid'] . "\" />
						<input type=\"submit\"></input>
						</form>
					</div>";
			}

			echo "</div></div>";

			$query = $conn->prepare("UPDATE event SET views = :views WHERE eventid = :eventid ;");
			$query->bindValue(':views', ((int)$eventInfo['views']) + 1);
			$query->bindValue(':eventid', (int)$_REQUEST['eventid']);

			$query->execute();
		}
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