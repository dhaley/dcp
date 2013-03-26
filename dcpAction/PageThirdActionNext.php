<?php

require_once "dcpAction.php";
require_once "dcpHostname.php";
class PageThirdActionNext extends dcpAction
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
	$dcp_action = $data['values'][$pageName]['dcp_action'];

		
 	$full_hostname = $data['values'][$pageName]['full_hostname'];
 	$data['values']['perm']['full_hostname'] = $full_hostname;
 	$hostname = new dcpHostname($full_hostname);
 	if ( $hostname->validateHostname() ) {
	  echo "<hr>";
	  print_r($dcp_action);
	  echo "<hr>";
	  
	  $host_name = $hostname->returnOnlyHostname();
	  $domain_name = $hostname->returnOnlyDomainname();

	  $data['values']['perm']['hostname'] = $host_name;
	  $data['values']['perm']['domain_name'] = $domain_name;
	  
	  $dcpRegtool = new dcpRegtool($host_name,$domain_name);
	  $row = $dcpRegtool->getRow();
	  
	  $data['values']['perm']['regToolRows'] = $row;
	  
	  if ( isset ( $row[0] ) ) {
	    $next =& $page->controller->getPage('page4');
	    // Investigate what handle does can we just call page directly....?????
	    $next->handle('jump');
	  }
	  else {
	    echo "$host_name $domain_name doesn't exist in Regtool<p>\n";
	  }
	}
 	else {
 	    print "$full_hostname is not a valid PSC standare hostname<br>\n";
	}
    }
}

?>