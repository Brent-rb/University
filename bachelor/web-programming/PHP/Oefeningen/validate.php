<!DOCTYPE html>
<html>
<head>
	<title>validate</title>
</head>
<body>
<?php
$prename = $_REQUEST['voornaam'];
$prename = trim($prename);
$lastname = $_REQUEST['achternaam'];
$lastname = trim($lastname);
$password = $_REQUEST['pw'];
$pcontrol = $_REQUEST['pc'];
$email = $_REQUEST['email'];
$email = trim($email);
$eorde = false;
$porde = true;
$lorde = true;
$pworde = false;
$pcorde = false;



if (preg_match('/^[^\W][a-zA-Z0-9_]+(\.[a-zA-Z0-9_]+)*\@[a-zA-Z0-9_]+(\.[a-zA-Z0-9_]+)*\.[a-zA-Z]{2,4}$/', $email))
	$eorde = true;

if(strlen($prename) > 30 || strlen($prename) == 0)
	$porde = false;
for($i = 0; $i < strlen($prename) && !$porde; $i++) {
	if(!(($prename[$i] >= 'a' && $prename[$i] <= 'z') || ($prename[$i] >= 'A' && $prename[$i] <= 'Z') || $prename[$i] == 'é' || $prename[$i] == 'è' || $prename[$i] == 'à'))
		$porde = false;
}

if(strlen($lastname) > 30 || strlen($lastname) == 0)
	$lorde = false;
for($i = 0; $i < strlen($lastname) && !$porde; $i++) {
	if(!(($lastname[$i] >= 'a' && $lastname[$i] <= 'z') || ($lastname[$i] >= 'A' && $lastname[$i] <= 'Z') || $lastname[$i] == 'é' || $lastname[$i] == 'è' || $lastname[$i] == 'à'))
		$lorde = false;
}


if(strlen($password) > 5)
	$pworde = true;

if(strcmp($password, $pcontrol) == 0)
	$pcorde = true;

if($eorde && $porde && $lorde && $pworde && $pcorde)
	echo "<p>Form approved.</p>";
else
	echo "<p>Form not approved.</p>";

if($eorde)
	echo "Email in orde <br />";
if($porde)
	echo "Voornaam in orde <br/>";
if($lorde)
	echo "Achternaam in orde <br />";
if($pworde)
	echo "paswoord in orde<br />";
if($pcorde)
	echo "contol in orde <br />";

?>
</body>
</html>
