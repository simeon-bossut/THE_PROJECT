<?php session_start(); ?>

<!DOCTYPE html>
<html lang="en">

<head>

	<?php include("head.php"); ?>

	<title>The Crate Stacker - Customization</title>

	<link rel="stylesheet" href="../CSS/test.css">

</head>

<body>

	<?php include("nav.php"); ?>
	<main>

		<header>
			<h1>Custom your game </h1>
		</header>

		<div class="creamBG">
			<h2 class="titleContainer">Custom your game background</h2>

			<div class="containerContent">
				<div id="textContent">
					<select>
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
		</div>

		<div class="creamBG">
			<h2 class="titleContainer">Custom your character</h2>

			<div class="containerContent">
				<div id="textContent">
					<select>
						<option class="1" src="../Images/test1.jpg">Option 1</option>
						<option class="2" src="../Images/test2.jpg">Option 2</option>
						<option class="3" src="../Images/test3.jpg">Option 3</option>
						<option class="4" src="../Images/test4.jpg">Option 4</option>
						<option class="5" src="../Images/test5.jpg">Option 5</option>
					</select>

					<p class="para">Choose your cosmetics to dress up your character! Wide choices are available. Grab a cool hat?
						A serious one? An impressive? Choose your style and use your imagination </p>
				</div>

				<img class="img_back">
			</div>
		</div>

		<!--
		<div class="creamBG">	
		<h1>Custom your game background </h1>
		<div class="box" class="containerContent">
		
			<select>
			<option class = "1" src="../Images/test1.jpg">Option 1</option>
			<option class = "2" src="../Images/test2.jpg">Option 2</option>
			<option class = "3"  src="../Images/test3.jpg">Option 3</option>
			<option class = "4" src="../Images/test4.jpg">Option 4</option>
			<option class = "5" src="../Images/test5.jpg">Option 5</option>
			</select>
		</div>
		
		<span id="selected"></span>
		
		<div class="containerContent">
		<p>Choose your favorite game screen, don't settle for the basics, demand the best, here's what universe you want to transport yourself to </p>
		<img class="img_back">
		</div>
		</div>-->
	</main>
	<?php include("footer.php"); ?>


</body>

</html>
<script>

	var optionSelector = document.querySelector("select");

	function changeBgImg() {
		//document.querySelector("#selected").textContent = optionSelector.options[optionSelector.selectedIndex].getAttribute("src");
		let id = optionSelector.options[optionSelector.selectedIndex].getAttribute("class");
		document.cookie = `background=${id};60*60*24*30`;
		let src = optionSelector.options[optionSelector.selectedIndex].getAttribute("src");

		document.querySelector("img").setAttribute('src', src);
	}

	changeBgImg();

	optionSelector.addEventListener("change", e => {
		changeBgImg();
	});


</script>