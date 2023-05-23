<?php

if(!isset($_SESSION["authentifie"]) || $_SESSION["authentifie"] == false) {
	header("Location:error.php");
}

?>