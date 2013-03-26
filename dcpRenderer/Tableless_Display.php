<?php

require_once 'HTML/QuickForm/Action/Display.php';
require_once 'HTML/QuickForm/Renderer/Tableless.php'; 

class Tableless_Display extends HTML_QuickForm_Action_Display  
{  
  function _renderForm(&$page)  
  {  
    $renderer =& new HTML_QuickForm_Renderer_Tableless();  
    $page->accept($renderer);  
    echo $renderer->toHtml();  
  }  
}

?>