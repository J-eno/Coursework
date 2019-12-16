<html>
<head>
	<title> New Site - Search </title>
	<link rel="stylesheet" href="style/style.css">
	<link rel="stylesheet" href="style/stylemenu.css">

</head>

<body>
		<header class="banner">
	<img src="images/logo.png">  

	<div class="panel panel-nav">
		<center>
			<ul>
			<li> <a href="index.php"> Home </a> </li>
			<li> <a href=""> Archive </a> </li>
			<li> <a href=""> Contact Us </a> </li>
			<li> <a href=""> Login </a> </li>
			<li>  <div class="search">
							<Form action="search.php">
							<input type="text" name="search" size="20" height="24">
							<input type="image" src="images/search.png" alt="Submit" width="24" height="24">
							</Form>
							</div>	 
			</li>
			</ul>
		</center>
	</div>
	</header>
	
	<main>
	
	<?php


require 'dbcon.php';
//echo "Connected successfully";

$id = "";
$id = $_GET['search'];

//$sql = "SELECT * from tblnews LEFT JOIN tblcategory ON tblnews.newscatid = tblcategory.catid where newsheadline like %".$id."% or newsdetails like ".$id."";
$sql = "SELECT * from tblNews_FA08019 LEFT JOIN tblCategory_FA08019 ON tblNews_FA08019.newscatid = tblCategory_FA08019.catid where newsheadline like '%".$id."%' or newsdetails like '%".$id."%'  or newsauthor like '%".$id."%'";
//echo $sql;
// SELECT * FROM table1 LEFT JOIN table2 ON table1.id=table2.id;
$result = $conn->query($sql);

    while($row = $result->fetch_assoc()) 
	{
	
	echo 	"
			<section>	
				<article>
					<BR>
					<h2> ".$row["newsheadline"]." </h2>
					<p> ".substr($row["newsdetails"],0,300)." </p>
					<p><br><br><a href=details.php?id=".$row["newsid"].">Details</a><br><br></p>
				</article>
			</section>";
		
	}
	
$conn->close();

	?>
	
	</main>
	
	<footer>
		<center>
			Footer information
		</center>
	</footer>
</body>
</html>