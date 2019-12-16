<?php
session_start();
if (isset($_SESSION['loggedin']) && $_SESSION['loggedin'] == true) {
    echo "<H3>Welcome to the member's area, " . $_SESSION['username'] . "!</H3>";
} else {
    header("Location: index.html");
}
?>