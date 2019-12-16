<?php
include 'member.php';
// Show MyGuests Data

require 'dbcon.php';

// define variables and set to empty values
$id = "";
$show = "";

$id = $_GET['nid'];
$show = $_GET['show'];

echo $id . "<br>";
echo $show . "<br>";
if($show == 0)
{
    echo "WE GOT A 0 BOYS";
    $sql = "UPDATE tblComment_FA08019 set commentshow=1 WHERE commentid=$id";
}
else
{
    echo "WE GOT A 1 BOYS";
    $sql = "UPDATE tblComment_FA08019 set commentshow=0 WHERE commentid=$id";    
}

$conn->query($sql);
echo "Updated";
$conn->close();

header('Location: displaycomment.php');

?>