<?php

class StageSix extends dcpPage
{
    function buildForm()
    {
      $this->_formBuilt = true;
      $data     =& $this->controller->container();

      $hostname = $data['values']['perm']['hostname'];
      global $connection;
      $sdesk_num = $data['values']['perm']['sdesk_num'];
      $sysid = $data['values']['perm']['sysid'];

      $this->buildPageHeading();
      
      $this->addElement('header', null, "DCP Procedure status Architecture Options for ticket #$sdesk_num ($hostname)");
      $optional_tables = array('dcp_procedure_verification_eeprom' => 'eeprom Modifications required', 'dcp_procedure_verification_svm' => 'svm utilized', 'dcp_procedure_verification_zfs' => 'zfs employed', 'dcp_procedure_verification_clt' => 'host in CLT', 'dcp_procedure_verification_san' => 'host san attached', 'dcp_procedure_verification_cluster' => 'cluster enabled', 'dcp_procedure_verification_x86' => 'x86 architecture', 'dcp_procedure_verification_offswan' => 'located OffSwan', 'dcp_procedure_verification_onswan' => 'located OnSwan', 'dcp_procedure_verification_vlan' => 'vlan utilized');

      foreach ($optional_tables as $table => $label)
	{
	  if (! preg_match ('/^dcp_procedure_verification_onswan/', $table) )
	    {
	      ${$table}[] = &$this->createElement('radio', null, null, 'Yes', 'Y');
	      ${$table}[] = &$this->createElement('radio', null, null, 'No', 'N');
	      $this->addGroup($$table, "$table", "$label?");
	      $this->addRule("$table", 'Check Yes or No', 'required');
	      $this->setDefaults( array(
					"$table" => 'N'
					));	 
	    }
	}
      $prevnext[] =& $this->createElement('submit', $this->getButtonName('back'), '<< Back', array("onClick" => "this.form.onsubmit = null; return true;") );
      $prevnext[] =& $this->createElement('submit',   $this->getButtonName('next'), 'Next >>');
      $this->addGroup($prevnext, null, '', '&nbsp;', false);
      $this->setDefaultAction('next');
     }
}

?>