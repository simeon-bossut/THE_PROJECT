<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
	<title>Crapescrapers</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>My Website</title>
    <link rel="stylesheet" href="../CSS/login.css">
    <link rel="icon" href="./favicon.ico" type="image/x-icon">
  </head>
  <body>
  <?php include("nav.php"); ?>
    <header>
        <h1>Sign up portal</h1>
    </header>
    <main>
        <form class="form" action="newacc.php" method="post">
            <div class="form_div">
                <label>Email (login):</label>
                <input class="field_class" name="email" type="text" placeholder="Your Email"  maxlength="40" required >
				
				<label>Votre pseudonyme!:</label>
                <input class="field_class" name="pseudo" type="text" placeholder="Pseudo" required pattern= "^[A-Za-z ']+$" maxlength="40" required >
				
				<label class="input" >Civilité :</label>
				<input type="radio" name="civility" id="male" value="M" required /><label for="male">Monsieur</label>
				<input  type="radio" name="civility" id="female" value="Mme" required /><label for="female">Madame</label>
				<br> <br>
				
                <label>Password:</label>
                <input id="pass" class="field_class" name="password" type="password" placeholder="Your password" required >
				
				 <label>Confirm your password:</label>
                <input id="pass" class="field_class" name="password2" type="password" placeholder="Your password" required>
                <button class="bouton" type="submit" name="add">Go!</button>
				<br><br>
            </div>
			
        </form>
    </main>
	
		<?php include("footer.php"); ?>
	
</body>
