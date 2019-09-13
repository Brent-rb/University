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
	<div id="profile">
		<ul>
			<!-- TODO content vervangen met AJAX en ophalen met PHP-->
			<!-- Profiel overzicht -->
			<li id="selected">Profiel</li>
			<!-- Afgelopen evenemeten waarop hij gesubscribed was -->
			<!-- Evenementen tonen zoals op de subcategorieen pagina -->
			<li>Afgelopen evenementen</li>
			<!-- Nog niet afgelopen evenementen waarop hij gesubscribed was -->
			<li>Toekomstige evenementen</li>
			<!-- Comments / ratings die de user gelaten heeft -->
			<li>Geplaatse comments/ratings</li>
		</ul>
		<img src="/~brentberghmans/img/ele.jpg" />
		<?php
		session_start();
		if(isset($_SESSION['userid'])) {


			include "/home/brentberghmans/secure/DB_INFO.php";

			try {
				$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
			}
			catch (PDOException $e) {
				echo "<p> Database error </p>";
			}

			$query = $conn->prepare("SELECT * FROM userInfo WHERE userid = :userid ;");
			$query->bindValue(':userid', (int)$_SESSION['userid']);
			if($query->execute()) {
				if($row = $query->fetch(PDO::FETCH_BOTH)) {
					echo "<table><tr><td>Username:</td><td>". $_SESSION['username'] ."</td></tr><tr><td>Voornaam:</td><td>". $row['voornaam'] ."</td></tr><tr><td>Achternaam:</td><td>". $row['achternaam'] ."</td></tr><tr><td>Leeftijd:</td><td>". $row['leeftijd'] ."</td></tr><tr><td>Woonplaats:</td><td>" . $row['straat'] . " " . $row['stad'] . " " . $row['postcode'] . "</td></tr><tr><td>Email:</td><td>". $row['email'] ."</td></tr></table>";
				}

			}
			else {
				echo "<div class=\"basic_textbox\">Shit werkt niet</div>";
			}
		}
		else {
			echo "<div class=\"basic_textbox\"> U bent niet ingelogd, gelieve in te loggen </div>";
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