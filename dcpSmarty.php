<?php
require_once "dcpPage.php";

class dcpSmarty
{
  var $smarty;
  
  function dcpSmarty ($smarty="")
  {
    $this->smarty = $smarty;
  }

  function getSmarty () 
  {
    return $this->smarty;
  }
  
}

?>