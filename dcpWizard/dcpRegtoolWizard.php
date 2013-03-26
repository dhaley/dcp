<?php

require_once 'dcpWizard.php';
require_once "dcpPage/StageThree.php";
require_once "dcpPage/StageFour.php";
require_once "dcpAction/PageThirdActionNext.php";
require_once "dcpAction/PageFourthActionNext.php";
require_once "dcpController.php";

class dcpRegtoolWizard extends dcpWizard
{

  function Run ($sdesk_num,$dcp_action)
  {
    $controller =& new HTML_QuickForm_Controller('PSC DCP Tracker');

    // Set defaults for the form elements
    $controller->setDefaults(array(
				   'sdesk_num' => $sdesk_num,
				   'dcp_action' => $dcp_action
				   ));

    $page3 =& new StageThree('page3');
    $page3->addAction('next',  new PageThirdActionNext());

    $page4 =& new StageFour('page4');
    $page4->addAction('next', new PageFourthActionNext());


    $controller->addPage($page3);
    $controller->addPage($page4);
    $controller->run();
    
  }
}
?>