<?php 
session_start();
if( !isset($_SESSION["authentifie"]) ||  $_SESSION["authentifie"] == false){
	header("Location:error.php");
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
	<title>The Crate Stacker Login</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="../CSS/login.css">
  <link rel="icon" href="./favicon.ico" type="image/x-icon">
</head>

<body>

</body>


</html>