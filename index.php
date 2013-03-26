<?php

require_once "db.inc";
require_once "DB.php";
require_once "dcpDataGrid.php";
require_once "dcpWizard/dcpNewWizard.php";
require_once "dcpWizard/dcpRegtoolWizard.php";
require_once "dcpDataGrid/All_dcps.php";
require_once 'dcpDataGrid/All_dcps_procedure.php';
require_once 'dcpDataGrid/All_dcps_business.php';
require_once "dcpPage/dcpView.php";
require_once "dcpActionDisplay.php";
require_once "dcpSmarty/dcpProcedure.php";

// Connect to server
$connection = DB::connect($dsn);
if (DB::isError($connection))
  die($connection->getMessage());

$config = parse_ini_file('dcpDataObjects/dcp.ini',TRUE);
foreach($config as $class=>$values) {
  $options = &PEAR::getStaticProperty($class,'options');
  $options = $values;
}

session_start();
ob_start(); // hack to not screw up header information

$php_script = $_SERVER['SCRIPT_NAME'];


if ( $_GET['dcp_action'] ) 
  {
    $dcp_action = $_GET['dcp_action'];
  }
elseif ( isset($_POST['dcp_action']) )
{
  $dcp_action = $_POST['dcp_action'];
}

error_log("dcp_action is $dcp_action BEFORE");
if (! isset($dcp_action) )
  {
    $dcp_action = 'new';
  }
error_log("dcp_action is $dcp_action AFTER");



if ( $dcp_action == 'new' ) {
  $newWizard = new dcpNewWizard();
  $newWizard->run();
   }
elseif ( $dcp_action == 'edit_dcp' ) {
  if ( $_GET['sdesk_num'] ) 
    {
      $sdesk_num = $_GET['sdesk_num'];
    }
  elseif ( isset($_POST['sdesk_num']) )
    {
      $sdesk_num = $_POST['sdesk_num'];
    }

  $page = new dcpPage('PSC DCP Tracker');
  $page->buildPageHeading();
  $page->buildEditForm($sdesk_num); // creates Smarty at this stage
  
  $prevnext[] =& $page->createElement('hidden', 'dcp_action',  'edit_dcp');
  $prevnext[] =& $page->createElement('hidden', 'sdesk_num',  "$sdesk_num");
  $prevnext[] =& $page->createElement('submit', 'save_button',  'Submit');
  $page->addGroup($prevnext, 'prevnext', '', '&nbsp;', false);
  $page->setDefaultAction('submit');
  $dcp_smarty = $page->createSmarty();
  $dcpProcedure_Smarty = new dcpProcedure($dcp_smarty);
  $dcpProcedure_Smarty->loadSmarty($sdesk_num);
  $dcp_smarty = $dcpProcedure_Smarty->getSmarty(); // fully loaded Smarty
  $action_display = new dcpActionDisplay('edit_dcp2.tpl');
  $action_display->setUpPage($page);
  $renderer = $action_display->renderSmarty($dcp_smarty);
  // Try to validate a form
  if ($page->validate()) {
    $page->freeze();
    echo 'Thank you for your submission';
    $action = new PageSeventhActionNext();
    $values_array = $page->getSubmitValues();
    $action->saveDcp($sdesk_num, $values_array);
  }
  else {
    $page->accept($renderer);
    $dcp_smarty->assign('form_data', $renderer->toArray());
    $contents = $dcp_smarty->fetch($action_display->tplFile);
    $smarty = $page->createSmarty();
    $smarty->assign('contents',$contents);
    $smarty->display($frame_template==''?"frame.tpl":$this->_frame_template);
  }
}
elseif ( $dcp_action == 'edit_regtool' ) {
  if ( $_GET['sdesk_num'] ) 
    {
      $sdesk_num = $_GET['sdesk_num'];
    }
  elseif ( isset($_POST['sdesk_num']) )
    {
      $sdesk_num = $_POST['sdesk_num'];
    }

  $page = new dcpPage('PSC DCP Tracker');
  $page->buildPageHeading();
  $page->buildRegToolEditForm($sdesk_num); // creates Smarty at this stage
  
  $prevnext[] =& $page->createElement('hidden', 'dcp_action',  'edit_regtool');
  $prevnext[] =& $page->createElement('hidden', 'sdesk_num',  "$sdesk_num");
  $prevnext[] =& $page->createElement('submit', 'save_button',  'Submit');

  $page->addGroup($prevnext, 'prevnext', '', '&nbsp;', false);
  $page->setDefaultAction('submit');
  $dcp_smarty = $page->createSmarty();
  $dcpProcedure_Smarty = new dcpProcedure($dcp_smarty);
  $dcpProcedure_Smarty->loadSmarty($sdesk_num);
  $dcp_smarty = $dcpProcedure_Smarty->getSmarty(); // fully loaded Smarty
  $action_display = new dcpActionDisplay('edit_regtool.tpl');
  $action_display->setUpPage($page);
  $renderer = $action_display->renderSmarty($dcp_smarty);
  // Try to validate a form
  if ($page->validate()) {
    $page->freeze();
    echo 'Thank you for your submission';
    //    $action = new PageSeventhActionNext();
    $action = new DcpAction();    
    $values_array = $page->getSubmitValues();
    $action->saveDcpRegtool($sdesk_num, $values_array);
  }
  else {
    $page->accept($renderer);
    $dcp_smarty->assign('form_data', $renderer->toArray());
    $contents = $dcp_smarty->fetch($action_display->tplFile);
    $smarty = $page->createSmarty();
    $smarty->assign('contents',$contents);
    $smarty->display($frame_template==''?"frame.tpl":$this->_frame_template);
  }
}
elseif ($dcp_action == 'assign_regtool') {
    if ( $_GET['sdesk_num'] ) 
    {
      $sdesk_num = $_GET['sdesk_num'];
    }
  elseif ( isset($_POST['sdesk_num']) )
    {
      $sdesk_num = $_POST['sdesk_num'];
    }
  $newWizard = new dcpRegtoolWizard();
  $newWizard->run($sdesk_num, $dcp_action);
}
elseif ($dcp_action == 'view_all_dcps') {
  $page = new All_dcps;
  $page->buildPage();
}
elseif ($dcp_action == 'view_all_dcps_procedure') {
  $page = new All_dcps_procedure;
  $page->buildPage();
}
elseif ($dcp_action == 'view_all_dcps_business') {
  $page = new All_dcps_business;
  $page->buildPage();
}
elseif ($dcp_action == 'view_dcp')
{
  // create tabbed page
  $sdesk_num = $_GET['sdesk_num'];
  $dcpView = new dcpView();

  $dcpView->smartyIze($sdesk_num);
  $dcpView->printHeader('new');
  $dcpView->viewDisplay();
}
  
?>