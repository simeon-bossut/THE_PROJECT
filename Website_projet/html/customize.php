<?php 
session_start();
if( !isset($_SESSION["authentifie"]) ||  $_SESSION["authentifie"] == false){
	header("Location:error.php");
}
?>

<!DOCTYPE html>
<html lang="en">

  <head>

		<?php include("head.php"); ?>

		<title>The Crate Stacker - Customization</title>

		<link rel="stylesheet" href="../CSS/customize.css">

  </head>

<body>

</body>


</html>