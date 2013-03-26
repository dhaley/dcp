<?php

require_once 'HTML/QuickForm/Action.php';
//require('/opt/coolstack/php5/lib/php/Smarty/Smarty.class.php');
//require_once 'dcpRenderer/Tableless_Display.php';
//require_once 'HTML/QuickForm/Renderer/ArraySmarty.php';

class dcpActionProcess extends HTML_QuickForm_Action {
   // This kicks in at the end of the wizard process and assign the data to a Smarty Var
   // Which can then be used by Smarty to display a summary of the information to the user
   
   var $_smartyReference = null;
   
   // function dcpActionProcess(&$smarty) {
   //    // The parent class doesn't have a constructor
   //    parent::__construct();
   //    $this->_smartyReference =$smarty;
   // }
   
   // function perform(&$page, $actionName) {
      
   //    // Let's first import the smarty Variable
   //    global $thisPage;
            
   //    $thisPage->assign("valuesExported",$page->controller->exportValues());
   // }

   // Action to process the form
   function perform(&$page, $actionName)
   {
     echo "Submit successful!<br>\n<pre>\n";
     var_dump($page->controller->exportValues());
     echo "\n</pre>\n";
   }
}



?>