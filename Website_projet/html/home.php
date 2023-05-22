<?php session_start(); ?>

<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
	<title>The Crate Stacker</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="icon" href="../Images/Crate.png" type="image/x-icon">
  <link rel="stylesheet" href="../CSS/home.css">
</head>

  <body <?php if(!isset($_SESSION['isOnWebsite']) || !$_SESSION['isOnWebsite']) { echo 'style="overflow: hidden"'; } ?> >
		

  <?php if(!isset($_SESSION['isOnWebsite']) || !$_SESSION['isOnWebsite']) { ?>

    <div class="frontDis">
      <img src="../Images/complete_logo.png" id="crateStackLogo">

      <div id="pressKeyText">Press any key to continue</div>
    </div>

    <script src="script.js" defer></script>

    <?php } ?>

    <?php if(!isset($_SESSION['isOnWebsite']) || !$_SESSION['isOnWebsite']) {
      $_SESSION['isOnWebsite'] = true;
      echo '<div class="backDis hidden">'; 
    } else {
      echo '<div class="backDis">';
    } ?>

    <nav>
      <div class="buttonsLogo">
        <a href="conceptor.php"><div class="buttonLogo">Level Creator</div></a>
        <a href="settings.php"><div class="buttonLogo">Settings</div></a>
      </div>
      <a href=""><img src="../Images/complete_logo.png" id="logo"></a>
      <div class="buttonsLogo">
        <a href="ranking.php"><div class="buttonLogo">Leaderboard</div></a>
        <a href="login.php"><div class="buttonLogo">Login / Sign up</div></a>
      </div>
    </nav>

    <main>

      <div class="gameTemplate">

        <canvas id="mainPlate"></canvas>

        <canvas id="secondPlate"></canvas>

      </div>

      <div  style="display: none;" id="musicPlayer">

      <audio id="bgMusic"></audio>

        <button id="prevMus" onclick="prevMusic()">PREV</button>
        <button id="pausePlay" onclick="playPause()">||</button>
        <button id="nextMus" onclick="nextMusic()">NEXT</button>

      </div>

      
      
      <div class="creamBG">
        <h2 class="titleContainer">What is it ?</h2>
        <p>The Crate Stacker is similar to Skyscrapers, which is a puzzle game that involves placing buildings on a square grid with some clues on the sides.</p>
      </div>
      
      <div class="brownBG">
        <h2 class="titleContainer">The Goal</h2>

        <div class="containerContent">
          <iframe src="https://www.youtube.com/embed/Ww3HbHMnJ5g" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>  
          <p>The goal of Skyscrapers is to place a skyscraper in each square, with a height between 1 and N, so that no two skyscrapers in the same row or column have the same number of floors.</p>
        </div>

        <div class="containerContent">
          <p>Note that the tallest skyscrapers block the view of the lower skyscrapers behind them. The men on the hill must see the number of buildings that are marked in front of them.</p>
          <img src="../images/skyscraper_stage.png">
        </div>

      </div>

      <div class="creamBG">
        <h2 class="titleContainer">Our Game</h2>
        <p>In Crate Stacker, we don't stack skyscraper floors but crates stored in a warehouse, the goal remains the same: stack our crates while seeing the number of crates on the sides of our grid.</p>
      </div>

    </main>
    
    <?php if(isset($_SESSION['isOnWebsite']) && $_SESSION['isOnWebsite']) { include("footer.php"); } ?>

    </div>

    <script src="music.js"></script>

</body>
</html>