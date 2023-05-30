<?php
function getLanguage($textFr, $textEn) {
  if (isset($_COOKIE["lang"]) && $_COOKIE["lang"] == 'fr')
    return $textFr;
  else {
    setcookie("lang", 'en', time() +(60*60*24*30*365));
    return $textEn;
  }
}

?>