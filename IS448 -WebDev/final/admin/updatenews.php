<?php
include 'member.php';
// Show MyGuests Data

require 'dbcon.php';

// define variables and set to empty values
$id = "";

$id = $_GET['nid'];
$sql = "SELECT * FROM  tblNews_FA08019 where newsid=$id";
$result = $conn->query($sql);
$conn->query($sql);
$row = $result->fetch_assoc();

$nd = $row["newsdetails"];

echo "<Center>";
echo "<H1> Update Article Details </H1>";
echo "<Form action=updateinsertnews.php method=post>";
echo "<input type=hidden name=id value=$id>";
echo "<H3> Category <select name=ca>";
$sql1 = "SELECT * from tblCategory_FA08019";
$result1 = $conn->query($sql1);
while($row1 = $result1->fetch_assoc()) 
{
    echo "<option value=". $row1["catid"] ."> ". $row1["catname"]." </option>";
    //echo "<option> ".  ."</option>";
}
echo "</select> <BR>";
echo "<H3> Headline <Input type=text name=hl value=\"". $row["newsheadline"] ."\"> <Br>"; 
echo "<H3> Author <Input type=text name=au value=\"". $row["newsauthor"] ."\"> <Br>";
echo "<H3> Date <Input type=date name=da value=". $row["newsdate"] ."> <Br>";  
echo "<H3> Image <Input type=text name=im value=". $row["newsimage"] ."> <Br>"; 
echo "<H3> Details <textarea cols=50 rows=15 name=de>" .$row["newsdetails"]."</textarea> <Br>";
echo "<Input type=submit value=Submit>";
echo "<Form action=displaynews.php><Input type=submit value=Cancel></Form>";

echo "</Form>";
echo "</Center>";

$conn->close();

?>