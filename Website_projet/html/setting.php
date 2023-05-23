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

		<title>The Crate Stacker - Settings</title>

		<link rel="stylesheet" href="../CSS/settings.css">

  </head>

<body>

</body>


</html>
