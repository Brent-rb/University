<!DOCTYPE html>
<html>
<head>
	<title>Oef2</title>
</head>
<body>
<form action="2.php" method="post">
Num one: <input type="number" name="num1" />
Num two: <input type="number" name="num2" />
<input type="submit" />
</form>
<?php
if($_REQUEST["num1"])
	$num1 = $_REQUEST["num1"];
if($_REQUEST["num2"])
	$num2 = $_REQUEST["num2"];
if($num1 && $num2)
	echo "<p>Uitkomst: " + ((int)$num1 + (int)$num2) + "</p>";
?>
</body>
</html>