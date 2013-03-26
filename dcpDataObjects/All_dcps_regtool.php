<?php
/**
 * Table Definition for all_dcps_regtool
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_All_dcps_regtool extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'all_dcps_regtool';                // table name
    public $hostname;                        // string(128)  not_null unique_key
    public $frmware_obp_name;                // string(100)  unique_key
    public $frmware_alom_name;               // string(100)  unique_key
    public $frmware_hypervisor_name;         // string(100)  unique_key
    public $frmware_hba_name;                // string(100)  unique_key
    public $frmware_disks_name;              // string(100)  unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_All_dcps_regtool',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
