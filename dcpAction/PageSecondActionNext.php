<?php

require_once "dcpAction.php";

class PageSecondActionNext extends dcpAction
{
    function perform(&$page, $actionName)
    {
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

	$num_rows = $data['values']['perm']['num_rows'];
	$sdesk_num = $data['values']['perm']['sdesk_num'];
	$row = $data['values']['perm']['sdesk_row'];
	
	// Let's enter $row in the database
	global $connection; 			  
	$Procedure_verification = new dcpProcedureVerificationFromServiceDesk($connection,$sdesk_num);
	$Procedure_verification->populateServiceDesk($row);
	$Procedure_verification->insertFromServiceDesk(); // populate (update/insert) dcp_procedure_verification table

        // More pages?
        $next =& $page->controller->getPage('page3');
        $next->handle('jump');
    }
}

?>