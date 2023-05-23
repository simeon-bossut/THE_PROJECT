<?php

session_start(); //D�marrer la session
if (isset($_SESSION["authentifie"])) { // si un utilisateur est authentifi� (session en cours)
	session_unset(); //d�truire les variables de sessions
	session_destroy(); //d�truire la session
	header("Location:home.php");
}

?>
