<?php

  /**
 * Table Definition for all_dcps
 */

require_once 'DB/DataObject.php';

class dcpDataObjects_All_dcps extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'all_dcps';                        // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $short_desc;                      // string(80)  not_null
    public $hostname;                        // string(128)  not_null unique_key
    public $os_name;                         // string(50)  not_null unique_key
    public $os_version_name;                 // string(50)  not_null unique_key
    public $processor_type_name;             // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_All_dcps',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
    var $fb_createSubmit = true;
    var $fb_linkDisplayLevel = 2;
    function preGenerateForm(&$fb) {
      $fb->elementTypeMap = array('shorttext' => 'text', 'date' => 'myDate');
    }
}
