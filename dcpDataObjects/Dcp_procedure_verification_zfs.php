<?php
/**
 * Table Definition for dcp_procedure_verification_zfs
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Dcp_procedure_verification_zfs extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'dcp_procedure_verification_zfs';    // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $boot_zpool;                      // string(3)  not_null enum

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Dcp_procedure_verification_zfs',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
