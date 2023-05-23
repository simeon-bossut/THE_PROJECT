<nav>

  <div id="menucontenu">

    <input type="checkbox" />
    
    <!-- BURGER BUTTON -->
    <span></span>
    <span></span>
    <span></span>
    

    <ul id="menu">

      <a href="home.php"><li>Home</li></a>
	    
      <?php if(isset($_SESSION["authentifie"]) &&  $_SESSION["authentifie"] == true) { ?>
	    
        <a href="logout.php"><li>Log Out</li></a>
	    
      <?php } else { ?>
	 
        <a href="login.php"><li>Log In</li></a>
	    
      <?php } ?>

      <a href="conceptor.php"><li>Level Conceptor</li></a>
      <a href="ranking.php"><li>Ranking</li></a>
      <a href="setting.php"><li>Settings</li></a>
    </ul>
  </div>
</nav>
