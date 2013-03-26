<?php

require_once "HTML/QuickForm/Controller.php";

class dcpController extends HTML_QuickForm_Controller

{

   function reset()
   {
     error_log("calling reset function in dcpController");
     $this->container($reset = true);
     $_SESSION["_" . $_SERVER['PHP_SELF']. '_stack'] = array();
   }


  //$page->controller->container();
  
  // function reset( ) {
  //   $this->container( true );
  //   self::$_session->resetScope( $this->_scope );
  // }


   
}

?>