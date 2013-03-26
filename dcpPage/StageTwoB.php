<?php

class StageTwoB extends dcpPage
{
    function buildForm()
    {
        $this->_formBuilt = true;
	$data     =& $this->controller->container();	

	$this->buildPageHeading();

	$num_rows = $data['values']['perm']['num_rows'];
	$sdesk_num = $data['values']['perm']['sdesk_num'];


	$this->addElement('header', null, "Ticket #$sdesk_num does not exist in Service Desk. Please go back and enter valid ticket #");	

	$prevnext[] =& $this->createElement('submit',   $this->getButtonName('back'), '<< Back');

	$this->addGroup($prevnext, null, '', '&nbsp;', false);

	$this->setDefaultAction('back');
    }
}

?>