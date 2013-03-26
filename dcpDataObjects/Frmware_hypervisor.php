<?php
/**
 * Table Definition for frmware_hypervisor
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Frmware_hypervisor extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'frmware_hypervisor';              // table name
    public $frmware_hypervisor_id;           // int(2)  not_null primary_key
    public $frmware_hypervisor_name;         // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Frmware_hypervisor',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
