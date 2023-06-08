<?php session_start();
include 'language.php';

require("connexion.php");

require("request.php");

$resBack;
$resBody;
$resHat;

$out;
$out2;
if (isset($_POST["restart"]) && isset($_COOKIE["score_player"])) {
  $score = $_COOKIE["score_player"];
  setcookie("score_player", "", time() - 3600);
  if (isset($_SESSION) && isset($_SESSION['email'])) {
    $res = request("SELECT score FROM acc WHERE email = :email", true, array(":email" => $_SESSION['email']));
    $score += $res["score"];
    $res2 = request("UPDATE acc SET score =:score WHERE email=:email", true, array(":score" => $score, ":email" => $_SESSION["email"]));
  }
}
try {

  if (isset($_SESSION) && isset($_SESSION['email'])) {

    $res = request("SELECT * FROM acc WHERE email = ?", true, array($_SESSION['email']));

    $id_back = $res['id_back'];
    $id_dude = $res['id_dude'];
    $id_hat  = $res['id_hat'];

    $resBack = request("SELECT url FROM background WHERE id = ?", true, array($id_back));
    if ($resBack != false)
      $resBack = $resBack[0];
    else {
      $resBack = 'bg_factory';
    }


    $resHat  = request("SELECT url FROM hat WHERE id = ?", true, array($id_hat));
    if ($resHat != false)
      $resHat = $resHat[0];
    else {
      $resHat = null;
    }

    $resBody = request("SELECT url FROM body WHERE id = ?", true, array($id_dude));
    if ($resBody != false)
      $resBody = $resBody[0];
    else {
      $resBody = 'character_default';
    }
  } else {
    $resBack = 'bg_factory';
    $resHat = null;
    $resBody = 'character_default';
  }

  if (!isset($_COOKIE["dim"])) {
    setcookie("dim", "3", time() + 365 * 24 * 60 * 60, '/');
  }

  if (!isset($_COOKIE["diff"])) {
    setcookie("diff", "0", time() + 365 * 24 * 60 * 60, '/');
  }




  // If user started a new grid (action 1)
  if (!isset($_COOKIE["grid"])) {
    setcookie("diff", "0", time() + 365 * 24 * 60 * 60, '/');
    setcookie("dim",  "3", time() + 365 * 24 * 60 * 60, '/');

    $size;
    if (!isset($_COOKIE['dim']))
      $size = 3;
    else
      $size = $_COOKIE['dim'];

    $diff;
    if (!isset($_COOKIE['diff']))
      $diff = 0;
    else
      $diff = $_COOKIE['diff'];

    exec("cd ../../THE_PROJECT/ && main.exe $size 1 $diff", $newGrid);

    if(!isset($newGrid) || empty($newGrid) || !$newGrid) {
      $playerGrid = $_COOKIE["grid"];
      $playerGrid = str_split($playerGrid);
      array_splice($playerGrid, 1 + $size*4);
      $str = "";
      
      for($i = 0; $i < $size**2; $i++) {
        $str = $str."0";
      }
      
      $playerGrid = join($playerGrid).$str;

      setcookie("grid", $playerGrid, time() + 365*24*60*60, '/');
      setcookie("gridClue", $_COOKIE["grid"], time() + 365*24*60*60, '/');
      //setcookie("originGrid", $_COOKIE["grid"], time() + 365*24*60*60, '/');
    }

    else {
      $playerGrid = $newGrid[0];
      $playerGrid = str_split($playerGrid);
      array_splice($playerGrid, 1 + $size*4);
      $str = "";
      
      for($i = 0; $i < $size**2; $i++) {
        $str = $str."0";
      }
      
      $playerGrid = join($playerGrid).$str;
      setcookie("grid", $playerGrid, time() + 365*24*60*60, '/');
      setcookie("gridClue", $newGrid[0], time() + 365*24*60*60, '/');
      //setcookie("originGrid", $newGrid[0], time() + 365*24*60*60, '/');
    }
  }



  

  // If user asked for a clue (action 2)
  else if(!str_contains($_COOKIE['grid'], "-")) {
    $size;
    if (!isset($_COOKIE['dim']))
      $size = 3;
    else
      $size = $_COOKIE['dim'];

    $Grid;

    // var_dump($_COOKIE["gridClue"]);

    if(!isset($_COOKIE['gridClue']))
      $Grid = "3321123221123000000000";
    else
      $Grid = $_COOKIE['gridClue'];

    $Grid = str_split($Grid);
    $Grid = join(array_splice($Grid, 1));

    $gridClue;

    // do {

      $gridClue = null;

      exec("cd ../../THE_PROJECT/ && main.exe $size 2 $Grid", $gridClue);

      if(!isset($gridClue) || empty($gridClue) || !$gridClue) {
        $str = "";
        for($i = 0; $i < $size**2; $i++) {
          $str = $str."0";
        }

        $gridClue = array($str);
      }

      $gridClue[0] = str_split($gridClue[0]);

      foreach($gridClue[0] as $key=>$val) {
        if(str_split($_COOKIE['gridClue'])[$key] != $val && str_split($_COOKIE['gridClue'])[$key] != 0) {
          $gridClue[0][$key] = str_split($_COOKIE['gridClue'])[$key];
        }
      }
    // } while(join($gridClue[0]) == $_COOKIE['gridClue']);

    $gridClue = join($gridClue[0]);

    setcookie("gridClue", $gridClue, time() + 356 * 24 * 60 * 60, '/');
  }

  // IF USER WANTS THE SOLUTION (action 3)
  else {
    $solution;

    $size;
    if (!isset($_COOKIE['dim']))
      $size = 3;
    else
      $size = $_COOKIE['dim'];

    if(!isset($_COOKIE['gridClue']))
      $Grid = "3321123221123000000000";
    else
      $Grid = $_COOKIE['gridClue'];

    $Grid = str_split($Grid);
    $Grid = join(array_splice($Grid, 1));

    exec("cd ../../THE_PROJECT/ && main.exe $size 3 $Grid", $solution);

    if(!isset($solution) || empty($solution) || !$solution) {
      $str = "";
      for($i = 0; $i < $size**2; $i++) {
        $str = $str."0";
      }

      $solution = array($str);
    }

    $solution = $solution[0];

    setcookie("gridClue", $solution, time() + 356 * 24 * 60 * 60, '/');
  }


} catch (Exception $e) {
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
      <a href="level.php">
        <div class="buttonLogo"><?php echo getLanguage("Niveaux", "Levels");  ?></div>
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

      <div class="popup" id="popup">

        <img src="../Images/crossIcon.svg" class="crossVictory" id="close-popup">
        <img src="../Images/keyboard_popup.png" class="keyboard-pop-up">
      </div>

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
            <!-- <div class="victoryInfoContent" id="coinsVictory">
                <img src="../Images/coinsIcon.png">
                <span>670</span>
              </div> -->
          </div>
          <div class="victoryInfo">
            <form class="form" action="" method="post">
              <button class="victoryRefreshButton" name="restart" onclick="onclickGenerate()">New Grid</button>
            </form>
          </div>
        </div>
      </div>

      <div class="secondPlate">
        <div class="box">
          <div class="view">
            <div id="characterBodyIcon"></div>
            <div id="characterHatIcon"></div>
          </div>

          <a href="customization.php" class="skinButton"><?php echo getLanguage("PERSONNALISER", "CUSTOM");  ?></a>
          <div class="select">
            <div class="selectBox">
              <h2 class="titleselect"><?php echo getLanguage("Taille", "Size");  ?></h2>
              <select name="size">
                <option value="3" <?php if (isset($_COOKIE['dim']) && $_COOKIE['dim'] == 3) {
                                    echo "selected";
                                  } ?>>3*3</option>
                <option value="4" <?php if (isset($_COOKIE['dim']) && $_COOKIE['dim'] == 4) {
                                    echo "selected";
                                  } ?>>4*4</option>
              </select>
            </div>
            <div class="selectBox">
              <h2 class="titleselect"><?php echo getLanguage("Level", "Level");  ?></h2>
              <select name="difficulty">
                <option value="0" <?php if (isset($_COOKIE['diff']) && $_COOKIE['diff'] == 0) {
                                    echo "selected";
                                  } ?>><?php echo getLanguage("Très facile", "Very Easy");  ?></option>
                <option value="1" <?php if (isset($_COOKIE['diff']) && $_COOKIE['diff'] == 1) {
                                    echo "selected";
                                  } ?>><?php echo getLanguage("Facile", "Easy");  ?></option>
                <option value="2" <?php if (isset($_COOKIE['diff']) && $_COOKIE['diff'] == 2) {
                                    echo "selected";
                                  } ?>><?php echo getLanguage("Moyen", "Medium");  ?></option>
                <option value="3" <?php if (isset($_COOKIE['diff']) && $_COOKIE['diff'] == 3) {
                                    echo "selected";
                                  } ?>><?php echo getLanguage("Difficile", "Hard");  ?></option>
              </select>
            </div>
          </div>

          <button onclick="onclickGenerate()" class="skinButton"><?php echo getLanguage("GENERER", "GENERATE");  ?></button>
        </div>
      </div>

      <div id="mainPlate"></div>

      <div class="secondPlate">
        <div class="box">
          <div class="view" id="povBox">
            <div class="viewBox" id="povBoxContent">
              <!--
                <div id="crate1" class="z4 size1"></div>
                <div id="crate2" class="z3 size1"></div>
                <div id="crate3" class="z1 size1"></div>
                <div id="crate4" class="z2 size1"></div>
                -->
            </div>
          </div>
          <p>Point Of View</p>
        </div>
      </div>

    </div>

    <!--
      <div id="musicPlayer">

        <audio id="bgMusic"></audio>

        <button id="prevMus" onclick="prevMusic()">PREV</button>
        <button id="pausePlay" onclick="playPause()">||</button>
        <button id="nextMus" onclick="nextMusic()">NEXT</button>

      </div>
      -->



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
        <img src="../Images/skyscraper_stage.png">
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


  <?php include("game.php"); ?>
  <script src="music.js"></script>


</body>

</html>