<?php

function valider_donnees($donnee)
{
	$donnee = trim($donnee);
	$donnee = stripslashes($donnee);
	$donnee = htmlspecialchars($donnee);
	return $donnee;
}

$sameemail= 0;




if (isset($_POST["add"])) {
	$pseudo = valider_donnees($_POST["pseudo"]);
	$civility = valider_donnees($_POST["civility"]);
	$email = valider_donnees($_POST["email"]);
	$password2 = valider_donnees($_POST["password"]);
	$password3 = valider_donnees($_POST["password2"]);


	if($password2 == $password3){
	try {
	
	require("connexion.php");
	$reqPrep1 = "SELECT * FROM acc"; //La requere SQL: SELECT
    $req = $conn->prepare($reqPrep1); //Préparer la requete
    $req->execute(); //Executer la requete
	 $resultat = $req->fetchALl(PDO::FETCH_ASSOC); 
	foreach ($resultat as $row) {
		if($row["email"] == $email){ $sameemail=1;}
	}
	
		if($sameemail==0){
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
		}
		else{
			setcookie("email_error", '1', time() + 60);
			
			
		}
	$conn = NULL;
	if($sameemail==0){
	header("Location:login.php");}
	else{header("Location:signup.php");}
	} catch (Exception $e) {
		die("Erreur : " . $e->getMessage());
	}
	
	}
	else{
		setcookie("password_error", '1', time() + 60);
		header("Location:signup.php");
	}
	
}

?>
