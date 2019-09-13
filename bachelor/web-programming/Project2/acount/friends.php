<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<meta name="viewport" content="width=device-width" />
	<title>Volg Lijst</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div class='basic_textbox'>
		<ul>
			<?php
				if(isset($_SESSION['userid'])) {
					include '/home/brentberghmans/secure/DB_INFO.php';

					//Connectie maken
					try {
						$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
					}
					catch (PDOException $e) {
						echo "Failed to connect to the database.\n";
					}

					$query = $conn->prepare("SELECT username, userid FROM followers JOIN users ON followers.targetid = users.userid WHERE baseid = :baseid ;");
					$query->bindValue(':baseid', $_SESSION['userid']);

					if($query->execute()) {
						while($row = $query->fetch(PDO::FETCH_BOTH)) {
							echo "<a href='/~brentberghmans/acount/?userid=" . $row['userid'] . "'><li>" . $row['username'] . "</li></a>";
						}
					}
				}
				else
					echo "<li>Niet ingelogd</li>";
			?>
		</ul>
	</div>
</div>

<footer>
Footer Notes
TODO
</footer>

</body>
</html>