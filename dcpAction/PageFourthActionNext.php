<?php

require_once "dcpAction.php";
require_once "dcpDatabase/dcpProcedureVerification.php";

class PageFourthActionNext extends dcpAction
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

 	$answer = $data['values'][$pageName]['iradYesNo'];

 	if ($answer == 'Y') 
 	  {
 	    $Sun_Server = $data['values']['perm']['Sun_Server_obj'];
 	    $System_id = $Sun_Server->getSysId();	    
	    $data['values']['perm']['sysid'] = $System_id;
	    $data['values']['perm']['hostname'] = $Sun_Server->getHostname();	    

	    $Sun_Server->insertFromRegtool(); // populate (update/insert) sun_server table

	    $sdesk_num = $data['values']['perm']['sdesk_num'];
	    global $connection; 			  
	    $Procedure_verification = new dcpProcedureVerification($connection,$sdesk_num);
	    $Procedure_verification->linkRegToolHost($System_id);
	    
	    $next =& $page->controller->getPage('page5');
	    $next->handle('jump');
 	  }
 	else 
 	  {
	    echo "here is where fifth page would go with answer $answer!<br>\n";	    
	    //	    $next =& $page->controller->getPage('page5');
	    //	    $next->handle('jump');
 	  }
    }
}

?>