<!DOCTYPE html>
<html>
<head>
	<title>Login</title>
</head>
<body>
<p>Registreer</p>
<form action="register.php" method="post">
	<p>Name</p>
	<input type="text" name="rname" />
	<p>Password</p>
	<input type="password" name="rpassword" />
	<input type="submit" />
</form>

<form action="login.php" method="post">
	<p>Name</p>
	<input type="text" name="lname" />
	<p>Password</p>
	<input type="password" name="lpassword" />
	<input type="submit" />
</form>
</body>
</html>