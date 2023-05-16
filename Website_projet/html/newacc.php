<?php

function valider_donnees($donnee)
{
	$donnee = trim($donnee);
	$donnee = stripslashes($donnee);
	$donnee = htmlspecialchars($donnee);
	return $donnee;
}

if (isset($_POST["add"])) {
	$pseudo = valider_donnees($_POST["pseudo"]);
	$civility = valider_donnees($_POST["civility"]);
	$email = valider_donnees($_POST["email"]);
	$password2 = valider_donnees($_POST["password"]);
	$password3 = valider_donnees($_POST["password2"]);


	if($password2 == $password3){
	try {
	
	require("connexion.php");
		$reqPrep = "INSERT INTO acc (email,pseudo,civility,password)
			VALUES(:email,:pseudo,:civility,:password)";
		$req = $conn->prepare($reqPrep);
		$req->execute(
			array(
				':email' => $email,
				':pseudo' => $pseudo,
				':civility' => $civility,
				':password' => $password2
			)
		);

	$conn = NULL;
	header("Location:login.php");
	} catch (Exception $e) {
		die("Erreur : " . $e->getMessage());
	}
	
	}
	
}

?>