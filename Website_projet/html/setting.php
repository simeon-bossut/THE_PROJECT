<?php session_start(); ?>

<?php include("verifLogin.php"); ?>

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
			<h1>Custom your game </h1>
		</header>

		<div class="form">
			<h1 class="settingh1"> Modify your account data </h1>
			
			<form action="edit.php" method="post">
				<div class="form_div">

					<label>Email</label>
					<input class="field_class" name="login" type="text" placeholder="<?php echo $_SESSION["email"]; ?>" required autofocus>

					<?php if (isset($_COOKIE["email_edit_error"])) {
						echo '<div style="font-size:14px;color:red;text-align:center"> <p>This email is already taken</p> </div>';
						setcookie("email_edit_error", "", time() - 3600);
					} ?>
				</div>
				
				<div class="form_div">
					<label>Pseudo</label>
					<input class="field_class" name="pseudo" type="text" placeholder=<?php echo $_SESSION["pseudo"]; ?> required>
				</div>

				<div class="form_div">
					<label>New Password</label>
					<input id="pass" class="field_class" name="password1" type="password" placeholder="New password" required>
					<label>Confirm your new Password :</label>
					<input id="pass" class="field_class" name="password2" type="password" placeholder="New password" required>

					<?php if (isset($_COOKIE["password_edit_error2"])) {
						echo '<div style="font-size:14px;color:red;text-align:center"> <p>Please choose the same password</p> </div>';
						setcookie("password_edit_error2", "", time() - 3600);
					} ?>
					
					
					<label>Confirm old password</label>
					<input id="pass" class="field_class" name="true_password" type="password" placeholder="Your password" required>
					<button class="bouton" type="submit" name="Modifier">Go!</button>

					<?php if (isset($_COOKIE["password_edit_error"])) {
						echo '<div style="font-size:14px;color:red;text-align:center"> <p>Please enter the right password</p> </div>';
						setcookie("password_edit_error", "", time() - 3600);
					} ?>
				</div>
			</form>
		</div>
	</main>

	<?php include("footer.php"); ?>


</body>
</html>