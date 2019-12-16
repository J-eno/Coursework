<?php
include 'member.php';
?>
<HTML>
<Title> Add Article </Title>
<Center>
<H1> Insert New Article Data        ---     <A Href=page1.php> Home </A> </H1>
<Form action=insertnews.php method=post>
<H3> Category <select name=ca>
<?php
require 'dbcon.php';
$sql = "SELECT * from tblCategory_FA08019";
$result = $conn->query($sql);
    while($row = $result->fetch_assoc()) 
	{
	echo "<option value=". $row["catid"] ."> ". $row["catname"]." </option>";
	//echo "<option> ".  ."</option>";
	}
	
$conn->close();

	?>
</select>	



 <Br>
<H3> Headline <Input type=text name=hl> <Br>
<H3> Author <Input type=text name=au> <Br>
<H3> Date <Input type=date name=da> <Br>
<H3> Image <Input type=text name=im> <Br>
<H3> Details <Textarea cols=50 rows=15 name=de> </textarea> <Br>

<Input type=submit value=Submit>
</Form>
</Center>
</HTML>