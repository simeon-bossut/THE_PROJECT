	<?php session_start(); ?>

	<?php include("verifLogin.php"); ?>

	<?php
	if (isset($_POST['checked'])) {
		
		if($_POST['checked'] == "fr"){
			setcookie("lang", 'fr', time() + (60*60*24*30*365),'/');
			header("Location:setting.php");
		}
		else{
			setcookie("lang", 'en', time() +(60*60*24*30*365),'/');
			header("Location:setting.php");

		}
	}
	?>
	<!DOCTYPE html>
	<html lang="en">

	<head>

		<?php include("head.php"); ?>

		<title>The Crate Stacker - Settings</title>

		<link rel="stylesheet" href="../CSS/settings.css">

	</head>

	<body>
		<?php include("nav.php"); ?>

		<main>

			<header>
				<h1><?php  echo getLanguage("Paramètres","Settings");  ?> </h1>
			</header>

			<div class="container">
				<div class="choice"> 
				<h2>Choose your language</h2>
					<form action="" method="post">
						<div class="formInputs">
							<div class="lablelg">
								<input type="radio" checked="checked" name="checked"  value="en">
								<img src="../Images/ukflag.png" class="flag" alt="French flag" >
								English
							</div>
							<div class="lablelg">
								<input type="radio"  name="checked" value="fr">
								<img src="../Images/France.png" class="flag" alt="French flag" >
								Français
							</div>
						</div>
						
						<button class="bouton" type="submit" name="Modifier">Choose!</button>
					</form>
				</div>	

				<div class="form">
					<h2><?php  echo getLanguage("Modifie ton compte","Modify your account");  ?></h2>

					<form action="edit.php" method="post">
						<div class="form_div">

							<label>Email</label>
							<input class="field_class" name="email" type="text" placeholder="<?php echo $_SESSION["email"]; ?>" required autofocus>

							<?php if (isset($_COOKIE["email_edit_error"])) {
								echo '<div style="font-size:14px;color:red;text-align:center"> <p>This email is already taken</p> </div>';
								setcookie("email_edit_error", "", time() - 3600);
							} ?>

							<button class="bouton" type="submit" name="edit_mail">Change</button>
						</div>
					</form>

					<form action="edit.php" method="post">				
						<div class="form_div">
							<label>Pseudo</label>
							<input class="field_class" name="pseudo" type="text" placeholder=<?php echo $_SESSION["pseudo"]; ?> required>

							<button class="bouton" type="submit" name="edit_pseudo">Change</button>
						</div>
					</form>

					<form action="edit.php" method="post">
						<div class="form_div">
							<label><?php  echo getLanguage("nouveau mot de passe","New password");  ?></label>
							<input id="pass" class="field_class" name="newPassword1" type="password" placeholder="New password" required>
							<label><?php  echo getLanguage("Confirmez votre nouveau mot de passe","Confirm your new password");  ?></label>
							<input id="pass" class="field_class" name="newPassword2" type="password" placeholder="New password" required>

							<?php if (isset($_COOKIE["password_edit_error2"])) {
								echo '<div style="font-size:14px;color:red;text-align:center"> <p>Please choose the same password</p> </div>';
								setcookie("password_edit_error2", "", time() - 3600);
							} ?>
							
							
							<label><?php  echo getLanguage("Confirmez votre ancien mot de passe","Confirm your old password");  ?></label>
							<input id="pass" class="field_class" name="oldPassword" type="password" placeholder="Your password" required>

							<?php if (isset($_COOKIE["password_edit_error"])) {
								echo '<div style="font-size:14px;color:red;text-align:center"> <p>Please enter the right password</p> </div>';
								setcookie("password_edit_error", "", time() - 3600);
							} ?>

							<button class="bouton" type="submit" name="edit_pass"><?php  echo getLanguage("Modifer","Change");  ?></button>
						</div>
					</form>
				</div>
			</div>
		</main>

		<?php include("footer.php"); ?>


	</body>
	</html>
