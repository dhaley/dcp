<?php
/**
 * Table Definition for frmware_disks
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Frmware_disks extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'frmware_disks';                   // table name
    public $frmware_disks_id;                // int(2)  not_null primary_key
    public $frmware_disks_name;              // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Frmware_disks',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
