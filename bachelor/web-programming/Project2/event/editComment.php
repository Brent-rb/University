<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="description" content="Evenementen Website" />
	<meta name="keywords" content="HTML,CSS,JavaScript" />
	<meta name="author" content="Brent Berghmans" />
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<script src="/~brentberghmans/src/scripts/topScroll.js" type="text/JavaScript"></script>
	<meta name="viewport" content="width=device-width" />
	<title>Edit comment</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<?php 
	if(isset($_SESSION['rights']) && ($_SESSION['rights'] == "mod" || $_SESSION['rights'] == "admin") && isset($_POST['commentid']) && $_POST['commentid'] != null) {
	?>
	<form class='basic_form' action='/~brentberghmans/src/scripts/editComment.php' method='POST'>
		<?php
		echo "<input type='hidden' name='commentid' value='". $_POST['commentid'] . "' />";
		include '/home/brentberghmans/secure/DB_INFO.php';

		//Connectie maken met DB
		try {
			$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
		}
		catch (PDOException $e) {
			return "dberror";
		}

		$conn = $conn->prepare("SELECT content, eventid FROM comments WHERE commentid = :commentid ;");
		$conn->bindValue(':commentid', $_POST['commentid']);

		if($conn->execute()) {
			$row = $conn->fetch(PDO::FETCH_BOTH);
		}

		echo "<textarea name='content'>" . $row['content'] . "</textarea>";
		echo "<input type='hidden' name='eventid' value='" . $row['eventid'] . "' />";
		echo "<input type='submit' />";

		?>
	</form>
	<?php
	}
	?>
</div>
</body>
</html>