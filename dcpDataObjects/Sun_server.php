<?php
/**
 * Table Definition for sun_server
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Sun_server extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'sun_server';                      // table name
    public $sysid;                           // real(15)  not_null primary_key
    public $hostname;                        // string(128)  not_null unique_key
    public $status;                          // string(1)  not_null
    public $hostid;                          // string(15)  not_null
    public $serial_number;                   // string(20)  not_null
    public $division;                        // string(40)  not_null
    public $model_id;                        // int(2)  not_null multiple_key
    public $location_id;                     // int(2)  not_null multiple_key
    public $netwrk_isr_id;                   // int(2)  not_null multiple_key
    public $slevel_id;                       // int(2)  not_null multiple_key
    public $op_env_id;                       // int(2)  not_null multiple_key
    public $frmware_obp_id;                  // int(2)  multiple_key
    public $frmware_alom_id;                 // int(2)  multiple_key
    public $frmware_hypervisor_id;           // int(2)  multiple_key
    public $os_instance_id;                  // int(2)  multiple_key
    public $regtool_prod_status;             // string(3)  not_null enum
    public $console_id;                      // int(2)  multiple_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Sun_server',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
    var $fb_linkDisplayFields = array('hostname');
}
