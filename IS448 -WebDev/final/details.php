<html>
<head>
	<title> New Site - Details</title>
	<link rel="stylesheet" href="style/style.css">
	<link rel="stylesheet" href="style/stylemenu.css">
	<style>
	body {font-family: Arial, Helvetica, sans-serif;}
	textarea {
  width: 100%;
  padding: 12px;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
  margin-top: 6px;
  margin-bottom: 16px;
  resize: vertical;
}

input[type=submit] {
  background-color: red;
  color: white;
  padding: 12px 20px;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}
	</style>
</head>

<body>
	<header class="banner">
	<img src="images/logo.png">  

	<div class="panel panel-nav">
		<center>
			<ul>
			<li> <a href="index.php"> Home </a> </li>
			<li> <a href=""> Archive </a> </li>
			<li> <a href="contact.php"> Contact Us </a> </li>
			<li> <a href="https://swe.umbc.edu/~joelo1/final/admin"> Login </a> </li>
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

$id = $_GET['id'];

$sql = "SELECT * from tblNews_FA08019 LEFT JOIN tblCategory_FA08019 ON tblNews_FA08019.newscatid = tblCategory_FA08019.catid where newsid=" .$id;
//echo $sql;

// SELECT * FROM table1 LEFT JOIN table2 ON table1.id=table2.id;
$result = $conn->query($sql);
    while($row = $result->fetch_assoc()) 
	{
		
//echo $row["id"]." ".$row["firstname"]." ".$row["lastname"]." ".$row["email"]. " - <a href=del.php?nid=".$row["id"]."> Del </a>    - <a href=update.php?nid=".$row["id"]."> Update </a> ". "<BR>";
	echo 	"
			<section>	
				<article>
					<img width=250px src=images/".$row["newsimage"]." />
					<BR>
					<h2> ".$row["newsheadline"]." </h2>
					<p> ".$row["newsdetails"]." </p>
					<p><br></p>
					<p> Author: ".$row["newsauthor"]." Date: ".$row["newsdate"]."  Category: ".$row["catname"]." </p>
				</article>
			</section>";

	}
	$result = $conn->query($sql);
	$row = $result->fetch_assoc();

	echo 	"
			<section>	
				<article>
					<h3> User Comments </h3> <br>
			";
	$sql1 = "SELECT * FROM tblComment_FA08019 WHERE commentnewsid=$id AND commentshow=1";
	$result1 = $conn->query($sql1);
	while($row1 = $result1->fetch_assoc())
	{
		echo "<p style=color:grey;>" .$row1["commentdetails"] . "</p><br>";
	}


	echo "					
					<Form action=insertcomment.php method=post>
					<input type=hidden name=newsid value=" .$id.">
					<input type=hidden name=hl value=\"" .$row["newsheadline"]. "\">
					<textarea name=comment rows=2 cols=50></textarea>
					<input type=submit value=Comment>
					</Form>
				</article>
			</section>";
	
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