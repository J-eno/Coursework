<?php
include 'member.php';
?>
<html>
<head>
<link rel=stylesheet href=style.css>
</head>
<body>

<?php
Echo '<a href=logout.php> || Logout  ||</a>';
echo '<br><Center>';
echo '<H1> Admin Home </H1>';

	echo '<br><H3>';
	echo '<br>';
	Echo '<a href=displaycat.php> [ Display Category ]</a>';
	echo '   ---   |   ---   ';
	Echo '<a href=displaynews.php> [ Display NEWS ]</a>';
	echo '   ---   |   ---   ';
	Echo '<a href=displaycomment.php> [ Comments ]</a>';
	echo '   ---   |   ---   ';
	Echo '<a href=displaystyle.php> [ StyleSheet ]</a>';
	echo '   ---   |   ---   ';
	Echo '<a href=displaycontact.php> [ Contacts ]</a>';
	echo '</H3><br>';
	
	
echo '<br></Center>';
?>

</body>
</html>