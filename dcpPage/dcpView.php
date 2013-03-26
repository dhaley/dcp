<?php

require_once "dcpSmarty/dcpProcedure.php";
require_once "dcpPage.php";

class dcpView
{
  var $sdesk_num;
  var $dcpPage;
  var $smarty;
  
  function dcpView ()
  {
    $this->dcpPage = new dcpPage('PSC DCP Tracker');
  }
  

  function printHeader ($dcp_action) 
  {
    $this->dcpPage->buildPageHeading("$dcp_action");     
  }

  
  function smartyIze ($sdesk_num) {
    $this->sdesk_num = $sdesk_num;
    $this->smarty = $this->dcpPage->createSmarty(); // get brand new Smarty
    $dcpProcedure_Smarty = new dcpProcedure($this->smarty);
    $dcpProcedure_Smarty->loadSmarty($this->sdesk_num);
  }
  
    
    function viewDisplay () 
    {
      echo "<div style='width:600px;'>\n";
      $this->dcpPage->tab( "DCP Details", $this->smarty, 'view.tpl' );
      $this->dcpPage->tab( "Hardware Details", $this->smarty, 'regtool.tpl' );
      $this->dcpPage->tabs_end($this->sdesk_num);
      echo "</div>\n";
    }
}
  
?>