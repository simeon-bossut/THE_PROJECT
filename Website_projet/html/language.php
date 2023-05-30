<?php 
	function getLanguage($textFr, $textEn) {
    if($_COOKIE["lang"] == 'fr')
        return $textFr;

    if($_COOKIE["lang"] == 'en')
        return $textEn;
}

?>