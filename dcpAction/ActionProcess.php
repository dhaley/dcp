<?php

require_once 'HTML/QuickForm/Action.php';

// Action to process the form
class ActionProcess extends HTML_QuickForm_Action
{
    function perform(&$page, $actionName)
    {
      error_log("made it to ActionProcess");
      echo "Submit successful!<br>\n<pre>\n";
      var_dump($page->controller->exportValues());
      echo "\n</pre>\n";
    }
}

?>