<?php 
	function getLanguage($textFr, $textEn) {
    if($_COOKIE["lang"] == 'fr')
        return $textFr;

    else if($_COOKIE["lang"] == 'en')
        return $textEn;
}

?>