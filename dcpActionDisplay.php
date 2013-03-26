<?php

require_once "HTML/QuickForm/Action/Display.php";
require_once 'HTML/QuickForm/Renderer/ArraySmarty.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class dcpActionDisplay extends HTML_QuickForm_Action_Display
{

  var $tplFile;
  var $_frame_template;
  
  function dcpActionDisplay ($tplFile)
  {
    $this->tplFile = $tplFile;
  } 

  function _renderForm(&$page) 
  {
    $pageName = $page->getAttribute('name');

    $this->setUpPage($page);
    if ( ! $page->_smarty_template==FALSE )
      {
	$sdesk_num = $page->sdesk_num;
	// // Create the template object
	$dcp_smarty = $page->createSmarty();
	$renderer = $this->renderSmarty($dcp_smarty);
	$page->accept($renderer);
	$dcp_smarty->assign('form_data', $renderer->toArray());
	// parse and display the template
	$contents = $dcp_smarty->fetch("$this->tplFile");
      }
    else
      {
	$renderer =& $page->defaultRenderer();
	$this->renderHTML($renderer);
 	$page->accept($renderer);
	$contents = $renderer->toHtml();
      }
    $smarty = $page->createSmarty();
    $smarty->assign('contents',$contents);
    $smarty->display($this->frame_template==''?"frame.tpl":$this->frame_template);
  }

  function renderSmarty ($dcp_smarty)
  {
    // Create the renderer object	
    $renderer =& new HTML_QuickForm_Renderer_ArraySmarty($dcp_smarty);
    $renderer->setRequiredTemplate(
				   '{if $error}
          <font color="red">{$label|upper}</font>
      {else}
          {$label}
          {if $required}
              <font color="red" size="1">*</font>
          {/if}
      {/if}'
				   );
    $renderer->setErrorTemplate(
				'{if $error}
          <font color="orange" size="1">{$error}</font><br />
      {/if}
      {$html}'
				);
    error_log("set up renderer");
    return $renderer;
  }

  
  function renderHTML ($renderer)
  {
	$renderer->setHeaderTemplate('<tr><td style="white-space:nowrap;background:#CCCCCC;color:#ffc;" align="left" colspan="2"><b>{header}</b></td></tr>');
 	$renderer->setFormTemplate('<table width="500" border="0" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE"><form{attributes}>{content}</form></table>');
	$renderer->setGroupTemplate('<table><tr>{content}</tr></table>', 'name');
	$renderer->setGroupElementTemplate('<td>{element}<br /><span style="font-size:10px;"><!-- BEGIN required --><span style="color: #f00">*</span><!-- END required --><span style="color:#996;">{label}</span></span></td>', 'name');

  }

  function setUpPage ($page)
  {
    $page->setRequiredNote(
			   '<font color="red" size="2">
		  *&nbsp;
	  </font>
	  <font color="blue" size="2">
		  This field is mandatory
	  </font>');
    $page->setJsWarnings('Those fields have errors :', 'Thanks for correcting them.');
  }
  
}

?>