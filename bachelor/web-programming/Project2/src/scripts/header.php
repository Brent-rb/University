<nav id="nav">
	<a href="/~brentberghmans/"><img src="/~brentberghmans/img/ele.jpg" id="banner" alt="banner"/></a>
	<ul id="menubar">
		<?php
		session_start();
		//DB info includen
		include '/home/brentberghmans/secure/DB_INFO.php';

		//Connectie maken met DB
		try {
			$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
		}
		catch (PDOException $e) {
			return "dberror";
		}

		//Query voorbereiden
		$query = $conn->prepare("SELECT hoofdid, name FROM hoofdcat;");
		//Hoofdcategorieen ophalen
		if($query->execute()) {
			while($row = $query->fetch(PDO::FETCH_BOTH)) {
				echo "<li><a href=\"/~brentberghmans/hoofdcat/index.php?hoofdid=" . $row['hoofdid'] . "\">" . $row['name'] . "</a><ul>";

				//Subcat ophalen
				$subquery = $conn->prepare("SELECT * FROM subcat WHERE hoofdid = :id ;");
				$subquery->bindValue(':id', (int)$row['hoofdid']);
				if($subquery->execute())
					while($subrow = $subquery->fetch(PDO::FETCH_BOTH)) {
						echo "<li><a href=\"/~brentberghmans/subcat/index.php?subid=" . $subrow['subid'] . "\">" . $subrow['name'] . "</a>";
						echo "</li>";
				}
				echo "</ul></li>";
			}
		}


		?>
		<li id="search">
			<form action="/~brentberghmans/subcat/index.php" method="GET">
				<input type="text" name="name" />
			</form>
			<ul>
				<li><a href="/~brentberghmans/search/">Geavanceerd zoeken</a></li>
			</ul>
		</li>
		<li id="settings">
			<span><img src="/~brentberghmans/img/setting.png" alt="settings"/></span>
			<ul>
				<?php
				session_start();
				if(isset($_SESSION['username'])) {
					echo "<li><a href=\"/~brentberghmans/acount/?userid=" . $_SESSION['userid'] . "\">" . $_SESSION['username'] . "</a></li><li><a href=\"/~brentberghmans/acount/logout.php\">Log out </a></li>";
					echo "<li><a href='/~brentberghmans/acount/friends.php'>Volg Lijst</a></li>";
					echo "<li><a href='/~brentberghmans/acount/'>Zoek een persoon</a></li>";
				}
				else 
					echo "<li><a href=\"/~brentberghmans/acount/register.php\">Register</a></li><li><a href=\"/~brentberghmans/acount/login.php\">Log In</a></li>";
				if(isset($_SESSION['rights']) && $_SESSION['rights'] == "admin") {
					echo "<li><a href=\"/~brentberghmans/event/create.php\">Creeer evenement</a></li>";
					echo "<li><a href='/~brentberghmans/hoofdcat/create.php'>Creeer Hoofdcategorie</a></li>";
					echo "<li><a href='/~brentberghmans/subcat/create.php'>Creeer Subcategorie</a></li>";
				}
				if(isset($_SESSION['rights']) && ($_SESSION['rights'] == "admin" || $_SESSION['rights'] == "mod")) {
					echo "<li><a href='/~brentberghmans/hoofdcat/edit.php'>Hoofdcategorieen Aanpassen</a></li>";
					echo "<li><a href='/~brentberghmans/subcat/edit.php'>Subcategorieen Aanpassen</a></li>";
				}
				?>
			</ul>
		</li>
		<!--TODO ZOEKEN, OOK RECHTS-->
		<!--TODO Quick Login, Waar plaatsen? -->
	</ul>
</nav>