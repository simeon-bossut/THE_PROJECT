<?php session_start();?>

<?php 
include("verifLogin.php");
include("request.php"); 
?>

<?php
if(isset($_POST["clue"])) {

$grid = str_split($_COOKIE["grid"]);

array_splice($grid, 0, 1);

$grid = join($grid);

exec("../../THE_PROJECT/main $_POST[dim] 2 $grid", $out);

setcookie("gridClue", "120013017", time() + 365*24*60*60, '/' );

header("Location:home.php");

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
        <form>
          <input type="hidden" name="dim" value="4">
          <input type="submit" value="Check if grid is solvable">
        </form>
      </div>

      <div class="tools">
        <div class="toolsBox">
          <div class="title">Generate A Grid</div>
          <div class="difficultyInput">
            <div><input type="radio" id="diff0" name="difficulty" value="0" checked><label for="diff0">Very Easy</label></div>
            <div><input type="radio" id="diff1" name="difficulty" value="1"><label for="diff1">Easy</label>     </div>
            <div><input type="radio" id="diff2" name="difficulty" value="2"><label for="diff2">Medium</label>   </div>
            <div><input type="radio" id="diff3" name="difficulty" value="3"><label for="diff3">Hard</label>     </div>
          </div>
          <button>Generate</button>
        </div>
        
        <div class="separator"></div>

        <div class="toolsBox">
          <div class="title">Choose grid size</div>
          <div class="radiosInput">
            <div><input type="radio" id="size3" name="sizeGrid" value="3"><label for="size3">3x3</label></div>
            <div><input type="radio" id="size4" name="sizeGrid" value="4"><label for="size4">4x4</label></div>
          </div>
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
    echo "<table>";
    echo"
    <tr>
    <th>name</th>
    <th>size</th>
    <th>difficulty</th>
    <th>seed</th>
    <th>dimension</th>
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

}catch (Exception $e) {
    die("Erreur : " . $e->getMessage());
}

?>
      
    </div>

  </main>
	
	<?php include("footer.php"); ?>
	
</body>

<script src="conceptor.js"></script>

</html>
