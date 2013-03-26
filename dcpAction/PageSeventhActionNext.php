<?php

require_once "dcpAction.php";
require_once "dcpSmarty/dcpProcedure.php";

//
require_once 'dcpDataObjects/Dcp_procedure_verification.php';
//

class PageSeventhActionNext extends dcpAction
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
	echo 'Thank you for your submission';
	$sdesk_num = $data['values']['perm']['sdesk_num'];
	$this->saveDcp($sdesk_num, $data['values'][$pageName]);
	
	//$next =& $page->controller->getPage('page8');
	//$next->handle('jump');
    }


    function saveDcp ($sdesk_num, $values_array)
    {
      $dcpProcedure = new dcpProcedure();
      $dcp = $dcpProcedure->joinDCPTables();
      $dcp->get($sdesk_num);

      $joined_tables = $dcpProcedure->joinOptionalTables($sdesk_num); // we need the table name, among others
      array_unshift($joined_tables, $dcp);

      foreach ($joined_tables as $table)
	{ 
	  $original_table = clone($table); // clone is emulated in php4 for compatibility reasons. 
	  $db =& $table->getDatabaseConnection();
	  $mysql_schema = $db->getAll("SHOW COLUMNS FROM "
				      . $table->tableName());
	  //DB_DataObject::debugLevel(5);
	  foreach($mysql_schema as $field)
	    {
	      $col = $field[0];
	      $answer = $values_array["$col"];
	      if (isset ($answer))
		{
		  if ($field[1] == 'datetime')
		    {
		      $date = $values_array["$col"];
		      $table->$col = DB_DataObject_Cast::date($date[Y],$date[M],$date[d]);
		    }
		  else 
		    {
		      $table->$col = "$answer";
		    }
		}
	    }
	  $result = $table->update($original_table); // only update the difference between new and old
	  //DB_DataObject::debugLevel(0);
	}
    }



}

?>