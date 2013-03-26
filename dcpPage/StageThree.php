<?php

class StageThree extends dcpPage
{
    function buildForm()
    {
        $this->_formBuilt = true;
	$data     =& $this->controller->container();

	$num_rows = $data['values']['perm']['num_rows'];
	$sdesk_num = $data['values']['perm']['sdesk_num'];
	$dcp_action = $data['defaults']['dcp_action'];


	
	$this->buildPageHeading();
	$this->addElement('header', null, "Assign Regtool Host to SD Ticket #$sdesk_num");
        $this->addElement('text', 'full_hostname', 'Enter hostname (use Regtool format: host.domain):', array('size' => 50, 'maxlength' => 255));
	$this->applyFilter('full_hostname', 'trim');
	$this->addRule('full_hostname', 'Please enter a hostname', 'required', null, 'client');

	if ($dcp_action == 'assign_regtool') 
	  {
	    $prevnext[] =& $this->createElement('hidden', 'dcp_action', "$dcp_action");	    
	  }
	$prevnext[] =& $this->createElement('submit', $this->getButtonName('back'), '<< Back', array("onClick" => "this.form.onsubmit = null; return true;") );
	$prevnext[] =& $this->createElement('submit',   $this->getButtonName('next'), 'Next >>');
        $this->addGroup($prevnext, null, '', '&nbsp;', false);
        $this->setDefaultAction('next');
    }
}

?>