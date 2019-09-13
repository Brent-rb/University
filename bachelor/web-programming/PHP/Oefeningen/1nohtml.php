<?php
mt_srand((double)microtime() * 10000000); //SEED
$getal = mt_rand(0, 4); //Getal

if($getal == 0)
	echo "<p>Dit is een hele mooie zin.</p>";
else if($getal == 1)
	echo "<p>Dit is een niet zo mooie zin.</p>";
else if($getal == 2)
	echo "<p>Deze zin valt nog mee.</p>";
else if($getal == 3)
	echo "<p>En deze zin is gewoon prachtig.</p>";
else 
	echo "<p>Derp</p>";
?>