<?php
include 'member.php';
// Show MyGuests Data

require 'dbcon.php';

// define variables and set to empty values
$catname = "";
$id = "";
$id = $_POST['id'];
$catid = $_POST['ca'];
$hl = $_POST['hl'];
$au = $_POST['au'];
$da = $_POST['da'];
$im = $_POST['im'];
$de = $_POST['de'];

echo $id;
echo "<BR>";
echo $catname;
echo "<BR>";
echo $catid;
echo "<BR>";
echo $hl;

$sql = "update tblNews_FA08019 set newscatid='$catid', newsheadline='$hl', newsauthor='$au', newsdate='$da', newsimage='$im', newsdetails='$de' Where newsid=$id";
$conn->query($sql);

$conn->close();


header('Location: displaynews.php');

?>