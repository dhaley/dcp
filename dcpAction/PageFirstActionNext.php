<?php

require_once "dcpAction.php";
require_once 'dcpDataObjects/Dcp_procedure_verification.php';
require_once 'dcpPage/dcpView.php';

class PageFirstActionNext extends dcpAction
{
  function perform(&$page, $actionName)
  {
    $page->isFormBuilt() or $page->buildForm();
    $pageName =  $page->getAttribute('id');
	
    // Get the container from the page's controller
    $data     =& $page->controller->container();
    $nextName = $data['values'][$pageName]['iradPageAB'];
    $data['values'][$pageName] = $page->exportValues();

    if (PEAR::isError($valid = $page->validate())) {
      return $valid;
    }
    $data['valid'][$pageName] = $valid;

    // Modal form and page is invalid: don't go further
    if ($page->controller->isModal() && !$data['valid'][$pageName]) {
      return $page->handle('display');
    }

    $sdesk_num = $data['values'][$pageName]['sdesk_num'];

    // Let's assign $sdesk_num to a more permanent place
    $data['values']['perm']['sdesk_num'] = $sdesk_num;

    $dcp = new dcpDataObjects_Dcp_procedure_verification;
    $dcp->sdesk_num = $sdesk_num;
    $num_rows = $dcp->find();

    $data['values']['perm']['num_rows'] = $num_rows;
	
    if ( ($num_rows) && ($num_rows > 0) ) { // View Page
      $dcpView = new dcpView;
      $dcpView->smartyIze($sdesk_num);
      $dcpView->viewDisplay();
    }
    else {



      
      // we should verify that service desk ticket is actually in service desk
      $dcpServiceDesk = new dcpServiceDesk($sdesk_num);
      $row = $dcpServiceDesk->getRow();
      
      if ( isset ( $row[0] ) ) {
	if (empty($nextName)) {
	  $nextName = 'page1';
	}
	else {
	  $data['values']['perm']['sdesk_row'] = $row;	      	      	      
	  $nextName = 'page2a';
	}
      }
      else {
	$nextName = 'page2b';
      }
      
      if ($nextName == 'page2a') {
	$data['valid']['page2b'] = true;
      } else {
	$data['valid']['page2a'] = true;
      }
      $next =& $page->controller->getPage($nextName);
      $next->handle('jump');
    }
  }
}

?>