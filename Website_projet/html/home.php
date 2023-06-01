<?php session_start();
include 'language.php';

require("connexion.php");
if(isset($_SESSION["authentifie"]) && $_SESSION["authentifie"] == true){
	try{
	$reqPrep2 = "SELECT id_back FROM acc WHERE email= :email";
	$req = $conn->prepare($reqPrep2);
	$req->execute(array(
			':email' => $_SESSION["email"]));
	$id = $req->fetch()[0];
	}catch (Exception $e) {
	die("Erreur : " . $e->getMessage());
}
}
else{
	$id=1;
}
try {
			$reqPrep = "SELECT url FROM background WHERE id_back= :id";
			$req = $conn->prepare($reqPrep); //Préparer la requete
			$req->execute(array(
			':id' => $id)); //Executer la requete

			$resultat = $req->fetch(); //récupération du résultat 

}catch (Exception $e) {
	die("Erreur : " . $e->getMessage());
}
$id_hat =0;
$id_dude = 0;
if(isset($_SESSION["authentifie"]) && $_SESSION["authentifie"] == true){
    $reqhat = "SELECT id_hat FROM acc WHERE email= :email";
    $req = $conn->prepare($reqhat);
    $req->execute(array(
			':email' => $_SESSION["email"])); //Executer la requete

      $id_hat = $req->fetch()[0];


      $reqdude = "SELECT id_dude FROM acc WHERE email= :email";
      $req = $conn->prepare($reqdude);
      $req->execute(array(
        ':email' => $_SESSION["email"])); //Executer la requete
  
        $id_dude = $req->fetch()[0];


        $requrlhat = "SELECT url FROM hat WHERE id= :id";
        $req = $conn->prepare($requrlhat);
          $req->execute(array(':id' => $id_hat));
          $url_hat = $req->fetch()[0];
        $_SESSION["url_hat"]= $url_hat;

        $requrldude = "SELECT url FROM body WHERE id= :id";
        $req = $conn->prepare($requrldude);
        $req->execute(array(':id' => $id_dude));
        $url_dude = $req->fetch()[0];
        $_SESSION["url_dude"]= $url_dude;

}

?>




<!DOCTYPE html>
<html lang="en">

<head>

  <?php include("head.php"); ?>

  <title>The Crate Stacker</title>

  <link rel="stylesheet" href="../CSS/home.css">

</head>

