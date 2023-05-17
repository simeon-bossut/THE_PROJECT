<?php if(!isset($_SESSION)){
    session_start();
} ?>
<link rel="stylesheet" href="../CSS/nav.css">
<nav>
  <div id="menucontenu">

    <input type="checkbox" />
    

    <span></span>
    <span></span>
    <span></span>
    

    <ul id="menu">
      <a href="game.php"><li>Home</li></a>
	  <?php if(isset($_SESSION["authentifie"]) &&  $_SESSION["authentifie"] == true) { ?>
	  <a href="logout.php"><li>Deconnexion</li></a>
	  <?php } else{ ?>
	  <a href="login.php"><li>Connexion</li></a>
	  <?php } ?>
      <a href="#"><li>Game</li></a>
      <a href="#"><li>Contact</li></a>
    </ul>
  </div>
</nav>
