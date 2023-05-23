<?php session_start(); ?>


<!DOCTYPE html>
<html lang="en">

  <head>

		<?php include("head.php"); ?>

		<title>The Crate Stacker - Leaderboard</title>

		<link rel="stylesheet" href="../CSS/ranking.css">

  </head>



  <body>
		
		<?php include("nav.php"); ?>


		<header>
			<h1>Ranking</h1>
		</header>
    
		
		<main>
			<?php
			try{
				require("connexion.php");
				$reqPrep = "SELECT * FROM acc ORDER BY score DESC"; //La requere SQL: SELECT
				$req = $conn->prepare($reqPrep); //Préparer la requete
				$req->execute(); //Executer la requete
				$rank= 1;
				$resultat = $req->fetchALl(PDO::FETCH_ASSOC); //récupération du résultat 
				echo "
				<div id= scroll>
				<table class=container>
								<tr class = first>	
									<th class=header>Rank</th>
									<th class=header>Pseudo</th>
									<th class=header>Score</th>
								</tr>";
				foreach ($resultat as $row) {
						echo "
								<tr>	
									<td>$rank</td>
									<td>$row[pseudo]</td>
									<td>$row[score]</td>
								</tr>";
								
								$rank += 1;
					
				}

				echo "</table> </div>";
				}catch (Exception $e) {
					die("Erreur : " . $e->getMessage());}
	?>
    </main>
	<?php include("footer.php"); ?>

  </body>
</html>
