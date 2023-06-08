<?php session_start(); 
require("connexion.php");?>
<?php include("verifLogin.php"); ?>

<?php require("request.php"); ?>

<?php

try{
    if(isset($_SESSION['authentifie'])) {
        $admin = request("SELECT * FROM acc WHERE email = ?", true, array($_SESSION['email']));

        if($admin['admin'] != 1)
            header('Location:home.php');
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

  <link rel="stylesheet" href="../CSS/report.css">

</head>

<body>
    <?php include("nav.php"); ?>

    <header>
        <h1>Report Page</h1>
    </header>

    <main>
        <div class="container">
            <div class="bugBox">
                <?php

                    if(isset($_POST["delete"])) {
                        request("DELETE FROM report WHERE id = ?",true,array($_POST['id']));
                    }


                    if($admin['admin'] == 1) {
                        $res = request("SELECT * FROM report WHERE type='bug'", false);
                        /*var_dump($res);*/

                        echo "<table>
                                <tr>
                                    <th>id</th>
                                    <th>date</th>
                                    <th>text</th>
                                    <th>delete</th>
                                </tr>";

                        foreach($res as $row) {
                            echo "<tr>";
                            echo "<td>$row[id]</td>";
                            echo "<td>$row[date]</td>";
                            echo "<td>$row[text]</td>";
                            echo '<td><form action="" method="post"><input type="hidden" name="id" value="' . $row["id"] . '"><input type="submit" name="delete" value="Delete"></form> </td>';
                            echo "</tr>";	
                        }	
                        echo "</table>";
                    }            
                ?>
            </div>

            <div class="ideaBox">
                <?php

                    if(isset($_POST["delete"])) {
                        request("DELETE FROM report WHERE id = ?",true,array($_POST['id']));
                    }


                    if($admin['admin'] == 1) {
                        $res = request("SELECT * FROM report WHERE type='idea'", false);
                        /*var_dump($res);*/

                        echo "<table>
                                <tr>
                                    <th>id</th>
                                    <th>date</th>
                                    <th>text</th>
                                    <th>delete</th>
                                </tr>";

                        foreach($res as $row) {
                            echo "<tr>";
                            echo "<td>$row[id]</td>";
                            echo "<td>$row[date]</td>";
                            echo "<td>$row[text]</td>";
                            echo '<td><form action="" method="post"><input type="hidden" name="id" value="' . $row["id"] . '"><input type="submit" name="delete" value="Delete"></form> </td>';
                            echo "</tr>";	
                        }	
                        echo "</table>";
                    }            
                ?>
            </div>
        </div>
    </main>

    <?php if (isset($_SESSION['isOnWebsite']) && $_SESSION['isOnWebsite']) {
    include("footer.php");
  } ?>
</body>

</html>
