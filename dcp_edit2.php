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
// Insert "$do->get($some_id);" here to edit an 
// existing object instead of making a new one
$all_dcps->get(6312987);


$form =& $fb->getForm();

if ($form->validate())
  {
    $form->process(array(&$fg,'processForm'), false);
    $form->freeze();
  }
$form->display();
//echo $form->toHTML();

?>