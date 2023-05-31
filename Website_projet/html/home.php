<?php session_start();
include 'language.php';
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
    <a href=""><img src="../Images/complete_logo.png" id="logo"></a>
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
      <?php } ?>
    </div>
  </nav>

  <main>

    <div class="gameTemplate" style="background-image: url('../Images/bg_factory.jpg');">

      <div id="thirdPlate">
        <div id="box2">
          <div id="skinBox">
            <div id="characterBody"></div>
            <div id="characterHat"></div>
          </div>
        </div>
        <div id="buttonBox">
          <a href="customization.php" id="skinButton"><?php echo getLanguage("CUSTOM", "PERSONNALISER");  ?></a>
        </div>
      </div>

      <div id="mainPlate"></div>

      <div id="secondPlate">
        <div id="box">
          <div id="view">
            <div id="viewBox"></div>
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


  <script src="game.js"></script>
  <script src="music.js"></script>


</body>

</html>