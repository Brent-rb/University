<?php

uploadForm();

function uploadFiles($id, $conn) {
	$valid_formats = array("jpg", "png", "gif", "bmp");
	$max_file_size = 1024*1000*5; //100 kb
	$path = "/home/brentberghmans/public_html/img/uploads/"; // Upload directory
	$count = 0;

	echo "Started with file upload.<br />";

	if(isset($_FILES['files']['name'])) {
		$filename = "/home/brentberghmans/public_html/img/uploads/lastUpload.txt";

		if(!file_exists($filename)) {
			$number = 0;
		}
		else {
			$filehandle = fopen($filename, 'r') or die ("Can't open file.");
			$number = (int)(fgets($filehandle));
			fclose($filehandle);
		}

		// Loop $_FILES to exeicute all files
		foreach ($_FILES['files']['name'] as $f => $name) {     
		    if ($_FILES['files']['error'][$f] == 4) {
		        continue; // Skip file if any error found
		    }	       
		    if ($_FILES['files']['error'][$f] == 0) {	           
		        if ($_FILES['files']['size'][$f] > $max_file_size) {
		        	echo "File size too big.<br />";
		            continue; // Skip large files
		        }
				elseif( ! in_array(pathinfo($name, PATHINFO_EXTENSION), $valid_formats) ){
					echo "Invalid format.<br />";
					continue; // Skip invalid file formats
				}
		        else{ // No error found! Move uploaded files 
					$ext = pathinfo($_FILES['files']['name'][$f], PATHINFO_EXTENSION);
					$realPath = $path.($number + $count).".".$ext;
					$htmlPath = "/~brentberghmans/img/uploads/" . ($number + $count) . "." . $ext;
		            if(move_uploaded_file($_FILES["files"]["tmp_name"][$f], $realPath)) {
		            	$count++; // Number of successfully uploaded file
		            	$query = $conn->prepare("INSERT INTO eventImages(eventid, ImagePath) VALUES (:id, :htmlpath);");
		            	$query->bindValue(':id', $id);
		            	$query->bindValue(':htmlpath', $htmlPath);

		            	if($query->execute())
		            		echo "Uploaded file: " . $realPath . "<br/>";
		            	else
		            		print_r($conn->errorinfo());

		            }
		        }
		    }
		    else {
		    	echo "Errors happened.<br />";
		    }
		}

		$filehandle = fopen($filename, 'w') or die ("Can't open file.");
		fwrite($filehandle, "" . ($number + $count) . "\n");

		fclose($filehandle);

		header('Location: /~brentberghmans/event/index.php?eventid=' . $id);
	}
	else {
		echo "No files uploaded.";
	}
}

function uploadForm() {
	$eventname = addslashes($_REQUEST['eventname']);
	$startdate = $_REQUEST['startdate'];

	echo "Date: " . $startdate . " <br />";

	$enddate = $_REQUEST['enddate'];
	$street = addslashes($_REQUEST['street']);
	$city = addslashes($_REQUEST['city']);
	$zip = $_REQUEST['postcode'];
	$price = addslashes(nl2br($_REQUEST['price']));
	$description = addslashes(nl2br($_REQUEST['description']));
	$website = addslashes($_REQUEST['website']);
	$tags = addslashes($_REQUEST['tags']);
	$subid = (int)$_REQUEST['subcat'];
	$organisator = addslashes($_REQUEST['organisator']);


	include '/home/brentberghmans/secure/DB_INFO.php';

	try {
		$conn = new PDO("pgsql:host=" . $DB_HOST . ";dbname=" . $DB_DB, $DB_USR , $DB_PW);
	}
	catch (PDOException $e) {
		return "dberror";
	}

	echo "Starting upload<br />";	
	$query = $conn->prepare("INSERT INTO event (startdate, enddate, street, city, postcode, description, tags, name, price, website, subid, organisator) VALUES (:startdate, :enddate, :street, :city, :postcode, :description, :tags, :name, :price, :website, :subid, :organisator);");
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
	if($query->execute()) {
		$id = $conn->lastInsertId('event_eventid_seq');
		echo "Uploaded text information.<br />";
		uploadFiles($id, $conn);
		header('Location: /~brentberghmans/event/index.php?eventid=' . $id);
	}
	else {
		print_r($conn->errorinfo());
	}
}

?>