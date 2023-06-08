<?php session_start();?>

<?php 
include("verifLogin.php");
include("request.php"); 
?>

<?php


// User generates a grid
if(!isset($_COOKIE['CON_grid'])) {
  $newGrid;

  $size;
    if (!isset($_COOKIE['CON_dim']))
      $size = 3;
    else
      $size = $_COOKIE['CON_dim'];

    $diff;
    if (!isset($_COOKIE['CON_diff']))
      $diff = 0;
    else
      $diff = $_COOKIE['CON_diff'];

  exec("cd ../../THE_PROJECT/ && main.exe $size 1 $diff", $newGrid);

  // $newGrid = array_splice(str_split($newGrid[0]), 0, 1);
  // $newGrid = join($newGrid);

  // exec("cd ../../THE_PROJECT/ && main.exe $size 3 $newGrid", $newGrid);

  setcookie("CON_grid", $newGrid[0], time() + 365*24*60*60, '/');

}

// If user saves his grid
else {

  $size;
  if (!isset($_COOKIE['CON_dim']))
    $size = 3;
  else
    $size = $_COOKIE['CON_dim'];

  $name;
  if (!isset($_COOKIE['CON_gridName']))
    $name = 0;
  else
    $name = $_COOKIE['CON_gridName'];

  $grid = $_COOKIE['CON_grid'];
  
  $result;
  exec("cd ../../THE_PROJECT/ && main.exe $size 4 $grid", $result);

  var_dump($result);

  if(isset($result) && isset($grid) && !empty($result)&& isset($_SESSION['email']) && $result[0] == "possible") {

    $seed;
    exec("cd ../../THE_PROJECT/ && main.exe $size 5 $grid", $seed);

    setcookie("CON_grid", $size.$grid, time() + 365*24*60*60, '/');

    request("INSERT INTO `level`(`email`, `id`, `nom`, `seed`, `dim`) VALUES ('?', NULL,'?','?','?')", true, array($_SESSION['email'], $name, $seed, $size));

    setcookie("CON_message", "Grid saved !", time() + 365*24*60*60, '/');
  }

  else {

    setcookie("CON_grid", $size.$grid, time() + 365*24*60*60, '/');

    setcookie("CON_message", "An error occured", time() + 365*24*60*60, '/');

  }
  
}

?>

<!DOCTYPE html>
<html lang="en">

  <head>

		<?php include("head.php"); ?>

		<title>The Crate Stacker - Levels</title>
		<link rel="stylesheet" href="../CSS/level.css">

  </head>

<body>

  <?php include("nav.php"); ?>

  <header>
    <h1>Levels conceptor</h1>
  </header>
  
  <main>

    <div class="conceptor">

      <div class="plateBox">
        <div id="mainPlate"></div>
        <div class="messageBox">No information</div>
        <button onclick="saveGrid()">Save your grid</button>
      </div>

      <div class="tools">
        <div class="toolsBox">
          <div class="title">Generate A Grid</div>
          <div class="difficultyInput">
            <div><input type="radio" id="diff0" name="difficulty" value="0" <?php if(!isset($_COOKIE["CON_diff"]) || $_COOKIE["CON_diff"] == 0) { echo "checked";} ?>><label for="diff0">Very Easy</label></div>
            <div><input type="radio" id="diff1" name="difficulty" value="1" <?php if(isset($_COOKIE["CON_diff"]) && $_COOKIE["CON_diff"] == 1) { echo "checked";} ?>><label for="diff1">Easy</label>     </div>
            <div><input type="radio" id="diff2" name="difficulty" value="2" <?php if(isset($_COOKIE["CON_diff"]) && $_COOKIE["CON_diff"] == 2) { echo "checked";} ?>><label for="diff2">Medium</label>   </div>
            <div><input type="radio" id="diff3" name="difficulty" value="3" <?php if(isset($_COOKIE["CON_diff"]) && $_COOKIE["CON_diff"] == 3) { echo "checked";} ?>><label for="diff3">Hard</label>     </div>
            <div><input type="radio" id="diff4" name="difficulty" value="4" <?php if(isset($_COOKIE["CON_diff"]) && $_COOKIE["CON_diff"] == 4) { echo "checked";} ?>><label for="diff4">Empty</label>     </div>
          </div>

          <div class="title">Choose grid size</div>
          <div class="radiosInput">
            <div><input type="radio" id="size3" name="sizeGrid" value="3" <?php if(!isset($_COOKIE["CON_dim"]) || $_COOKIE["CON_dim"] == 3) { echo "checked";} ?>><label for="size3">3x3</label></div>
            <div><input type="radio" id="size4" name="sizeGrid" value="4" <?php if(isset($_COOKIE["CON_dim"]) && $_COOKIE["CON_dim"] == 4) { echo "checked";} ?>><label for="size4">4x4</label></div>
          </div>

          <button onclick="generateAutoGrid()">Generate</button>
        </div>

        <div class="separator"></div>

        <div class="toolsBox">
          <div class="title">Generate from a seed</div>
          <input type="number" id="seedInput" placeholder=""></input>
          <button>Generate</button>
        </div>
      </div>

      <div id="editTool">
        <div class="number" id="numberEmpty" onclick="changeCrates(this)"></div>
        <div class="number" onclick="changeCrates(this)">1</div>
        <div class="number" onclick="changeCrates(this)">2</div>
        <div class="number" onclick="changeCrates(this)">3</div>
        <div class="number" onclick="changeCrates(this)">4</div>
        <div class="crateInvChoice" title="Show/Hide Crate"></div>
      </div>

    </div>


    <div class="bigTitle">
      <h1>My Levels</h1>
    </div>

    <div class="myLevel">
    
    <?php 
    try{
      $resultat = request("SELECT * FROM level WHERE email = :email", false, array(':email' => $_SESSION['email']));
      echo "<table>
              <tr>
              <th>Name</th>
              <th>Size</th>
              <th>Difficulty</th>
              <th>Seed</th>
              <th>Dimension</th>
            </tr>";
      foreach ($resultat as $row) {
        echo "
        <tr>    
            <td>$row[nom]</td>
            <td>$row[dim]</td>
            <td>$row[difficulty]</td>
            <td>$row[seed]</td>
            <td><a href='home.php?ida=$row[seed]'>Jouer</a></td>
        </tr>";
        }
      echo "</table>";
    }

    catch (Exception $e) {
        die("Erreur : " . $e->getMessage());
    }

?>
      
    </div>

  </main>
	
	<?php include("footer.php"); ?>
	
</body>

<script src="conceptor.js"></script>

</html>
