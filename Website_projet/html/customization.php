<?php session_start(); 
require("connexion.php");?>
<?php include("verifLogin.php"); ?>
<?php 
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
		)); 
	}catch (Exception $e) {
		die("Erreur : " . $e->getMessage());
	}

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

		<div class="creamBG">
			<h2>Custom your game background</h2>

			<div class="containerContent">
				<div id="textContent">
					<select id="bgSelect">
						<option class="1" src="../Images/bg_factory.jpg">Classic</option>
						<option class="2" src="../Images/bg_factory_chemical.jpg">Chemical</option>
						<option class="3" src="../Images/bg_factory_neon.jpg">Neon</option>
						<option class="4" src="../Images/bg_factory_panda.jpg">???</option>
					</select>

					<p class="para">Choose your favorite game screen, don't settle for the basics, demand the best, here's what
						universe you want to transport yourself to </p>
				</div>
					
				<img class="img_back">

			</div>
			<form class="form" action="" method="post">
			<input type="submit" name="conf">Submit</button>
			</form>
		</div>

		<div class="creamBG">
			<h2>Custom your character</h2>

			<div class="containerContent">
				<div id="textContent">
					<label>Hat :</label>
						<select id="hatSelect">
							<option class="1" >None</option>
							<option class="2" src="../Images/customizations/crown.svg">Crown</option>
							<option class="3" src="../Images/customizations/aureole.svg">Aureole</option>
							<option class="4" src="../Images/customizations/corns.svg">Bull Horns</option>
							<option class="5" src="../Images/customizations/audio_helmet.svg">Headset</option>
							<option class="6" src="../Images/customizations/biker_helmet.svg">Biker Helmet</option>
							<option class="7" src="../Images/customizations/cap.svg">Cap</option>
							<option class="8" src="../Images/customizations/cowboy_hat.svg">Cowboy Hat</option>
							<option class="9" src="../Images/customizations/work_helmet.svg">Construction Helmet</option>
							<option class="10" src="../Images/customizations/miner_helmet.svg">Mining Helmet</option>
							<option class="11" src="../Images/customizations/viking_helmet.svg">Viking Helmet</option>
							<option class="12" src="../Images/customizations/drink_cap.svg">Drink Helmet</option>
							<option class="13" src="../Images/customizations/silver_robot.svg">Silver Robot</option>
							<option class="14" src="../Images/customizations/gold_robot.svg">Gold Robot</option>
						</select>
					<label>Skin :</label>
						<select id="bodySelect">
                            <option class="1" src="../Images/customizations/character_default.svg">Default Character</option>
							<option class="2" src="../Images/customizations/red.svg">Red</option>
							<option class="3" src="../Images/customizations/blue.svg">Blue</option>
							<option class="4" src="../Images/customizations/green.svg">Green</option>
                            <option class="5" src="../Images/customizations/orange.svg">Orange</option>
                            <option class="6" src="../Images/customizations/purple.svg">Purple</option>
                            <option class="7" src="../Images/customizations/yellow.svg">Yellow</option>
                            <option class="8" src="../Images/customizations/green.svg">Cyan</option>
                            <option class="9" src="../Images/customizations/plus_minus.svg">Plus Minus</option>
                            <option class="10" src="../Images/customizations/crate_body.svg">Crate</option>
						</select>

					<p class="para">Choose your cosmetics to dress up your character! Wide choices are available. Grab a cool hat?
						A serious one? An impressive? Choose your style and use your imagination </p>

					<form class="form" action="" method="post">
						<input type="submit" name="conf_body">Submit</button>
					</form>
				</div>

				<div class="charBox">

					<img class="hat">
					<img class="body">
					
				</div>

			</div>
		</div>
	</main>
	<?php include("footer.php"); ?>


</body>

</html>
<script>

	var optionSelector = document.querySelector("select#bgSelect");

	var hatSelector = document.querySelector("select#hatSelect");
	var bodySelector = document.querySelector("select#bodySelect");

	function changeBgImg() {
		//document.querySelector("#selected").textContent = optionSelector.options[optionSelector.selectedIndex].getAttribute("src");
		let id = optionSelector.options[optionSelector.selectedIndex].getAttribute("class");
		document.cookie = `background=${id};60*60*24*30`;
		let src = optionSelector.options[optionSelector.selectedIndex].getAttribute("src");

		document.querySelector(".img_back").setAttribute('src', src);
		 
	}
	
	function changeHat() {
		let src = hatSelector.options[hatSelector.selectedIndex].getAttribute("src");
		let id =hatSelector.options[hatSelector.selectedIndex].getAttribute("class");
		document.cookie = `hat=${id};60*60*24*30`;
		document.querySelector(".hat").style.backgroundImage = `url("${src}")`;
	}

	function changeBody() {
		let src = bodySelector.options[bodySelector.selectedIndex].getAttribute("src");
		let id =bodySelector.options[bodySelector.selectedIndex].getAttribute("class");
		document.cookie = `dude=${id};60*60*24*30`;
		document.querySelector(".body").style.backgroundImage = `url("${src}")`;
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
