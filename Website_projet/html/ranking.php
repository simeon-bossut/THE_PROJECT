<?php session_start(); ?>


<!DOCTYPE html>
<html lang="en">

<head>

	<?php include("head.php"); ?>

	<title>The Crate Stacker - Leaderboard</title>

	<link rel="stylesheet" href="../CSS/ranking.css">

</head>



<body>

	<?php include("nav.php"); require("request.php"); ?>


	<header>
		<h1><?php  echo getLanguage("Classement","Leaderboard");  ?></h1>
	</header>


	<main>

		<div class="container">
			<img src="../Images/Leader Board.png">

			<div id="containerUL">
				<div id="containerBox">

					<?php
					try {

						$resultat = request("SELECT * FROM acc ORDER BY score DESC", false);

						$rank = 1;

						foreach ($resultat as $row) {
							echo "<div class='boardElem'>";
							if($rank==1){
										echo"<span> <img src='../Images/gold_medal.svg'/> </span>";
							}
							else if($rank==2){
								echo"<span> <img src='../Images/argent_medal.svg'/> </span>";
					}
							else if($rank==3){
										echo"<span> <img src='../Images/bronze_medal.svg'/> </span>";
							}
							else{echo"<span>$rank</span>";}
													echo"<span>$row[pseudo]</span>
													<span>$row[score]</span>
												</div>";

							$rank += 1;

						}

					} catch (Exception $e) {
						die("Erreur : " . $e->getMessage());
					}

					?>

				</div>
			</div>
		</div>
	</main>

	<?php include("footer.php"); ?>

</body>

</html>
