<head><title> Style Data </title> 
<link rel=stylesheet href=style.css> 
</head>

<?php
include 'member.php';


require 'dbcon.php';

$sql = "SELECT styleid, tag, value FROM  tblStyle_FA08019";
$result = $conn->query($sql);

echo "<Center>";
echo "<BR>";
Echo "<H2><BR><BR><BR>
<a href=ncat.php > Add New Category         ---     <A Href=page1.php> [ Home ] </A></a></H2>";
echo "<BR>";
echo "<BR>";
echo "<HR>";

echo "<h2>Data from Style table</h2> <Br>";

echo "<Table border=0 width=50%>";
echo "<TR bgcolor=#85e085>";
echo "<TD> Style ID </TD><TD> Tag </TD><TD> Value </TD><TD> </TD> <TD> Color </TD><TD> Update </TD>";
echo "</TR>";

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
		echo "<TR>";
		echo "<TD>";
        echo $row["styleid"];
		echo "</TD>";
		echo "<TD>";
        echo $row["tag"];
		echo "</TD>";
		echo "<TD>";
        echo $row["value"];
		echo "</TD>";
		echo "<TD>";
        echo "";
		echo "</TD>";
		echo "<TD>";
		echo "<Form action=updatestyle.php method=post>";
		echo "<input type=color name=color value=" .$row['value']. ">";
		echo "</TD>";
		echo "<TD>";
		echo "<input type=hidden name=styleid value=" .$row['styleid']. ">";
		echo "<input type=submit value=Update>";
		echo "</Form>";
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
