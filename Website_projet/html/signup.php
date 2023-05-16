<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
	<title>The Crate Stacker Sign Up</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge"> 
    <link rel="stylesheet" href="../CSS/signup.css">
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

				<?php if (isset($_COOKIE["email_error"])) {echo " <style= text_align: center;> <p> this email address is already in use </p>";
				setcookie("email_error", "", time() - 3600);} ?>
				
				<label>Pseudonym :</label>
                <input class="field_class" name="pseudo" type="text" placeholder="Pseudo" required pattern= "^[A-Za-z ']+$" maxlength="40" required >
				
				<label class="input" >Civility :</label>
				<input type="radio" name="civility" id="male" value="M" required /><label for="male">Mr</label>
				<input  type="radio" name="civility" id="female" value="Mme" required /><label for="female">Mrs</label>
				<br> <br>
				
                <label>Password :</label>
                <input id="pass" class="field_class" name="password" type="password" placeholder="Your password" required >
				
				<label>Confirm your password :</label>
                <input id="pass" class="field_class" name="password2" type="password" placeholder="Your password" required>
                <button class="bouton" type="submit" name="add">Sign Up!</button>

				<?php if (isset($_COOKIE["password_error"])) {echo " <style= text_align: center;> <p> please choose the same password </p>";
				setcookie("password_error", "", time() - 3600);} ?>
				
            </div>
        </form>
    </main>
	
		<?php include("footer.php"); ?>
	
</body>

</html>
