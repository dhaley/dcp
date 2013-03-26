<?php

require_once 'dcpWizard.php';
require_once "dcpPage/StageOne.php";
require_once "dcpPage/StageTwo.php";
require_once "dcpPage/StageTwoB.php";
require_once "dcpPage/StageThree.php";
require_once "dcpPage/StageFour.php";
require_once "dcpPage/StageFive.php";
require_once "dcpPage/StageSix.php";
require_once "dcpPage/StageSeven.php";
//require_once "dcpPage/StageEight.php";
//require_once "dcpPage/StageNine.php";
require_once "dcpController.php";
require_once "dcpAction/PageFirstActionNext.php";
require_once "dcpAction/PageSecondActionNext.php";
require_once "dcpAction/PageSecondActionBack.php";
require_once "dcpAction/PageThirdActionNext.php";
require_once "dcpAction/PageFourthActionNext.php";
require_once "dcpAction/PageFifthActionNext.php";
require_once "dcpAction/PageSixthActionNext.php";
require_once "dcpAction/PageSeventhActionNext.php";
//require_once "dcpAction/PageEighthActionNext.php";
require_once "dcpAction/dcpActionProcess.php";
require_once "dcpActionDisplay.php";

class dcpNewWizard extends dcpWizard
{

  function Run ()
  {
    $controller =& new HTML_QuickForm_Controller('PSC DCP Tracker');

    $controller->container($reset = false);
    
    $page1 =& new StageOne('page1');
    $page1->addAction('next',  new PageFirstActionNext());

    $page2a =& new StageTwo('page2a');
    $page2a->addAction('next', new  PageSecondActionNext());
    $page2a->addAction('back', new PageSecondActionBack());
    
    $page2b =& new StageTwoB('page2b');
    $page2b->addAction('back', new PageSecondActionBack());

    $page3 =& new StageThree('page3');
    $page3->addAction('next', new PageThirdActionNext());
    
    $page4 =& new StageFour('page4');
    $page4->addAction('next', new PageFourthActionNext());
    
    $page5 =& new StageFive('page5');
    $page5->addAction('next', new PageFifthActionNext());
    
    $page6 =& new StageSix('page6');
    $page6->addAction('next', new PageSixthActionNext());

    $page7 =& new StageSeven('page7');
    $page7->addAction('next', new PageSeventhActionNext()); 

    //    $page8 =& new StageEight('page8');
    //    $page8->addAction('next', new PageEighthActionNext()); 

    //    $page9 =& new StageNine('page9');

    //$page5->addAction('next', new HTML_QuickForm_Action_Next());

    // Add the page to Controller

    $controller->addPage($page1);
    $controller->addPage($page2a);
    $controller->addPage($page2b);
    $controller->addPage($page3);
    $controller->addPage($page4);
    $controller->addPage($page5);
    $controller->addPage($page6);
    $controller->addPage($page7);
    //    $controller->addPage($page8);
    //    $controller->addPage($page9);
    $controller->addAction('display', new dcpActionDisplay('edit_dcp2.tpl'));
    
    // Process the request
    $controller->run();
  }

}


?>