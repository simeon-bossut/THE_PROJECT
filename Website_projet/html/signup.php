<!DOCTYPE html>
<html lang="en">
    <head>
    
        <?php include("head.php"); ?>

		<title>The Crate Stacker - Sign Up</title>

		<link rel="stylesheet" href="../CSS/signup.css">

    </head>

    <body>

  <?php include("nav.php"); ?>

    <header>
        <h1><?php  echo getLanguage("portail d'inscription","Sign up portal");  ?></h1>
    </header>

    <main>
        <form class="form" action="newacc.php" method="post">
            <div class="form_div">
                <label>Email (login):</label>
                <input class="field_class" name="email" type="text" placeholder="Your Email"  maxlength="40" required >

				<?php if (isset($_COOKIE["email_error"])) {echo '<div style="font-size:14px;color:red;text-align:center"> <p>this email address is already in use</p> </div>';
				setcookie("email_error", "", time() - 3600);} ?>
				
				<label><?php  echo getLanguage("Pseudonyme :","Pseudonym :");  ?></label>
                <input class="field_class" name="pseudo" type="text" placeholder="Pseudo" required pattern= "^[A-Za-z ']+$" maxlength="40" required >
				
				<label class="input" ><?php  echo getLanguage("Civilité","Civility :");  ?></label>
				<input type="radio" name="civility" id="male" value="M" required /><label for="male">Mr</label>
				<input  type="radio" name="civility" id="female" value="Mme" required /><label for="female">Mrs</label>
				<br> <br>
				
                <label><?php  echo getLanguage("Mot de passe :","Password :");  ?></label>
                <input id="pass" class="field_class" name="password" type="password" placeholder="Your password" required >
				
				<label><?php  echo getLanguage("Confirmez votre mot de passe :","Confirm your password :");  ?></label>
                <input id="pass" class="field_class" name="password2" type="password" placeholder="Your password" required>
                

				<?php if (isset($_COOKIE["password_error"])) {echo '<div style="font-size:14px;color:red;text-align:center"> <p>please choose the same password</p> </div>';
				setcookie("password_error", "", time() - 3600);} ?>

                <button class="bouton" type="submit" name="add"><?php  echo getLanguage("Insciption!","Sign Up!");  ?></button>
				
            </div>
        </form>
    </main>
	
		<?php include("footer.php"); ?>
	
</body>

</html>
