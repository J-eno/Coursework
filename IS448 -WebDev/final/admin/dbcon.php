<?php
// Connection

$servername = "studentdb-maria.gl.umbc.edu";
$username = "joelo1";
$password = "joelo1";
$dbname = "joelo1";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

?>