<?php

  exec("testone.exe", $out);
  var_dump($out);


  $firstDim = explode(";", $out[0]);

  $finalArr = array();

  echo "<br><br>";

  foreach($firstDim as $key=>$val) {
    $finalArr[$key] = explode(",", $val);
  }

  var_dump($finalArr);

?>