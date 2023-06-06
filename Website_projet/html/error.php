<!DOCTYPE html>
<html lang="en">

<head>

  <?php include("head.php"); ?>

  <title>The Crate Stacker - Error</title>

  <link rel="stylesheet" href="../CSS/error.css">

</head>


<body>
  <?php include("nav.php"); ?>
  
  <header>

  </header>

  <main>
    <div class="main-wrapper">
      <picture class="img">
        <img src="../Images/barrel4.JPG" alt="background">
      </picture>
      <div class="error-text">
        <h2><?php  echo getLanguage("J'ai une mauvaise nouvelle pour toi","I got bad news for you");  ?></h2>
        <p> <?php  echo getLanguage("Cette page ne peut être affichée que si vous êtes connecté","This page can only be displayed if you are logged in");  ?></p>
        <span class="input-group-btn">
          <button class="btn" type="button" onclick="window.location.href='login.php';"
					><?php echo getLanguage("Connectez-vous","Please login");  ?></button>
        </span>
      </div>
    </div>

  </main>


</body>
