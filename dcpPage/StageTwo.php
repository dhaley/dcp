<?php

class StageTwo extends dcpPage
{
    function buildForm()
    {
        $this->_formBuilt = true;
	$data     =& $this->controller->container();	
	$this->buildPageHeading();

	$num_rows = $data['values']['perm']['num_rows'];
	$sdesk_num = $data['values']['perm']['sdesk_num'];
	$row = $data['values']['perm']['sdesk_row'];

	$login = $row[0];
	$short_desc = $row[9];
	$submit_time = $row[1];
	$submitter = $row[4];
	$upper_submitter = ucwords($submitter);	
	$priority = $row[6];
	$status = $row[8];
	$usr_dept = $row[5];

	putenv("TZ=GMT");
	$human_submit_time = date('r', $submit_time); //Output format example: 'r' = RFC 2822 date

	
	$this->addElement('html', "<b>Ticket Details for Sdesk Ticket #$sdesk_num</b><br>");
	$this->addElement('html', "<b>Submit Time (GMT)</b>: $human_submit_time<br>");
	$this->addElement('html', "<b>Ticket Description</b>: $short_desc<br>");
	$this->addElement('html', "<b>Submitter</b>: $upper_submitter, <b>Priority</b>: $priority, <b>Status</b>: $status");
	
	$this->addElement('header', null, "Is this the correct Service Desk Ticket?");	
	$prevnext[] =& $this->createElement('submit',   $this->getButtonName('back'), '<< No');
	$prevnext[] =& $this->createElement('submit',   $this->getButtonName('next'), 'Yes >>');
	$this->addGroup($prevnext, null, '', '&nbsp;', false);

	$data['values'][$pageName]['iradPageAB'] = 'page3';
	$this->setDefaultAction('next');
    }
}

?>