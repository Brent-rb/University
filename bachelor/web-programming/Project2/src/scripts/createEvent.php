<?php

$answer = uploadForm();

function uploadFiles($id, $conn) {
	$answer = "";
	$valid_formats = array("jpg", "png", "gif", "bmp");
	//$max_file_size = 1024*1000*5; //100 kb
	$path = "/home/brentberghmans/public_html/img/uploads/"; // Upload directory
	$count = 0;

	if(isset($_FILES['files']['name'])) {
		$imageqry = $conn->prepare("SELECT * FROM lastImageID;");
		if($imageqry->execute()) 
			$row = $imageqry->fetch(PDO::FETCH_BOTH);

		$number = (int)$row['lastimageid'];

		// Loop $_FILES to exeicute all files
		foreach ($_FILES['files']['name'] as $f => $name) {     
		    if ($_FILES['files']['error'][$f] == 4) {
		    	$answer = $answer . "Error in bestand: " . $_FILES['files']['name'][$f] . "<br />";
		        continue; 
		    }	       
		    if ($_FILES['files']['error'][$f] == 0) {	           
		        /*if ($_FILES['files']['size'][$f] > $max_file_size) {
		        	$answer = $answer . "Bestand te groot: ". $_FILES['files']['name'][$f] ." <br />";
		            continue; // Skip large files
		        }*/
				if(!in_array(pathinfo($name, PATHINFO_EXTENSION), $valid_formats) ){
					$answer = $answer .  "Verkeerd bestandsformaat: " . pathinfo($name, PATHINFO_EXTENSION) . "<br />";
					continue; // Skip invalid file formats
				}
		        else { // No error found! Move uploaded files 
					$ext = pathinfo($_FILES['files']['name'][$f], PATHINFO_EXTENSION);
					$realPath = $path.($number + $count).".".$ext;
					$htmlPath = "/~brentberghmans/img/uploads/" . ($number + $count) . "." . $ext;
		            if(move_uploaded_file($_FILES["files"]["tmp_name"][$f], $realPath)) {
		            	$count++; // Number of successfully uploaded file
		            	$query = $conn->prepare("INSERT INTO eventImages(eventid, ImagePath, realPath) VALUES (:id, :htmlpath, :realpath);");
		            	$query->bindValue(':id', $id);
		            	$query->bindValue(':htmlpath', $htmlPath);
		            	$query->bindValue(':realpath', $realPath);

		            	if(!$query->execute())
		            		$answer = $answer . "Kon file: " . $_FILES['files']['name'][$f] . " niet uploaden.<br />";
		            }
		        }
		    }
		}

		$imageqry = $conn->prepare("UPDATE lastImageID SET lastimageid = :lastimageid ;");
		$imageqry->bindValue(':lastimageid', $number + $count);
		$imageqry->execute();

		header('Location: /~brentberghmans/event/index.php?eventid=' . $id);
		die();
	}
}

function uploadForm() {
	$answer = "";
	$eventname = addslashes($_REQUEST['eventname']);
	$startdate = $_REQUEST['startdate'];
	$enddate = $_REQUEST['enddate'];
	$street = addslashes($_REQUEST['street']);
	$city = addslashes($_REQUEST['city']);
	$zip = $_REQUEST['postcode'];
	if(isset($_REQUEST['sponsor']))
		$sponsor = '1';
	else
		$sponsor = '0';
	$price = addslashes(nl2br($_REQUEST['price']));
	$description = str_replace("[youtube]" , "<iframe src=\"" , $_REQUEST['description']);
	$description = str_replace("www.youtube.com/watch?v=", "www.youtube.com/embed/", $description);
	$description = str_replace("[/youtube]", "\" allowfullscreen></iframe>", $description); 
	$description = addslashes(nl2br($description));
	$website = addslashes($_REQUEST['website']);
	$tags = addslashes($_REQUEST['tags']);
	$subid = (int)$_REQUEST['subcat'];
	$organisator = addslashes($_REQUEST['organisator']);


	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		return "Kon niet verbinden met de database.<br />";
	}

	$query = $conn->prepare("INSERT INTO event (startdate, enddate, street, city, postcode, description, tags, name, price, website, subid, organisator, sponsor) VALUES (:startdate, :enddate, :street, :city, :postcode, :description, :tags, :name, :price, :website, :subid, :organisator, :sponsor);");
	$query->bindValue(':name', $eventname);
	$query->bindValue(':startdate', $startdate);
	$query->bindValue(':enddate', $enddate);
	$query->bindValue(':street', $street);
	$query->bindValue(':city', $city);
	$query->bindValue(':postcode', $zip);
	$query->bindValue(':description', $description);
	$query->bindValue(':tags', $tags);
	$query->bindValue(':price', $price);
	$query->bindValue(':website', $website);
	$query->bindValue(':subid', $subid);
	$query->bindValue(':organisator', $organisator);
	$query->bindValue(':sponsor', $sponsor);
	if($query->execute()) {
		$id = $conn->lastInsertId('event_eventid_seq');
		return uploadFiles($id, $conn);
	}
	else {
		print_r($conn->errorInfo());
		return "Kon de query niet uitvoeren.<br />";
	}
}

?>


<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="/~brentberghmans/styles/generalStyle.css" type="text/css" /> 
	<meta http-equiv='refresh' content='5;url=/~brentberghmans/event/create.php' />
	<title>Create Evenement</title>
</head>
<body>
<?php
include "/home/brentberghmans/public_html/src/scripts/header.php";
?>
<div id="content">
	<div class="basic_textbox">
		<?php
		echo $answer;
		echo "<a href='/~brentberghmans/event/create.php'>U wordt doorverwezen naar de start pagina, klik hier als dit niet gebeurd in 5 seconden.</a>";
		?>
	</div>
</div>
</body>
</html>