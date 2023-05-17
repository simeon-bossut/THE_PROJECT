<?php

session_start();
$find = true;
try {
	if (isset($_POST["con"])) {
		//echo "ça marche omg";
		require("connexion.php");
		    $login = $_POST["login"];
			$password = $_POST["password"];
			$reqPrep = "SELECT * FROM acc"; //La requere SQL: SELECT
			$req = $conn->prepare($reqPrep); //Préparer la requete
			$req->execute(); //Executer la requete

			$resultat = $req->fetchALl(PDO::FETCH_ASSOC); //récupération du résultat 
			foreach ($resultat as $row) {
				if ($row["password"] == $password && $row["email"] == $login){
					        $_SESSION["authentifie"] = true;
							$_SESSION["email"] = $row["email"];
							$_SESSION["civility"] = $row["civility"];
							setcookie("email", $row["email"], time() + 60 * 60 * 24 * 30);
							header("Location: game.php");
									}
			
			else{
				$find = false;
			}
			}
	}
}catch (Exception $e) {
die("Erreur : " . $e->getMessage());}

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

  <?php include("nav.php"); ?>

  <header>
    <h1>login portal</h1>
  </header>
  
  <main>
    <form class="form" action="" method="post">
      <div class="form_div">
        <label>Login:</label>
        <input class="field_class" name="login" type="text" placeholder="Your Email" autofocus>
        <label>Password:</label>
        <input id="pass" class="field_class" name="password" type="password" placeholder="Your password">
        <button class="bouton" type="submit" name="con">Go!</button>
	
          <?php if (!$find) {
            echo '<div style="font-size:14px;color:red;margin-top:20px;text-align:center"> <p>login or password is invalid</p> </div>';
          }
          ?>

      </div>
      <div class="newacc">
        <p>you don't have an account yet? <a href="signup.php">Sign up!</a></p>
      </div>
    </form>
  </main>
	
		<?php include("footer.php"); ?>
	
</body>

</html>
