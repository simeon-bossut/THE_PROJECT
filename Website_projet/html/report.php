<?php session_start();

include 'language.php';

require("connexion.php");

require("request.php");

$req1;
$req2;

try{
    if(isset($_SESSION) && isset($_SESSION['admin']==1)) {
        $req1 = request("SELECT * FROM bug_list");
        $req2 = request("SELECT * FROM idea_list");
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

  <title>The Crate Stacker - Report Page</title>

  <link rel="stylesheet" href="../CSS/home.css">

</head>

<body>
    <?php include("nav.php"); ?>

    <header>
        <h1>Report Page</h1>
    </header>

    <main>
        <div class="bugBox">
        
        </div>

        <div class="ideaBox">

        </div>
    </main>

    <?php if (isset($_SESSION['isOnWebsite']) && $_SESSION['isOnWebsite']) {
    include("footer.php");
  } ?>
</body>

</html>
