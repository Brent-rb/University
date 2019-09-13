<!DOCTYPE html>
<html>
<head>
	<title>Register</title>
</head>
<body>
<p>
	<?php
	$taken = false;
	$name = $_REQUEST["rname"];
	$password = $_REQUEST["rpassword"];

	$file = "/home/brent/Documents/localhost/logins.txt";
	$handle = fopen($file, 'r') or die("Cannot open file: " . $file);

	while(($line = fgets($handle, 4096)) != false && !$taken) {
		if(strstr($line, "username:$name"))
			$taken = true;
	}
	fclose($handle);
	
	if($taken) {
		echo "Username taken, pick a new one.";
		die();
	}

	

	$handle = fopen($file, 'a') or die ("Cannot open file: " . $file);

	fwrite($handle, "username:$name|password:$password\n");

	fclose($handle);

	echo "Registered succesfully.";

	?>
</body>
</html>