<!DOCTYPE html>
<html>
<head>
	<title>Login</title>
</head>
<body>
	<?php
	$found = false;
	$name = $_REQUEST["lname"];
	$password = $_REQUEST["lpassword"];

	$file = "/home/brent/Documents/localhost/logins.txt";
	$handle = fopen($file, 'r') or die("Cannot open file: " . $file);

	while(($line = fgets($handle, 4096)) != false && !$found) {
		if(strstr($line, "username:$name")) {
			if(strstr($line, "password:$password"))
				$found = true;
			else 
				break;
		}
	}
	fclose($handle);

	if($found)
		echo "You have been granted acces.";
	else
		echo "You shall not pass.";

	?>
</body>
</html>