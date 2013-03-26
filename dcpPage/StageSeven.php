<?php

require_once "HTML/QuickForm/Page.php";
require_once "dcpSmarty/dcpProcedure.php";
require_once "dcpPage.php";

// Class representing a form
class StageSeven extends dcpPage
{
  var $sdesk_num;
  var $smarty;
  
    function buildForm()
    {
        $this->_formBuilt = true;
	$data     =& $this->controller->container();
	//$hostname = $data['values']['perm']['hostname'];
	$sdesk_num = $data['values']['perm']['sdesk_num'];
	$this->sdesk_num = $sdesk_num;
	
	// Turn Smarty template on or off
	$this->_smarty_template = TRUE;
	//$this->_smarty_template = FALSE;

	// UPDATE dcp_procedure_verification SET os_load_date = NOW() where sdesk_num = 6231113
	
	$this->smarty = parent::createSmarty();

	$dcpProcedure_Smarty = new dcpProcedure($this->smarty);
	$dcpProcedure_Smarty->loadSmarty($this->sdesk_num);
	$this->dcp_smarty = $dcpProcedure_Smarty->getSmarty(); // fully loaded Smarty	
	$dcp_labels = $this->dcpVal('dcp_labels');
	
	$this->buildPageHeading();
	$this->addElement('header', 'hdrTesting', "Please update the status of DCP #$sdesk_num");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	$this->addElement('text', 'regtool_prod_status_sdt', 'Regtool Prod Status SDT #:',  array('size' => 7, 'maxlength' => 7)); 
	$this->addRule('regtool_prod_status_sdt', 'ERROR: Incorrect data type', 'numeric');
	$this->addRule('regtool_prod_status_sdt', 'SDESK number must be 7 digits:', 'rangelength', array(7,7) );
	// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	$this->addElement('text', 'gcn_num', $dcp_labels['gcn_num'], array('size' => 6, 'maxlength' => 6));		
	$this->addRule('gcn_num', 'ERROR: Incorrect data type', 'numeric');
	$this->addRule('gcn_num', 'SDESK number must be 6 digits:', 'rangelength', array(6,6) );
	// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	$this->addElement('date',       'os_load_date', 'OS Load Date:', array('format' => 'd-M-Y', 'minYear' => 2008, 'maxYear' => date('Y')));
	//	$this->addElement('textarea', 'note', $dcp_labels['note'], array('size' => 144, 'maxlength' => 144));
	$this->addElement('textarea', 'note', $dcp_labels['note'], array('cols'=>80, 'rows'=>4, 'size' => 144, 'maxlength' => 144)); // size 144
	$this->addRule('note', 'Note can only be 144 characters long', 'rangelength', array(144,144) );
	
	$this->addElement('text', 'backups_sdt_num', $dcp_labels['backups_sdt_num'], array('size' => 10, 'maxlength' => 10));
	$this->addRule('backups_std_num', 'ERROR: Incorrect data type', 'numeric');
	$this->addRule('backups_std_num', 'Backups SDESK number must be 7 digits:', 'rangelength', array(7,7) );

	$this->addElement('text', 'eis_radiance_case', $dcp_labels['eis_radiance_case'], array('size' => 10, 'maxlength' => 10));
	$this->addRule('eis_radiance_case', 'ERROR: Incorrect data type', 'numeric');
	$this->addRule('eis_radiance_case', 'EIS radiance case number must be 7 digits:', 'rangelength', array(7,7) );
	
	$this->addElement('text', 'netcool_inventory_sdt', $dcp_labels['netcool_inventory_sdt'], array('size' => 10, 'maxlength' => 10));
	$this->addRule('netcool_inventory_sdt', 'ERROR: Incorrect data type', 'numeric');
	$this->addRule('netcool_inventory_sdt', 'Netcool inventory SDESK number must be 7 digits:', 'rangelength', array(7,7) );

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	$choice_tables = array('netwrk_interfaces_any_faults' => 'Any network interface faults', 'netwrk_inferfaces_full_duplex' => 'Are network interfaces full duplex', 'ipmp_configured' => 'IPMP configured', 'sendmail_verified' => 'Sendmail verified', 'sendmail_root_alias' => 'Root mail alias created', 'dumpadm_validated' => 'Dumpadm validated', 'backups_started' => 'Backups started', 'explorer_enabled' => 'Explorer enabled', 'scic_enabled' => 'SCIC enabled', 'sunmc_enabled' => 'SunMC enabled', 'sunswat_enabled' => 'Sunswat enabled', 'helios_entry' => 'Helios entry created', 'root_password_set' => 'root password set', 'eds_tools_installed' => 'EDS tools installed', 'lu_patch_update' => 'Live Upgrade patches applied', 'fss_enabled' => 'fss enabled', 'pts_applied' => 'pts applied',
			       'frmware_obp_validation' => 'Firmware OBP validation', 'frmware_hba_validation' => 'Firmware HBA validation', 'frmware_alom_validation' => 'Firmware Alom validation', 'frmware_hypervisor_validation' => 'Firmware Hypervisor validation', 'lu_patch_update' => 'Lu patch update', 'frmware_disks_validation' => 'Firmware disks validation'
			       );
	$dcp_array = $this->dcpVal('view_dcp.0');
	//	foreach ($dcp_array as $column => $value)
	foreach ($choice_tables as $column => $value)
	{
	  ${$column}[] = &$this->createElement('radio', null, null, 'Yes', 'yes');
	  ${$column}[] = &$this->createElement('radio', null, null, 'No', 'no');
	  $this->addGroup($$column, $column, $dcp_labels[$column]);
	  $this->addRule("$$column", 'Check Yes or No', 'required');
	    $this->setDefaults(array(
				     $column => $dcp_array[$column],
				     ));
	}


	// THIS OPTIONAL TABLES STUFF SHOULD BE HANDLED BY SMARTY
	$sometables = array('svm', 'offswan', 'onswan', 'vlan', 'eeprom', 'san', 'zfs', 'x86', 'cluster', 'clt');
	foreach ($sometables as $o_table)
	  {
	    if ( $array = $this->dcpVal("view_$o_table.0") )
	      {
		$col_array = "view_" . $o_table . "_labels";
		$col_labels = $this->dcpVal($col_array);
		foreach ($array as $column => $value)
		  {
		    $col_label = $col_labels[0]["$column"];
		    if ( ($column == 'cam_sheet_sent_date' ) || ($column == 'san_switch_port_requested_date' ) || ($column == 'san_connected_date' ) )
		      {
			$this->addElement('date', "$column", "$col_label", array('format' => 'd-M-Y', 'minYear' => 2008, 'maxYear' => date('Y')));			
		      }
		    elseif ($column == 'san_cr_num')
		      $this->addElement('text', $column, $col_label, array('size' => 10, 'maxlength' => 10));
		    else 
		      {
			${$column}[] = &$this->createElement('radio', null, null, 'Yes', 'yes');
			${$column}[] = &$this->createElement('radio', null, null, 'No', 'no');
			$this->addGroup($$column, "$column", $col_label);	      
			$this->addRule("$$column", 'Check Yes or No', 'required');
		      }
		    $this->setDefaults(array(
					     $column => $value,
					     ));
		  }
	      }
	  }

	$prevnext[] =& $this->createElement('submit', $this->getButtonName('back'), '<< Back', array("onClick" => "this.form.onsubmit = null; return true;") );
	$prevnext[] =& $this->createElement('submit',   $this->getButtonName('next'), 'Next >>');
	$this->addGroup($prevnext, 'prevnext', '', '&nbsp;', false);
	$this->setDefaultAction('next');
    }

    function createSmarty ()
    {
      // Smarty
      return $this->smarty;
}

}


?>