<html>
<head>
	<title> Contact Us</title>
	<link rel="stylesheet" href="style/style.css">
	<link rel="stylesheet" href="style/stylemenu.css">
	<style>
						
		
body {font-family: Arial, Helvetica, sans-serif;}
* {box-sizing: border-box;}


select, textarea {
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

input[type=submit]:hover {
  background-color: #45a049;
}

.container {
  border-radius: 5px;
  background-color: #f2f2f2;
  padding: 20px;
  width: 100%
 
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

			<section>	
				<article>
				<div class="container">
				<H1>  </H1>
					<h2>My Contact</h2>
					<br>
					<p> Joel Okpara </p>
					<p> IS448 Final Project ITE468 </p>
					<p> Email: joelo1@umbc.edu </p>
					<p> Contact: 678-999-8212 </p><br>
				</div>
				</article>
			<article>

				<div class="container">
				  <form action="sendcontact.php">
					<label for="fname">First Name</label>
					<input class="prettyText" type="text" id="fname" name="firstname" placeholder="Your name.."><br>

					<label for="lname">Last Name</label>
					<input class="prettyText" type="text" id="lname" name="lastname" placeholder="Your last name.."><br>

					<label for="country">Country</label>
					<select id="country" name="country">
					  <option value="canada">Canada</option>
					  <option value="usa">USA</option>
					</select><br>

					<label for="subject">Subject</label>
					<input class="prettyText" type="text" id="subject" name="subject" placeholder="Subject.."><br>
					
					<label for="Message">Message</label>
					<textarea id="message" name="message" placeholder="Write your message.." style="height:200px"></textarea><br>

					<input type="submit" value="Submit">
				  </form>
				</div>
			</article>
			</section>
	</main>
	
	<footer>
		<center>
			Footer information
		</center>
	</footer>
</body>
</html>