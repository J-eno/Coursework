<?php
include 'member.php';
// Show MyGuests Data

require 'dbcon.php';

// define variables and set to empty values
$color = "";
$id = "";
$id = $_POST['styleid'];
$color = $_POST['color'];
echo $id;
echo "<BR>";
echo $color;

$sql = "update tblStyle_FA08019 set value='$color' Where styleid=$id";
$conn->query($sql);

$conn->close();


header('Location: displaystyle.php');

?>