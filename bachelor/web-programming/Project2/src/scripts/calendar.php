<?php
function printDay($conn, $day, $month, $year) {
	echo "<div class='day'>";
	$found = false;
	$date = mktime(0, 0, 0, $month, $day, $year);
	$query = $conn->prepare("SELECT eventid, name, startdate, enddate FROM event;");
	if($query->execute() && checkdate($month, $day, $year)) {
		while($row = $query->fetch(PDO::FETCH_BOTH)) {
			$start = strtotime($row['startdate']);
			$end = strtotime($row['enddate']);

			if($date >= $start && $date <= $end) {
				$found = true;
				echo "<a href='/~brentberghmans/event/index.php?eventid=" . $row['eventid'] .  "'>" . stripslashes($row['name']) . "</a>";
			}
		}
	}

	if(!$found)
		echo "<p>Geen evenementen op deze dag.<p>";
	echo "</div>";
}

function printMonth($conn, $month, $year) {
	$day = 1;
	echo "<table id='calendar'>";
	echo "<tr><th>Dag</th>";
	echo "<th>" . date('F', mktime(0, 0, 0, $month, $day, $year)) . "</th></tr>";
	while(checkdate($month, $day, $year)) {
		echo "<tr><td><a href='/~brentberghmans/calendar/?day=" . $day . "&amp;month=" . $month . "&amp;year=" . $year . "'>" . $day . "</a></td><td>";
		printDay($conn, $day, $month, $year);
		echo "</td></tr>";
		$day++;
	}
	echo "</table>";
}
?>