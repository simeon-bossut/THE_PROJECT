<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
	<title>Crate Stacker connexion</title>
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
        <form class="form" action="" method=" post">
            <div class="form_div">
                <label>Login:</label>
                <input class="field_class" name="login_txt" type="text" placeholder="Your Email" autofocus>
                <label>Password:</label>
                <input id="pass" class="field_class" name="password_txt" type="password" placeholder="Your password">
                <button class="bouton" type="submit" form="login_form">Go!</button>
            </div>
            <div class="newacc">
                <p>you don't have an account yet? <a href="signup.php">Sign up!</a></p>
            </div>
        </form>
    </main>
	
		<?php include("footer.php"); ?>
	
</body>
