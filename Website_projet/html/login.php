<?php

session_start();
$find = true;

require("request.php");
require("connexion.php");

try {
	if(isset($_POST["con"])) {
		$resultat = request("SELECT * FROM acc WHERE email = :email AND password = :pass", false, array(':email' => $_POST['login'], ':pass' => $_POST['password']));

		if(count($resultat) == 1) {
			$_SESSION["authentifie"] = true;
			$_SESSION["email"] = $resultat[0]["email"];
			$_SESSION["civility"] = $resultat[0]["civility"];
      $id_dude = $resultat[0]["id_dude"];
      $id_hat= $resultat[0]["id_hat"];
      $id_back = $resultat[0]["id_back"];
			$_SESSION["pseudo"] = $resultat[0]["pseudo"];
      header("Location: home.php");
			

			
		}
		
		else {
			$find = false;
		}
	}
}catch (Exception $e) {
	die("Erreur : " . $e->getMessage());
}

?>


<!DOCTYPE html>
<html lang="en">

  <head>

		<?php include("head.php"); ?>

		<title>The Crate Stacker - Log In</title>

		<link rel="stylesheet" href="../CSS/login.css">

  </head>

<body>

  <?php include("nav.php"); ?>

  <header>
    <h1><?php  echo getLanguage("portail de connexion","login portal");  ?></h1>
  </header>
  
  <main>
    <form class="form" action="" method="post">
      <div class="form_div">

        <label>Login:</label>
        <input class="field_class" name="login" type="text" placeholder="<?php  echo getLanguage("Votre email","Your email");  ?>" autofocus>

        <label><?php  echo getLanguage("Mot de passe:","Password:");  ?></label>
        <input id="pass" class="field_class" name="password" type="password" placeholder="<?php  echo getLanguage("Votre mot de passe","Your password"); ?>" required >

        <button class="bouton" type="submit" name="con">Go!</button>
	
				<?php if (!$find) { echo '<div style="font-size:14px;color:red;margin-top:20px;text-align:center"> <p>login or password is invalid</p> </div>'; }	?>

      </div>

      <div class="newacc">
        <p><?php  echo getLanguage("Vous n'avez pas encore un compte? ","You don't have an account yet? ");  ?><a href="signup.php">Sign up!</a></p>
      </div>

    </form>
  </main>
	
	<?php include("footer.php"); ?>
	
</body>

</html>
