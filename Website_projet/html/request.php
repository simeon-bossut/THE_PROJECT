<?php

  function request($phpRequest, $isUnique, $params = NULL) {
    try {

      if(!isset($phpRequest) || !isset($isUnique))
        throw("Not enough parameters");

      require("connexion.php");

      $req = $conn->prepare($phpRequest); //Préparer la requete

      if(isset($params)){
        $req->execute($params); //Executer la requete
      }

      else {
        $req->execute();
      }
      
      if($isUnique)
        $resultat = $req->fetch(); //récupération du résultat 
      
      else
        $resultat = $req->fetchAll(PDO::FETCH_ASSOC); //récupération du résultat

      $conn = NULL;

      return $resultat;
    }

    catch (Exception $e) {
      die("Erreur : " . $e->getMessage());
    }
  }

?>