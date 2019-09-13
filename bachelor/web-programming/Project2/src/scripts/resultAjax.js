function updateResults() {
    var array = document.getElementsByTagName("input");
    var name;
    var tags;
    var organisator;
    var subid;
    var city;
    var postcode;
    var temp;

    for(var i = 0; i < array.length; i++) {
        temp = array[i].getAttribute("name");

        if(temp == "name")
            name = array[i].value;
        else if(temp == "tags")
            tags = array[i].value;
        else if(temp == "organisator")
            organisator = array[i].value;
        else if(temp == "city")
            city = array[i].value;
        else if(temp == "postcode")
            postcode = array[i].value;
    }

    var select = document.getElementsByTagName("select")[0];
    subid = select.options[select.selectedIndex].value;

    var string = "/~brentberghmans/src/scripts/getEventTable.php?";

    if(typeof name != "undefined")
        string += "name=" + name;
    if(typeof tags != "undefined")
        string += "&tags=" + tags;
    if(typeof organisator != "undefined")
        string += "&organisator=" + organisator;
    if(typeof subid != "undefined")
        string += "&subid=" + subid;
    if(typeof city != "undefined")
        string += "&city=" + city;
    if(typeof postcode != "undefined")
        string += "&postcode=" + postcode;


    var xmlhttp=new XMLHttpRequest();
    xmlhttp.onreadystatechange=function() {
        if (xmlhttp.readyState==4 && xmlhttp.status==200) {
          document.getElementById("resultaten").innerHTML=xmlhttp.responseText;
        }
    }
    xmlhttp.open("GET", string, true);
    xmlhttp.send();
}   