<head><title> Display Contact </title> 
<link rel=stylesheet href=style.css> 
</head>

<?php
include 'member.php';


require 'dbcon.php';

$sql = "SELECT * FROM  tblContact_FA08019";
$result = $conn->query($sql);

echo "<Center>";
echo "<BR>";
Echo "<H2><BR><BR><BR>
<A Href=page1.php> [ Home ] </A></a></H2>";
echo "<BR>";
echo "<BR>";
echo "<HR>";

echo "<h2>Data from Contact table</h2> <Br>";

echo "<Table border=0 width=50%>";
echo "<TR bgcolor=#85e085>";
echo "<TD> Contact ID </TD><TD> Full Name </TD><TD>Date - Country </TD> <TD> Subject </TD> <TD> Message </TD>";
echo "</TR>";

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
		echo "<TR>";
		echo "<TD>";
        echo $row["contactid"];
		echo "</TD>";
		echo "<TD>";
        echo $row["contactfullname"];
		echo "</TD>";
		echo "<TD>";
        echo $row["contactdatecountry"];
		echo "</TD>";
		echo "<TD>";
        echo $row["contactsubject"];
		echo "</TD>";
		echo "<TD>";
		echo $row["contactmessage"];
		echo "</TD>";
		echo "</TR>";
    }
} else {
    echo "0 results";
}


echo "</Table>";
echo "</Center>";

$conn->close();



?>
