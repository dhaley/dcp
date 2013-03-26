<?php

class PageSecondActionBack extends HTML_QuickForm_Action_Back
{
    function perform(&$page, $actionName)
    {
        // save the form values and validation status to the session
        $page->isFormBuilt() or $page->buildForm();
        $pageName =  $page->getAttribute('id');
        $data     =& $page->controller->container();
        $data['values'][$pageName] = $page->exportValues();
        if (!$page->controller->isModal()) {
            if (PEAR::isError($valid = $page->validate())) {
                return $valid;
            }
            $data['valid'][$pageName] = $valid;
        }

        $prev =& $page->controller->getPage('page1');
        $prev->handle('jump');
    }
}

?>