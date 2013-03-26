<?php

require_once "dcpAction.php";
require_once( "dcpDatabase/dcpDBRecord.php" );

class PageSixthActionNext extends dcpAction
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
	$sdesk_num = $data['values']['perm']['sdesk_num'];

	// Create dcp_procedure_verification Object
	$Procedure_verification = new dcpProcedureVerification($connection,$sdesk_num);

	// Insert all this stuff in Database
	
  	$optional_tables = array('dcp_procedure_verification_eeprom' => 'eeprom Modifications required', 'dcp_procedure_verification_svm' => 'svm utilized', 'dcp_procedure_verification_zfs' => 'zfs employed', 'dcp_procedure_verification_clt' => 'host in CLT', 'dcp_procedure_verification_san' => 'host san attached', 'dcp_procedure_verification_cluster' => 'cluster enabled', 'dcp_procedure_verification_x86' => 'x86 architecture', 'dcp_procedure_verification_offswan' => 'located OffSwan', 'dcp_procedure_verification_vlan' => 'vlan utilized');
      foreach ($optional_tables as $table => $label)
	{
	  $answer = $data['values'][$pageName]["$table"];

	  if ( preg_match ('/^dcp_procedure_verification_offswan/', $table) )
	    {
	      if ( $answer == 'Y' )
		{
		  $rec = new dcpDBRecord($connection, "$table", "$sdesk_num" );
		}
	      else 
		{
		  $rec = new dcpDBRecord($connection, 'dcp_procedure_verification_onswan', "$sdesk_num" );
		}
	    }
	  else 
	    {
	      if ( $answer == 'Y' ) 
		{
		  $rec = new dcpDBRecord($connection, "$table", "$sdesk_num" );
		}
	      else 
		{
		  // need to delete record if no
		  

		}
	    }
	}

      $next =& $page->controller->getPage('page7');
      $next->handle('jump');
    }
}

?>