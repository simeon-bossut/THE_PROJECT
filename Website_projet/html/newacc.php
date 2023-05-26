<?php

function valider_donnees($donnee)
{
	$donnee = trim($donnee);
	$donnee = stripslashes($donnee);
	$donnee = htmlspecialchars($donnee);
	return $donnee;
}

require("request.php");


if (isset($_POST["add"])) {

	try {

		$pseudo = valider_donnees($_POST["pseudo"]);
		$civility = valider_donnees($_POST["civility"]);
		$email = valider_donnees($_POST["email"]);
		$password2 = valider_donnees($_POST["password"]);
		$password3 = valider_donnees($_POST["password2"]);


		if ($password2 == $password3) {
			$resultat = request("SELECT * FROM acc WHERE email = :email", false, array(':email' => $email));

			// If the email doesn't exist yet
			if (count($resultat) == 0) {
				request("INSERT INTO acc (email,pseudo,civility,password) VALUES(:email,:pseudo,:civility,:password)", true, array(
					':email' => $email,
					':pseudo' => $pseudo,
					':civility' => $civility,
					':password' => $password2
				)
				);

				header("Location:login.php");
			} else {
				setcookie("email_error", '1', time() + 60);

				header("Location:signup.php");
			}

		} else {
			setcookie("password_error", '1', time() + 60);

			header("Location:signup.php");
		}

	} catch (Exception $e) {
		die("Erreur : " . $e->getMessage());
	}

}

?>