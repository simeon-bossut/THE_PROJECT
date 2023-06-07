<?php include'language.php'; ?>

<nav>

  <div id="menucontenu">

    <input type="checkbox" />
    
    <!-- BURGER BUTTON -->
    <span></span>
    <span></span>
    <span></span>
    

    <ul id="menu">

      <a href="home.php"><li><?php  echo getLanguage("Accueil","Home");  ?></li></a>
	    
      <?php if(isset($_SESSION["authentifie"]) &&  $_SESSION["authentifie"] == true) { ?>
	    
        <a href="logout.php"><li><?php  echo getLanguage("Déconnexion","Logout");  ?></li></a>
	    
      <?php } else { ?>
	 
        <a href="login.php"><li><?php  echo getLanguage("Connexion","Login");  ?></li></a>
	    
      <?php } ?>

      <a href="level.php"><li><?php  echo getLanguage("Niveaux","Levels");  ?></li></a>
      <a href="ranking.php"><li><?php  echo getLanguage("Classement","Ranking");  ?></li></a>
      <a href="setting.php"><li><?php  echo getLanguage("Paramètres","Settings");  ?></li></a>
    </ul>
  </div>
</nav>
