<?php session_start(); 
require("connexion.php");?>
<?php include("verifLogin.php"); ?>

<?php require("request.php"); ?>

<?php 

try {

	if(isset($_POST['submitChanges'])) {

		request("UPDATE acc SET id_back = ?, id_dude = ?, id_hat = ? WHERE email = ?", false, array($_POST['bgSelect'], $_POST['bodySelect'], $_POST['hatSelect'], $_SESSION['email']));

	}
	/*
	if(isset($_POST["conf"])){
		header("customization.php");
	}


	
	if(isset($_COOKIE["background"])){
	$reqPrep1 = "UPDATE acc SET id_back= :id WHERE email=:email"; //La requere SQL: SELECT
    $req = $conn->prepare($reqPrep1); //Préparer la requete
    $req->execute(	array(
				':id' => $_COOKIE["background"],
				':email' => $_SESSION["email"]
			)); //Executer la requete

	}


	if(isset($_POST["conf_body"])){
		
		try{
		$reqPrep2 = "UPDATE acc SET id_hat= :id_hat, id_dude= :id_dude WHERE email=:email"; //La requere SQL: SELECT
		$req = $conn->prepare($reqPrep2);
		$req->execute(	array(
			':id_hat' => $_COOKIE["hat"],
			':id_dude' => $_COOKIE["dude"],
			':email' => $_SESSION["email"]
		)); */
}catch (Exception $e) {
	die("Erreur : " . $e->getMessage());
}

?>
<!DOCTYPE html>
<html lang="en">

<head>

	<?php include("head.php"); ?>

	<title>The Crate Stacker - Customization</title>

	<link rel="stylesheet" href="../CSS/customization.css">

</head>

<body>

	<?php include("nav.php"); ?>
	<main>

		<header>
			<h1>Custom your game</h1>
		</header>

		<form action="" method="POST">

		<div class="creamBG">
			<h2>Custom your game background</h2>

			<div class="containerContent">
				<div id="textContent">
					<select id="bgSelect" name="bgSelect">

						<?php
						$acc;
						if(isset($_SESSION['email'])) {
							$acc = request("SELECT * FROM acc WHERE email = ?", true, array($_SESSION['email']));
						}

						$res = request("SELECT * FROM background", false, null);

						foreach($res as $ind=>$val) {
							if(isset($acc) && $acc['id_back'] == $val['id']) 
								echo "<option value='$val[id]' id='$val[url]' selected>$val[name]</option>";
							else
								echo "<option value='$val[id]' id='$val[url]'>$val[name]</option>";
						}
						?>
					</select>

					<p class="para">Choose your favorite game screen, don't settle for the basics, demand the best, here's what
						universe you want to transport yourself to </p>
				</div>
					
				<img class="img_back">

			</div>
		</div>

		<div class="creamBG">
			<h2>Custom your character</h2>

			<div class="containerContent">
				<div id="textContent">
					<div class="formSelect">
						<label>Hat :</label>
						<select id="hatSelect" name="hatSelect">
							<option value="0">None</option>

							<?php
							$res = request("SELECT * FROM hat", false, null);

							foreach($res as $ind=>$val) {
								if(isset($acc) && $acc['id_hat'] == $val['id']) 
									echo "<option value='$val[id]' id='$val[url]' selected>$val[name]</option>";
								else
									echo "<option value='$val[id]' id='$val[url]'>$val[name]</option>";
							}
							?>
						</select>
					</div>

					<div class="formSelect">
						<label>Skin :</label>
						<select id="bodySelect" name="bodySelect">
							<?php
								$res = request("SELECT * FROM body", false, null);

								foreach($res as $ind=>$val) {
									if(isset($acc) && $acc['id_dude'] == $val['id']) 
										echo "<option value='$val[id]' id='$val[url]' selected>$val[name]</option>";
									else
										echo "<option value='$val[id]' id='$val[url]'>$val[name]</option>";
								}
								?>
						</select>
					</div>

					<p class="para">Choose your cosmetics to dress up your character! Wide choices are available. Grab a cool hat?
						A serious one? An impressive? Choose your style and use your imagination </p>
				</div>

				<div class="charBox">

					<img class="hat">
					<img class="body">
					
				</div>

			</div>
		</div>
			<input type="submit" name="submitChanges" value="Save Changes">

						</form>
	</main>
	<?php include("footer.php"); ?>


</body>

</html>
<script>

	var optionSelector = document.querySelector("select#bgSelect");

	var hatSelector = document.querySelector("select#hatSelect");
	var bodySelector = document.querySelector("select#bodySelect");

	function changeBgImg() {
		let id = optionSelector.options[optionSelector.selectedIndex].getAttribute("id");
		document.querySelector(".img_back").setAttribute('src', `../Images/${id}.jpg`);
		 
	}
	
	function changeHat() {
		let id = hatSelector.options[hatSelector.selectedIndex].getAttribute("id");

		if(id) {
			document.querySelector(".hat").setAttribute('src', `../Images/customizations/${id}.svg`);
			document.querySelector(".hat").style.display = 'block';
		}

		else {
			document.querySelector(".hat").style.display = 'none';
		}
	}

	function changeBody() {
		let id = bodySelector.options[bodySelector.selectedIndex].getAttribute("id");
		document.querySelector(".body").setAttribute('src', `../Images/customizations/${id}.svg`);
	}

	changeBgImg();
	changeHat();
	changeBody();


	optionSelector.addEventListener("change", e => {
		changeBgImg();
	});

	hatSelector.addEventListener("change", e => {
		changeHat();
	});

	bodySelector.addEventListener("change", e => {
		changeBody();
	});
</script>
