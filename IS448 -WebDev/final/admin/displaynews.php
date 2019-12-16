<head><title> Display NEWS </title> 
<link rel=stylesheet href=style.css> 
</head>


<?php
include 'member.php';


require 'dbcon.php';

$sql = "SELECT * from tblNews_FA08019 LEFT JOIN tblCategory_FA08019 ON tblNews_FA08019.newscatid = tblCategory_FA08019.catid";
$result = $conn->query($sql);

echo "<Center>";
echo "<BR>";
Echo "<H2><BR><BR><BR>
<a href=nnews.php > Add New NEWS         ---     <A Href=page1.php> [ Home ] </A></a></H2>";
echo "<BR>";
echo "<BR>";
echo "<HR>";

echo "<h2>Data from NEWS table</h2> <Br>";

echo "<Table border=0 width=50%>";
echo "<TR bgcolor=#85e085>";
echo "<TD> Headline </TD><TD> Category_Name </TD><TD> </TD> <TD> Edit </TD> <TD> Delete </TD>";
echo "</TR>";

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
		echo "<TR>";
		echo "<TD>";
        echo $row["newsheadline"];
		echo "</TD>";
		echo "<TD>";
        echo $row["catname"];
		echo "</TD>";
		echo "<TD>";
        echo "";
		echo "</TD>";
		echo "<TD>";
		echo "<A href=updatenews.php?nid=$row[newsid]> <img src=image/edit.gif width=25 height=25> </A>";
		echo "</TD>";
		echo "<TD>";
		echo "<A href=delnews.php?nid=$row[newsid]> <img src=image/delete.gif width=25 height=25  onclick=\"return confirm('Are you sure you want to delete this item?');\"> </A> ";
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
