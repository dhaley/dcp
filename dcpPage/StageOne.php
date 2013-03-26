<?php

// Class representing a form
class StageOne extends dcpPage
{

  function buildForm()
  {
    $this->_formBuilt = true;
    $data     =& $this->controller->container();
    $pageName =  $this->getAttribute('id');
    
    $this->buildPageHeading();
    
    $this->addElement('header', 'null', 'Find DCP');
    
    $this->addElement('text', 'sdesk_num', 'Please enter the Service Desk Ticket # for your DCP:', array('size' => 7));

    $this->addRule('sdesk_num', 'Please enter a new or existing Ace DCP Service Desk Ticket #:', 'required', null, 'client');
    $this->addRule('sdesk_num', 'ERROR: Incorrect data type', 'numeric');
    $this->addRule('sdesk_num', 'SDESK number must be 7 digits:', 'rangelength', array(7,7) );

    //    $prevnext[] =& $this->CreateElement('submit', $this->getButtonName('clear'), 'Clear');
    $prevnext[] =& $this->CreateElement('submit', $this->getButtonName('next'), 'Next >>');
    
    $this->addGroup($prevnext, null, '', '&nbsp;', false);
    
    $data['values'][$pageName]['iradPageAB'] = 'page2';
    $this->setDefaultAction('next');
  }
} 


?>