<body <?php if (!isset($_SESSION['isOnWebsite']) || !$_SESSION['isOnWebsite']) {
        echo 'style="overflow: hidden"';
      } ?>>


  <?php if (!isset($_SESSION['isOnWebsite']) || !$_SESSION['isOnWebsite']) { ?>

    <div class="frontDis">
      <img src="../Images/complete_logo.png" id="crateStackLogo">

      <div id="pressKeyText">Click to continue</div>
    </div>

    <script src="script.js" defer></script>

  <?php } ?>

  <?php if (!isset($_SESSION['isOnWebsite']) || !$_SESSION['isOnWebsite']) {
    $_SESSION['isOnWebsite'] = true;
    echo '<div class="backDis hidden">';
  } else {
    echo '<div class="backDis">';
  } ?>

    <nav>
    <div class="buttonsLogo">
      <a href="conceptor.php">
        <div class="buttonLogo"><?php echo getLanguage("Créateur de niveau", "Level Creator");  ?></div>
      </a>
      <a href="setting.php">
        <div class="buttonLogo"><?php echo getLanguage("Paramètres", "Settings");  ?></div>
      </a>
		</div>
		<div class="buttonsLogo">
    <a href=""><img src="../Images/complete_logo.png" id="logo"></a>
		</div>
    <div class="buttonsLogo">
      <a href="ranking.php">
        <div class="buttonLogo"><?php echo getLanguage("Classement", "Leaderboards");  ?></div>
      </a>
      <?php if (isset($_SESSION["authentifie"]) &&  $_SESSION["authentifie"] == true) { ?>
      <a href="logout.php">
        <div class="buttonLogo"><?php echo getLanguage("Déconnexion", "Logout");  ?></div>
      </a>

      <?php
      } else {  ?>
        <a href="login.php">
          <div class="buttonLogo"><?php echo getLanguage("Connexion/incription", "Login/sign up");  ?></div>
        </a>
      <?php  } ?>
    </div>
  </nav>

  <main>

    <div class="gameTemplate" style="background-image: url('<?php echo $resultat[0];?>');">

      <div class="victoryScreen">
        <div class="victoryBox">
          <div class="victoryTitle">Congratulations</div>

        <div class="victoryBrownBG">

          <div class="victoryInfo">
            <div class="victoryInfoContent" id="timerVictory">Time : 18:54</div>
            <div class="victoryInfoContent" id="moveVictory">Moves : 24</div>
          </div>
          <div class="victoryScores">
            <div class="victoryScoresInfo" id="xpVictory">XP : +500</div>
            <div class="victoryScoresInfo" id="coinsVictory">Coins : +500</div>
          </div>

        </div>

          <div class="victoryLevel">Level : 24</div>
        </div>
      </div>

      <div class="secondPlate">
        <div class="box">
          <div class="view">
            <div id="characterBodyIcon"></div>
            <div id="characterHatIcon"></div>
          </div>
          <a href="customization.php" id="skinButton"><?php echo getLanguage("PERSONNALISER", "CUSTOM");  ?></a>
        </div>
      </div>

      <div id="mainPlate"></div>

      <div class="secondPlate">
        <div class="box">
          <div class="view" id="povBox">
            <div class="viewBox" id="povBoxContent"></div>
          </div>
          <p>Point Of View</p>
        </div>
      </div>

    </div>

    <div style="display: none;" id="musicPlayer">

      <audio id="bgMusic"></audio>

      <button id="prevMus" onclick="prevMusic()">PREV</button>
      <button id="pausePlay" onclick="playPause()">||</button>
      <button id="nextMus" onclick="nextMusic()">NEXT</button>

    </div>



    <div class="creamBG">
      <h2 class="titleContainer"> <?php echo getLanguage("QU'EST CE QUE C'EST", "WHAT IS IT");  ?></h2>
      <p> <?php echo getLanguage("Le Crate Stacker est similaire à Skyscrapers, qui est un jeu de puzzle qui consiste à placer des bâtiments sur une grille carrée avec quelques indices sur les côtés.", "The Crate Stacker is similar to Skyscrapers, which is a puzzle game that involves placing buildings on a square grid with some clues on the sides.");  ?></p>
    </div>

    <div class="brownBG">
      <h2 class="titleContainer"><?php echo getLanguage("Le but", "The Goal");  ?></h2>

      <div class="containerContent">
        <iframe src="https://www.youtube.com/embed/Ww3HbHMnJ5g" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>
        <p> <?php echo getLanguage("Le but de Skyscrapers est de placer un gratte-ciel dans chaque case, avec une hauteur comprise entre 1 et N, de sorte qu'aucun gratte-ciel dans la même rangée ou colonne n'ait le même nombre d'étages.", "The goal of Skyscrapers is to place a skyscraper in each square, with a height between 1 and N, so that no two skyscrapers in the same row or column have the same number of floors.");  ?></p>
      </div>

      <div class="containerContent">
        <p> <?php echo getLanguage("Notez que les gratte-ciel les plus hauts bloquent la vue des gratte-ciel inférieurs derrière eux. Les hommes sur la colline doivent voir le nombre de bâtiments marqués devant eux.", "Note that the tallest skyscrapers block the view of the lower skyscrapers behind them. The men on the hill must see the number of buildings that are marked in front of them."); ?> </p>
        <img src="../images/skyscraper_stage.png">
      </div>

    </div>

    <div class="creamBG">
      <h2 class="titleContainer"><?php echo getLanguage("notre jeu", "our game");  ?></h2>
      <p><?php echo getLanguage("Dans Crate Stacker, on n'empile pas des étages de gratte-ciel mais des caisses stockées dans un entrepôt, le but reste le même : empiler nos caisses en voyant le nombre de caisses sur les côtés de notre grille.", "In Crate Stacker, we don't stack skyscraper floors but crates stored in a warehouse, the goal remains the same: stack our crates while seeing the number of crates on the sides of our grid.");  ?></p>
    </div>

  </main>

  <?php if (isset($_SESSION['isOnWebsite']) && $_SESSION['isOnWebsite']) {
    include("footer.php");
  } ?>

  </div>


  <?php include("game.php"); ?>
  <script src="music.js"></script>


</body>

</html>
