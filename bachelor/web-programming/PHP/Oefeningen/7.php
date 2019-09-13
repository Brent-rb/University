<!DOCTYPE html>
<html>
<head>
	<script>
	function loadXMLDoc() {
		var ajax = new XMLHttpRequest();	
		ajax.open("GET", "1nohtml.php", true);
		ajax.send();

		ajax.onreadystatechange = function() {
			if(ajax.readyState == 4 && ajax.status == 200)
				document.getElementById("zin").innerHTML = ajax.responseText;
		}

		
	}
	</script>
	<title>Oef7</title>
</head>
<body>
<h2>Random zin:</h2>
<p id="zin"></p>
<button type="button" onclick="loadXMLDoc()">Random Zin</button>
</body>
</html>