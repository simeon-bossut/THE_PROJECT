<?php
session_start();
$find = false;
$havemeail = false;
function valider_donnees($donnee) {
    $donnee = trim($donnee);
    $donnee = stripslashes($donnee);
    $donnee = htmlspecialchars($donnee);
    return $donnee;
}

$true_password = valider_donnees($_POST["true_password"]);
$password1 = valider_donnees($_POST["password1"]);
$password2 = valider_donnees($_POST["password2"]);
$login = valider_donnees($_POST["login"]);
$pseudo = valider_donnees($_POST["pseudo"]);

require("request.php");

// Email editing
if(isset($_POST["edit_mail"])) {
	try {
		
		if(!isset($_SESSION['email'])) {
			setcookie("email_edit_error", '1', time() + 60);
			header("Location:setting.php");
		}
		
		$res = request("SELECT * FROM acc WHERE email = :email", false, array(':email' => $_SESSION['email']));

		// If account has been found
		if(count($res) == 1) {
			request("UPDATE acc SET email = :newEmail WHERE email = :email", false, array(':email' => $_SESSION['email'], 'newEmail' => $_POST['email']));
		
			$_SESSION['email'] = $_POST["email"];

			header("Location:setting.php");
		}

		else {
			setcookie("email_edit_error", '1', time() + 60);
			header("Location:setting.php");
		}
	}

	catch (Exception $e) {
		die("Erreur : " . $e->getMessage());
	}
}


// Pseudo editing
if(isset($_POST["edit_pseudo"])) {
	try {
		
		if(!isset($_SESSION['pseudo']))
			return;
		
		$res = request("SELECT * FROM acc WHERE pseudo = :pseudo", false, array(':pseudo' => $_SESSION['pseudo']));

		// If account has been found
		if(count($res) == 1) {
			request("UPDATE acc SET pseudo = :pseudo WHERE email = :email", false, array(':email' => $_SESSION['email'], 'pseudo' => $_POST['pseudo']));
		
			$_SESSION['pseudo'] = $_POST["pseudo"];

			header("Location:setting.php");
		}
	}

	catch (Exception $e) {
		die("Erreur : " . $e->getMessage());
	}
}


// Pseudo editing
if(isset($_POST["edit_pass"])) {
	try {
		
		if(!isset($_SESSION['email'])) {
			setcookie("password_edit_error", '1', time() + 60);
			header("Location:setting.php");
		}
		
		if($_POST['newPassword1'] != $_POST['newPassword2']) {
			setcookie("password_edit_error2", '1', time() + 60);
			header("Location:setting.php");
		}

		$res = request("SELECT * FROM acc WHERE email = :email AND password = :pass", false, array(':email' => $_SESSION['email'], ':pass' => $_POST['oldPassword']));

		// If account has been found
		if(count($res) == 1) {
			request("UPDATE acc SET password = :newPassword WHERE password = :password", false, array(':password' =>  $_POST['oldPassword'], ':newPassword' => $_POST['newPassword1']));
		
			$_SESSION['pseudo'] = $_POST["pseudo"];

			header("Location:setting.php");
		}

		else {
			setcookie("password_edit_error", '1', time() + 60);
			header("Location:setting.php");
		}
	}

	catch (Exception $e) {
		die("Erreur : " . $e->getMessage());
	}
}