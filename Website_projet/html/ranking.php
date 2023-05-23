<?php session_start();
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
	<title>Crapescrapers</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>My Website</title>
    <link rel="stylesheet" href="../CSS/ranking.css">
    <link rel="icon" href="./favicon.ico" type="image/x-icon">
  </head>
  <body>
		
		<?php include("nav.php"); ?>
    <main>
        <h1>Ranking</h1>
		<br> <br> <br>
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
