<?php

require_once "dcpAction.php";

class PageFifthActionNext extends dcpAction
{
    function perform(&$page, $actionName)
    {
      // save the form values and validation status to the session
        $page->isFormBuilt() or $page->buildForm();
        $pageName =  $page->getAttribute('id');

        $data     =& $page->controller->container();
	
        $data['values'][$pageName] = $page->exportValues();

        if (PEAR::isError($valid = $page->validate())) {
            return $valid;
        }
        $data['valid'][$pageName] = $valid;

        // Modal form and page is invalid: don't go further
        if ($page->controller->isModal() && !$data['valid'][$pageName]) {
            return $page->handle('display');
        }
	global $connection;
	$sysid = $data['values']['perm']['sysid'];
	$Sun_Server = new dcpSun_Server($connection,$sysid);
	$Sun_Server->setFrmware_obp_id($data['values'][$pageName]['frmware_obp']);
	$Sun_Server->setFrmware_alom_id($data['values'][$pageName]['frmware_alom']);
	$Sun_Server->setFrmware_hypervisor_id($data['values'][$pageName]['frmware_hypervisor']);
	$Sun_Server->setOs_instance_id($data['values'][$pageName]['os_version_release']);
	if (! $data['values'][$pageName]['frmware_disks'] == '0' ) 
	  {
	    $Sun_Server->setFrmware_disks_id ($data['values'][$pageName]['frmware_disks']);
	  }
	if (! $data['values'][$pageName]['frmware_hba'] == '0' ) 
	  {
	    $Sun_Server->setFrmware_hba_id($data['values'][$pageName]['frmware_hba']);	    

	  }
	$next =& $page->controller->getPage('page6');
	$next->handle('jump');
    }
}

?>