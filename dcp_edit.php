<?php

require_once 'PEAR.php';
require_once 'dcpDataObjects/All_dcps.php';
require_once 'dcpDataObjects/Dcp_procedure_verification.php';
require_once 'dcpDataObjects/Sun_server.php';
require_once 'dcpDataObjects/Os_version_release.php';
require_once 'dcpDataObjects/Os.php';
require_once 'dcpDataObjects/Os_version.php';
require_once 'dcpDataObjects/Processor_type.php';
require_once 'dcpDataObjects/Os_choices.php';

require_once 'dcpDB_DataObject_FormBuilder/Edit_dcp.php';

require_once "dcpPage.php";

//require_once 'HTML/QuickForm.php';
//require_once 'HTML/QuickForm.php';

session_start();

$config = parse_ini_file('dcpDataObjects/dcp.ini',TRUE);
foreach($config as $class=>$values) {
  $options = &PEAR::getStaticProperty($class,'options');
  $options = $values;
}

// set error handling for PEAR classes
//PEAR::setErrorHandling(PEAR_ERROR_CALLBACK, array('Edit_dcp', 'errHandler'));

//DB_DataObject::debugLevel(1);
$os = new dcpDataObjects_Os;
$os_choices = new dcpDataObjects_Os_choices;
$os_version = new dcpDataObjects_Os_version;
$processor_type = new dcpDataObjects_Processor_type;
$os_version_release = new dcpDataObjects_Os_version_release;
//$os_version_release->joinAdd($os);
//$os_version_release->joinAdd($os_version);
//$os_version_release->joinAdd($processor_type);
$sun_servers = new dcpDataObjects_Sun_server;
//$sun_servers->joinAdd($os_version_release);
$all_dcps = new dcpDataObjects_Dcp_procedure_verification;

$fb =& Edit_dcp::create($all_dcps);

//$fb->elementTypeMap = array('shorttext' => 'text', 'date' => 'myDate');


$fb->fieldsToRender = array('sysid', 'note', 'regtool_prod_status_sdt', 'gcn_num', 'os_load_date', 'netwrk_inferfaces_full_duplex', 'netwrk_interfaces_any_faults', 'ipmp_configured', 'sendmail_verified', 'sendmail_root_alias', 'dumpadm_validated', 'backups_started', 'backups_sdt_num', 'explorer_enabled', 'scic_enabled', 'sunmc_enabled', 'sunswat_enabled', 'helios_entry', 'eis_radiance_case', 'netcool_inventory_sdt', 'root_password_set' ,'pts_applied', 'fss_enabled', 'eds_tools_installed', 'frmware_obp_validation', 'frmware_hba_validation', 'frmware_disks_validation', 'frmware_alom_validation', 'frmware_hypervisor_validation', 'lu_patch_update');


// Insert "$do->get($some_id);" here to edit an 
// existing object instead of making a new one
$all_dcps->get(6312987);


$form =& $fb->getForm();

if ($form->validate())
  {
    $form->process(array(&$fg,'processForm'), false);
    $form->freeze();
  }

$dcpPage =& new dcpPage('PSC DCP Tracker');
$dcpPage->buildPageHeading('http://psc.central.sun.com:9000/dcp/dcp_edit.php');

//$this->printHeader();
//echo '<h1>PSC DCP Tracker</h1>';
echo $form->toHTML();

?>