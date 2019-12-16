<head><title> Display Comment </title> 
<link rel=stylesheet href=style.css> 
</head>

<?php
include 'member.php';


require 'dbcon.php';

$sql = "SELECT * FROM  tblComment_FA08019";
$result = $conn->query($sql);

echo "<Center>";
echo "<BR>";
Echo "<H2><BR><BR><BR>
<A Href=page1.php> [ Home ] </A></a></H2>";
echo "<BR>";
echo "<BR>";
echo "<HR>";

echo "<h2>Data from Comment table</h2> <Br>";

echo "<Table border=0 width=50%>";
echo "<TR bgcolor=#85e085>";
echo "<TD> Comment ID </TD><TD> Comment </TD><TD>News ID </TD> <TD> News Headline </TD> <TD> Show/Hide </TD> <TD> Delete </TD>";
echo "</TR>";

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
		echo "<TR>";
		echo "<TD>";
        echo $row["commentid"];
		echo "</TD>";
		echo "<TD>";
        echo $row["commentdetails"];
		echo "</TD>";
		echo "<TD>";
        echo $row["commentnewsid"];
		echo "</TD>";
		echo "<TD>";
        echo $row["commentnewsheadline"];
		echo "</TD>";
		echo "<TD>";
		if($row["commentshow"] == 0)
		{
			echo "<A href=updatecomment.php?nid=$row[commentid]&show=$row[commentshow]> Show</A>";
		}
		else{
			echo "<A href=updatecomment.php?nid=$row[commentid]&show=$row[commentshow]> Hide </A>";
		}
		echo "</TD>";
		echo "<TD>";
		echo "<A href=delcomment.php?nid=$row[commentid]> <img src=image/delete.gif width=25 height=25  onclick=\"return confirm('Are you sure you want to delete this item?');\"> </A> ";
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
