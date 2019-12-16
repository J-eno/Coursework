<?php
include 'member.php';
// Show MyGuests Data

require 'dbcon.php';

// define variables and set to empty values
$catname = "";
$catid = "";

//
//$catid = $result->num_rows;
$sql1 = "SELECT catid FROM tblCategory_FA08019";
$result = $conn->query($sql1);
$catid = $result->num_rows + 1;

$catname = $_POST['cn'];

  $sql = "INSERT INTO tblCategory_FA08019 (catid, catname) VALUES ('$catid','$catname')";
  
if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

header('Location: displaycat.php');
?>