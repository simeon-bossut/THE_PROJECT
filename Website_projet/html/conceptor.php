<!DOCTYPE html>
<html lang="en">

  <head>

		<?php include("head.php"); ?>

		<title>The Crate Stacker - Conceptor</title>

		<link rel="stylesheet" href="../CSS/conceptor.css">

  </head>

<body>

  <?php include("nav.php"); ?>

  <header>
    <h1>Game Conceptor</h1>
  </header>
  
  <main>
    <div class="gameTemplate">
      <div id="mainPlate"></div>
    </div>


    <div id="editTool">
      <div class="number">1</div>
      <div class="number">2</div>
      <div class="number">3</div>
      <div class="number">4</div>
      <div class="crateInvChoice" title="Show/Hide Crate"></div>
    </div>
  </main>
	
	<?php include("footer.php"); ?>
	
</body>

<script src="conceptor.js"></script>

</html>
