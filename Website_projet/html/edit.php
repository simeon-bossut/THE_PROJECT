<?php
session_start();
$find = false;
$havemeail = false;
function valider_donnees($donnee)
{
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

if (isset($_POST["Modifier"])){
	
	try {
		require("connexion.php");
	
		    $req_Prep = "SELECT * FROM acc WHERE email = :login";
        $req = $conn->prepare($req_Prep);
        $req->execute([":login" => $login]);
        $info = $req->fetch();
				if(count($info) !=0){
				if($info["password"] == $true_password){
					if($password1 == $password2){
						$find = true;
					}
					else{
							setcookie("password_edit_error2", '1', time() + 60);
							header("Location:setting.php");
					}
					
				}
				else{
					setcookie("password_edit_error", '1', time() + 60);
					header("Location:setting.php");
				}
				}

	
	}catch (Exception $e) {
	die("Erreur : " . $e->getMessage());}
	
}

//--------------------------------------------------------------------------------//

if (isset($_POST["Modifier"])){
	
	try {
		require("connexion.php");
			$reqPrep = "SELECT * FROM acc"; //La requere SQL: SELECT
			$req = $conn->prepare($reqPrep); //Préparer la requete
			$req->execute(); //Executer la requete

			$resultat = $req->fetchAll(PDO::FETCH_ASSOC); //récupération du résultat 
			foreach ($resultat as $row) {
				
				if($row["email"]== $login && $row["email"]!= $_SESSION["email"]){
					$havemeail = true;
				}
			}
			if($havemeail==true){
					setcookie("email_edit_error", '1', time() + 60);
					header("Location:setting.php");
			}


	}catch (Exception $e) {
	die("Erreur : " . $e->getMessage());}
	
}

//------------------------------------------------------------------------------------------//

if($havemeail && !$find){
	try{
		require("connexion.php");
		 $req = "UPDATE acc SET email = :login, pseudo = :pseudo, password = :password1 WHERE email =:email_session ";
     $query = $conn->prepare($req);
		 $query->execute([
            ":login" => $login,
            ":pseudo" => $pseudo,
            ":password1" => $password1,
            ":email_session" => $_SESSION["email"]
        ]);
		
		
		
	}catch (Exception $e) {
	die("Erreur : " . $e->getMessage());}
	header("Location:logout.php");
}

?>