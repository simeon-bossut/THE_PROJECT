<?php session_start();
include 'language.php';

require("connexion.php");

require("request.php");

$resBack;
$resBody;
$resHat;

try {

  if(isset($_SESSION) && isset($_SESSION['email'])) {

    $res = request("SELECT * FROM acc WHERE email = ?", true, array($_SESSION['email']));

    $id_back = $res['id_back'];
    $id_dude = $res['id_dude'];
    $id_hat  = $res['id_hat'];

    $resBack = request("SELECT url FROM background WHERE id = ?", true, array($id_back));
    if($resBack!=false)
      $resBack= $resBack[0];
    else{
      $resBack = 'bg_factory';
    }

    
    $resHat  = request("SELECT url FROM hat WHERE id = ?", true, array($id_hat));
    if($resHat!=false)
      $resHat= $resHat[0];
    else{
      $resHat = null;
    }

    $resBody = request("SELECT url FROM body WHERE id = ?", true, array($id_dude));
    if($resBody!=false)
      $resBody= $resBody[0];
    else{
      $resBody = 'character_default';
  }
  }

  else {
    $resBack = 'bg_factory';
    $resHat = null;
    $resBody = 'character_default';
  }
} 

catch (Exception $e) {
	die("Erreur : " . $e->getMessage());
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

    <div class="gameTemplate" style="background-image: url('../Images/<?php echo $resBack; ?>.jpg');">

      <div class="victoryScreen">
        <div class="victoryBox">
          <div class="victoryTitle">Victory</div>
          <div class="victoryInfo">
            <div class="victoryInfoContent" id="timerVictory">
              <img src="../Images/timerIcon.svg">
              <span>18:54</span>
            </div>
            <div class="victoryInfoContent" id="moveVictory">
              <img src="../Images/movesIcon.svg">
              <span>23</span>
            </div>
          </div>
          <div class="victoryInfo">
            <div class="victoryInfoContent" id="xpVictory">
              <img src="../Images/xpIcon.svg">
              <span>500</span>
            </div>
            <div class="victoryInfoContent" id="coinsVictory">
              <img src="../Images/coinsIcon.png">
              <span>670</span>
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
