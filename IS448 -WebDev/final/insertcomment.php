<?php
require 'dbcon.php';

// define variables and set to empty values
$commentid = $newsid = $hl = $de = "";

$newsid = $_POST['newsid'];
$hl = $_POST['hl'];
$de = $_POST['comment'];

$sql1 = "SELECT commentid FROM tblComment_FA08019";
$result = $conn->query($sql1);
$commentid = $result->num_rows + 1;

echo "The headline is" . $hl;

  $sql = "INSERT INTO tblComment_FA08019 (commentid, commentnewsid, commentnewsheadline,  commentdetails, commentshow )
  VALUES 
  ($commentid, $newsid, '$hl', '$de', 0)";
  
if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

header('Location: details.php?id='.$newsid);
?>