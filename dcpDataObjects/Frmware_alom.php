<?php
/**
 * Table Definition for frmware_alom
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Frmware_alom extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'frmware_alom';                    // table name
    public $frmware_alom_id;                 // int(2)  not_null primary_key
    public $frmware_alom_name;               // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Frmware_alom',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
