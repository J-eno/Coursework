<?php
require 'dbcon.php';

// define variables and set to empty values
$firstname = $lastname = $fullname = $date = $country =$datecountry = $subject = $message = $contactid = "";

$firstname = $_GET['firstname'];
$lastname = $_GET['lastname'];
$fullname = $firstname . " " . $lastname;

$date = date('Y-m-d H:i:s');
$country = $_GET['country'];

$datecountry = $date . " - " . $country;

$subject = $_GET['subject'];
$message = $_GET['message'];

$sql1 = "SELECT contactid FROM tblContact_FA08019";
$result = $conn->query($sql1);
$contactid = $result->num_rows + 1;

echo $contactid . "<br>" . $fullname . "<br>" . $datecountry . "<br>" . $subject . "<br>" . $message . "<br>" ;

  $sql = "INSERT INTO tblContact_FA08019 (contactid, contactfullname, contactsubject,  contactmessage, contactdatecountry )
  VALUES 
  ($contactid, '$fullname', '$subject', '$message', '$datecountry')";
  
if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

header('Location: contact.php');
?>