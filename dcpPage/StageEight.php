<?php

class StageEight extends dcpPage
{
    function buildForm()
    {
      $this->_formBuilt = true;


      //	$sdesk_num = $data['values']['perm']['sdesk_num'];
      //	$sysid = $data['values']['perm']['sysid'];
      //	echo "ticket num is $sdesk_num and sysid is $sysid for new Action class<br>";

      // Add some elements to the form
      $this->buildPageHeading();      
      $this->addElement('header', null, 'QuickForm tutorial example');
      $this->addElement('text', 'name', 'Enter your name:', array('size' => 50, 'maxlength' => 255));
      // Note how we set the name of the submit button
      $this->addElement('submit', $this->getButtonName('submit'), 'Send');

      // Define filters and validation rules
      $this->applyFilter('name', 'trim');
      $this->addRule('name', 'Please enter your name', 'required', null, 'client');

      $this->setDefaultAction('submit');
	
     }
}

?>