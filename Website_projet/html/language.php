<?php
function getLanguage($textFr, $textEn) {
  if (isset($_COOKIE["lang"]) && $_COOKIE["lang"] == 'fr')
    return $textFr;
  else {
    return $textEn;
  }
}

?>
