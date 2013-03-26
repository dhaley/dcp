<?php

require_once "dcpPage.php";

class Menu extends dcpPage
{

  function buildForm()
  {
    $this->_formBuilt = true;
    //    $data     =& $this->controller->container();	
    $pageName =  $this->getAttribute('id');
    $this->buildPageHeading();
    $this->addElement('header', 'hdrMenu', 'Main Menu');
    $this->addElement('submit', 'dcp_action', 'new');
    $this->addElement('submit', 'dcp_action', 'view_single_dcp');
    $this->addElement('submit', 'dcp_action', 'view_all_dcps');
    $this->addElement('submit', 'dcp_action', 'edit_dcp');
    $this->addElement('submit',  'dcp_action', 'delete_dcp');
    $this->setDefaultAction('new');
  }
  
} 

?>