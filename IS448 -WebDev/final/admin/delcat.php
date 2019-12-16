<?php
include 'member.php';
// Show MyGuests Data

require 'dbcon.php';

// define variables and set to empty values
$id = "";

$id = $_GET['nid'];
$sql = "Delete FROM tblCategory_FA08019 Where catid=$id";

$conn->query($sql);
$conn->close();


//echo "Data Deleted"
header('Location: displaycat.php');

?>