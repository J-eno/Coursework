<?php
echo "
<html>
<head>
	<title> IS448 NEWS-Project </title>
	<link rel=stylesheet href=style/style.css>
	<link rel=stylesheet href=stylemenu/style.css>
";	
	
echo "<style>";

require 'dbcon.php';
$sql = "Select * from tblStyle_FA08019";
$result = $conn->query($sql);
	while($row = $result->fetch_assoc()) 
	{
	If ($row["tag"]=='H1')
	{
	echo "h1 {color:".$row["value"].";}";
	}
	elseif ($row["tag"]=='H2')
	{
	echo "h2 {color:".$row["value"].";}";
	}
	else
	{
	echo "h3 {color:".$row["value"].";}";
	}
	}

echo "body {font-family: Arial, Helvetica, sans-serif;}";
echo"	</style>";

echo" </head>
<body>
	<header class=banner>
	<img src=images/logo.png>  

	<div class=panel panel-nav>
		<center>
			<ul>
			<li> <a href=index.php> Home </a> </li>
			<li> <a href=> Archive </a> </li>
			<li> <a href=contact.php> Contact Us </a> </li>
			<li> <a href=https://swe.umbc.edu/~joelo1/final/admin> Login </a> </li>
			<li>  <div class=search>
							<Form action=search.php>
							<input type=text name=search size=20 height=24>
							<input type=image src=images/search.png alt=Submit width=24 height=24>
							</Form>
							</div>	 
			</li>
			</ul>
		</center>
	</div>
	</header>
	
	
	<main>";
	
	

//echo "Connected successfully";

$sql = "SELECT * from tblNews_FA08019 LEFT JOIN tblCategory_FA08019 ON tblNews_FA08019.newscatid = tblCategory_FA08019.catid";
// SELECT * FROM table1 LEFT JOIN table2 ON table1.id=table2.id;
$result = $conn->query($sql);
$na=0;

    while($row = $result->fetch_assoc()) 
	{
		if ($na==0)
		{echo "<section class=news-nav>";}
//echo $row["id"]." ".$row["firstname"]." ".$row["lastname"]." ".$row["email"]. " - <a href=del.php?nid=".$row["id"]."> Del </a>    - <a href=update.php?nid=".$row["id"]."> Update </a> ". "<BR>";
	echo 	"
			<section>	
				<article>
					<img width=250px height=150px src=images/".$row["newsimage"]." />
					<BR>
					<h2> ".$row["newsheadline"]." </h2>
					<p> ".substr($row["newsdetails"],0,125)." </p>
					<p><br><br><a href=details.php?id=".$row["newsid"].">Details</a><br><br></p>
					<p> Author: ".$row["newsauthor"]." Date: ".$row["newsdate"]."  Category: ".$row["catname"]." </p>
				</article>
			</section>";
		
		$na=$na+1;	
		if ($na==3)
		{echo "</section>";}
	
		if ($na==3)
		{ $na=0;}
	}
	

	
echo "	
	</main>
	
	<footer>
		<center>
			Footer information
		</center>
	</footer>
</body>
</html>
";
$conn->close();

?>