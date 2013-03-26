<?php

  //require_once 'HTML/QuickForm/Action.php';
require_once "dcpAction.php";

//class PageClearAction extends HTML_QuickForm_Action
class PageClearAction extends dcpAction
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


      $page->controller->container($reset = true);

      error_log("made it to PageClearAction");
      
      //      $data     =& $page->controller->container();
      //      $data($reset = true);
      	  
      //$page->isFormBuilt() or $page->buildForm();

	
    // Get the container from the page's controller
      //    $data['values'][$pageName] = $page->exportValues();


    $next =& $page->controller->getPage($page1);
    $next->handle('jump');
    }
}


?>