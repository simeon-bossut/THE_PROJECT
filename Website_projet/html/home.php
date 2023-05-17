<?php session_start(); ?>


<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
	<title>The Crate Stacker</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="icon" href="./favicon.ico" type="image/x-icon">
  <link rel="stylesheet" href="../CSS/home.css">
</head>

<?php
  if(!isset($_SESSION['isOnWebsite']) || !$_SESSION['isOnWebsite']) {
?>
  <body style="overflow: hidden">
		
  <div class="frontDis">
    <img src="../Images/complete_logo.png" id="crateStackLogo">

    <div id="pressKeyText">Press any key to continue</div>
  </div>

  <div class="backDis hidden">

	  <?php include("nav.php"); ?>

  </div>

  <main>
    <h1>The Crate Stacker game !</h1>
		<h2>The Crate Stacker is similar to Skyscrapers, which is a puzzle game that involves placing buildings on a square grid with some clues on the sides.</h2>
    <br>
    <div id="part1">
      <iframe width="560" height="315" src="https://www.youtube.com/embed/Ww3HbHMnJ5g" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>  
      <p>The goal of Skyscrapers is to place a skyscraper in each square, with a height between 1 and N, so that no two skyscrapers in the same row or column have the same number of floors.</p>
      <br>
    </div>
    <div id="part2">
      <p>Note that the tallest skyscrapers block the view of the lower skyscrapers behind them. The men on the hill must see the number of buildings that are marked in front of them.</p>
      <img width="560" height="315" src="../images/skyscraper_stage.png">
      <br>
    </div>
    <div id="part3">
      <p>In Crate Stacker, we don't stack skyscraper floors but crates stored in a warehouse, the goal remains the same: stack our crates while seeing the number of crates on the sides of our grid.</p>
    </div>  
  </main>

<?php include("footer.php"); ?>

</body>
  <script src="script.js"></script>
  

<?php
    $_SESSION['isOnWebsite'] = true;
  }

  else { 

    echo '<body>';
    include("nav.php");

?>

<main>
    <h1>The Crate Stacker game !</h1>
		<h2>The Crate Stacker is similar to Skyscrapers, which is a puzzle game that involves placing buildings on a square grid with some clues on the sides.</h2>
    <br>
    <div id="part1">
      <iframe width="560" height="315" src="https://www.youtube.com/embed/Ww3HbHMnJ5g" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>  
      <p>The goal of Skyscrapers is to place a skyscraper in each square, with a height between 1 and N, so that no two skyscrapers in the same row or column have the same number of floors.</p>
      <br>
    </div>
    <div id="part2">
      <p>Note that the tallest skyscrapers block the view of the lower skyscrapers behind them. The men on the hill must see the number of buildings that are marked in front of them.</p>
      <img width="560" height="315" src="../images/skyscraper_stage.png">
      <br>
    </div>
    <div id="part3">
      <p>In Crate Stacker, we don't stack skyscraper floors but crates stored in a warehouse, the goal remains the same: stack our crates while seeing the number of crates on the sides of our grid.</p>
    </div>  
  </main>

  <?php include("footer.php"); ?>
  </body>

  <?php
} 

?>
</html>
