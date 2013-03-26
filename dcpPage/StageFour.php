<?php

class StageFour extends dcpPage
{
    function buildForm()
    {
        $this->_formBuilt = true;
	$data     =& $this->controller->container();	
	$this->buildPageHeading();

	$num_rows = $data['values']['perm']['num_rows'];
	$sdesk_num = $data['values']['perm']['sdesk_num'];
	$row = $data['values']['perm']['regToolRows']; // Regtool row dcpRegtool
	$full_hostname = $data['values']['perm']['full_hostname'];
	$host_name = $data['values']['perm']['hostname'];
	$domain_name = $data['values']['perm']['domain_name'];

	$status = $row[1];
	$serial_number = $row[4];
	$location = $row[5];
	$hostid = $row[6];
	$eds_service_level = $row[7];
	$model = $row[8];
	$operation_env = $row[9];
	$network_access = $row[10];
	$in_production = $row[11];
	$division = $row[12];


	// Need to create Sun Server object here to get real_hostname
	global $connection; 			  
	$Sun_Server = new dcpSun_ServerFromRegtool($connection);
	$Sun_Server->populateRegTool($row);
	$data['values']['perm']['Sun_Server_obj'] = $Sun_Server;
	$real_hostname = $Sun_Server->getHostname();


	$this->addElement('html', "<b>Host Details for $real_hostname</b><br>");
	$this->addElement('html', "<b>Serial Number</b>: $serial_number, <b>Hostid</b>: $hostid, <b>Location</b>: $location<br>");
	$this->addElement('html', "<b>Model</b>: $model, <b>Environment</b>: $operation_env, <b>Eds Support</b>: $eds_service_level<br>");
	$this->addElement('html', "<b>In Prodcution</b>: $in_production, <b>Division</b>: $division, <b>Network</b>: $network_access");
	$this->addElement('header', null, "Is this the correct host?");	
        $radio[] = &$this->createElement('radio', null, null, 'Yes', 'Y');
        $radio[] = &$this->createElement('radio', null, null, 'No', 'N');
        $this->addGroup($radio, 'iradYesNo', 'Are you absolutely sure?');
        $this->addRule('iradYesNo', 'Check Yes or No', 'required');
	
	$prevnext[] =& $this->createElement('submit', $this->getButtonName('back'), '<< Back', array("onClick" => "this.form.onsubmit = null; return true;") );
	$prevnext[] =& $this->createElement('submit',   $this->getButtonName('next'), 'Next >>');
	$this->addGroup($prevnext, null, '', '&nbsp;', false);
	
        $this->setDefaultAction('next');
     }
}

?>