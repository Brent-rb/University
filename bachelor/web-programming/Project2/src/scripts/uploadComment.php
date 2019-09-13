<?php
include '/home/brentberghmans/secure/DB_INFO.php';
$answer = "";

try {
	$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
}
catch (PDOException $e) {
	$answer = $answer . "Kon geen verbinding maken met de database, probeer later nog eens.<br />";
	return;
}

$query = $conn->prepare("INSERT INTO comments(userid, eventid, content) VALUES ( :userid , :eventid , :content );");
$query->bindValue(':userid', $_POST['userid']);
$query->bindValue(':eventid', $_POST['eventid']);
$query->bindValue(':content', addslashes(htmlentities($_POST['content'])));

if($query->execute())
	header('Location: ' . $_REQUEST['url']);
else
	$answer = $answer . "Kon de query niet uitvoeren.<br />";

?>

<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<title>Comment</title>
	<?php
		echo "<meta http-equiv='refresh' content='5;url=" . $_REQUEST['url'] . "' />";
	?>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div class="basic_textbox">
		<?php
			echo $answer;
			echo "<a href='" . $_REQUEST['url'] . "'>U wordt doorverwezen naar de start pagina, klik hier als dit niet gebeurd in 5 seconden.</a>";
		?>
	</div>
</div>
</body>
</html>