<?php

require_once "HTML/QuickForm/Action/Display.php";
require_once 'HTML/QuickForm/Renderer/ArraySmarty.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once 'dcpSmarty/dcpView.php';

class dcpActionDisplay2 extends HTML_QuickForm_Action_Display
{

  var $tplFile;

  function dcpActionDisplay2 ($tplFile)
  {
     $this->tplFile = $tplFile;
  } 
  
    function _renderForm(&$page) 
    {
      $pageName = $page->getAttribute('name');
      $page->setRequiredNote(
			     '<font color="red" size="2">
		  *&nbsp;
	  </font>
	  <font color="blue" size="2">
		  This field is mandatory
	  </font>');
      $page->setJsWarnings('Those fields have errors :', 'Thanks for correcting them.');
      //$page->setDefaults(
      //            array(
      //          'cust_lname' => 'nachname'
      //          )
      // );       

      
      $sdesk_num = $page->sdesk_num;
      error_log("dcpActionDisplay: page is $pageName and sdesk num is $sdesk_num");
      $dcpView = new dcpView;
      $dcpView->smartyIze($sdesk_num);
      // Create the template object
      $dcp_smarty = $dcpView->getSmarty();
      
      // Create the renderer object	
      $renderer =& new HTML_QuickForm_Renderer_ArraySmarty($dcp_smarty);
      //$renderer =& new HTML_QuickForm_Renderer_Array($dcp_smarty);

      // $renderer->setRequiredTemplate(
      // 				     '{if $error}
      //     <font color="red">{$label|upper}</font>
      // {else}
      //     {$label}
      //     {if $required}
      //         <font color="red" size="1">*</font>
      //     {/if}
      // {/if}'
      // 				     );
      // $renderer->setErrorTemplate(
      // 				  '{if $error}
      //     <font color="orange" size="1">{$error}</font><br />
      // {/if}
      // {$html}'
      // 				  );
      $page->accept($renderer);
      $dcp_smarty->assign('form_data', $renderer->toArray());
      // parse and display the template
      $dcp_smarty->display($this->tplFile);
      
      //      echo "<pre>";var_dump($renderer->toArray());echo "</pre>";
      
      $page_action = $page->controller->getActionName();
      error_log("page action is $page_action");
      $pageURL = $page->getAttribute("action");
      error_log("pageUrl is $pageURL");
    }
}

?>