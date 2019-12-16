<?php
include 'member.php';
// Show MyGuests Data

require 'dbcon.php';

// define variables and set to empty values
$newsid = $ca = $hl = $au = $da = $im = $de = "";

$ca = $_POST['ca'];
$hl = $_POST['hl'];
$au = $_POST['au'];
$da = $_POST['da'];
$im = $_POST['im'];
$de = $_POST['de'];

$sql1 = "SELECT newsid FROM tblNews_FA08019";
$result = $conn->query($sql1);
$newsid = $result->num_rows + 1;


  $sql = "INSERT INTO tblNews_FA08019 (newsid, newscatid, newsheadline, newsauthor, newsdate, newsimage, newsdetails )
  VALUES 
  ($newsid, $ca, '$hl', '$au', '$da', '$im', '$de')";
  
if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

header('Location: displaynews.php');
?>