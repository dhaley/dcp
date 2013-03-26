<?php

require_once 'HTML/QuickForm/Action/Next.php';
require_once "dcpDatabase/dcpSun_Server.php";
require_once "dcpDatabase/dcpRegtool.php";
require_once "dcpDatabase/dcpServiceDesk.php";
require_once "dcpDatabase/dcpSun_ServerFromRegtool.php";
require_once "dcpDatabase/dcpProcedureVerificationFromServiceDesk.php";

class dcpAction extends HTML_QuickForm_Action_Next
{
  var $page;
  var $pageName;
  
  function FormVerify (&$page, $actionName) 
  {
    // save the form values and validation status to the session
    $page->isFormBuilt() or $page->buildForm();
    $pageName =  $page->getAttribute('id');

	
    // Get the container from the page's controller
    $data     =& $page->controller->container();
    error_log("$data is data");
    //$data     =& $page->controller->container();    

    // $nextName = $data['values'][$pageName]['iradPageAB'];
    // $data['values'][$pageName] = $page->exportValues();

    // if (PEAR::isError($valid = $page->validate())) {
    //   return $valid;
    // }
    // $data['valid'][$pageName] = $valid;

    // // Modal form and page is invalid: don't go further
    // if ($page->controller->isModal() && !$data['valid'][$pageName]) {
    //   return $page->handle('display');
    // }


  }
  
  function CheckUSPhoneNum($element_name, $element_value)
  { 
	$PhoneNumber = ereg_replace("[^0-9]", "", $element_value); // Strip out non-numerics
	if(ereg("^([2-9][0-9]{2})([2-9][0-9]{2})([0-9]{4})$", $PhoneNumber, $NumberParts)){
		return "(" . $NumberParts[1] . ") " . $NumberParts[2] . "-" . $NumberParts[3];
	} else {
		return false;
	}
}
 
  /**
   * Looks up a domain and makes sure it's valid; only works on *nix
   *
   * @param   string  $type	Type of banning to check
   * @param   string  $data	The cooresponding data to check
   * @return  bool
   */
  function FormDomainLookup($element, $value, $arg)
  { 
    $value = str_replace('http://','',$value);
	exec("host -t ns $value",$hasil); 
    if (ereg("host $value not found.",strtolower(trim($hasil[0])))) { 
        return false; 
    } else { 
        return true; 
    }
}
 
  /**
   * Makes sure an IP address is valid
   *
   * @param   string  $element_name	name of form field to check
   * @param   string  $element_value	IP Address to check
   * @return  bool
   */
  function CheckIP ($element_name,$element_value) {
    
	$ip = $element_value;
	if (($longip = ip2long($ip)) !== false)
	{
		if ($ip == long2ip($longip))
		{
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	} 
}
 
  /**
   * Makes sure a "date" isn't set to a past date.
   *
   * @param   string  $element_name	name of form field to check
   * @param   string  $element_value	Date to Check
   * @return  bool
   */
  function StopPastDate($element_name, $element_value)
  {
    global $vars, $now;
    
    //check that it's a valid date first
    $temp = explode('-', $element_value);
    if(!checkdate($temp['1'],$temp['2'],$temp['0'])){
      return false;
    }
    
    //now make sure the date isn't in the past.
    if($element_value < $now){
      return false;
    } else {
      return true;
    }
    
  }
  
  /**
   * Makes sure a "date" is a valid MYSQL format.
   *
   * @param   string  $element_name	name of form field to check
   * @param   string  $element_value	Date to Check
   * @return  bool
   */
  function ValidateMysqlDate($element_name, $element_value)
  {
    global $vars, $now;
    
    //check that it's a valid date first
    $temp = explode('-', $element_value);
    if(!checkdate($temp['1'],$temp['2'],$temp['0'])){
      return false;
    }
    return true;
  }
  
  /**
   * Makes sure an integer is positive
   *
   * @param   string  $element_name	name of form field to check
   * @param   string  $element_value	Int to Check
   * @return  bool
   */
  function IsIntPositive($element_name, $element_value)
  {
    
    if (!is_numeric($element_value))
      {
	$element_value = (int)$element_value;
      }
    
    if($element_value < 1)
      {
	return FALSE;
      }
    //exit;
    
    return TRUE;
  }
  
  /**
   * Makes sure an integer isn't a decimal
   *
   * @param   string  $element_name	name of form field to check
   * @param   string  $element_value	Int to Check
   * @return  bool
   */
  function IsIntDecimal($element_name, $element_value)
  {
    if (!is_numeric($element_value))
      {
	$element_value = (int)$element_value;
      }
    
    if(strpos($element_value,'.') === FALSE){
      return TRUE;
    }
    //exit;
    
    return FALSE;
  }
  
  /**
   * Makes sure a URL is valid
   *
   * @param   string  $element_name	name of form field to check
   * @param   string  $element_value	URL to Check
   * @return  bool
   */
  function IsURLValid($element_name,$element_value)
  {
    if (preg_match("/^(http(s?):\/\/|ftp:\/\/{1})((\w+\.){1,})\w{2,}$/i", $element_value)) {
      return TRUE;
    } else {
      return FALSE;
    }
  }
  
  /**
   * Makes sure at least one file was uploaded
   *
   * @param   string  $element_name	name of form field to check
   * @param   string  $element_value	
   * @return  bool
   */
  function EnsureUploadedFile($element_name, $element_value)
  {
    foreach($_FILES AS $name => $data){
      if($data['error'] == '0'){
	return TRUE;
      }
    }
    return FALSE;
  }
  
  function saveDcpRegtool ($sdesk_num, $values_array)
  {
    global $connection; // eventually this can get taken out

    $dcpProcedure = new dcpProcedure();
    $dcp = $dcpProcedure->joinDCPTables();
    $dcp->get($sdesk_num);
    $sun_server = $dcp->getLink('sysid');
    $sysid = $sun_server->sysid;
    $Sun_Server = new dcpSun_Server($connection,$sysid);
    
    //DB_DataObject::debugLevel(5);	      
    $original_sun_server = clone($sun_server); // clone is emulated in php4 for compatibility reasons.

    error_log("made it here ONE");
    foreach ($values_array as $label => $col) {
      if ( $sun_server->$label ) 
	{
	  $sun_server->$label = "$col";
	}
      elseif ( $label == 'frmware_disks_id' )            
	{
	  $Sun_Server->setFrmware_disks_id($col);	      	  	  
	}
      elseif ( $label == 'frmware_hba_id' )      
	{
	  $Sun_Server->setFrmware_hba_id($col);	      	  
	}
    }
    $result = $sun_server->update($original_sun_server); // only update the difference between new and old
    //DB_DataObject::debugLevel(0);    
  }
  
}


?>