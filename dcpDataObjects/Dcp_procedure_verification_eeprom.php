<?php
/**
 * Table Definition for dcp_procedure_verification_eeprom
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Dcp_procedure_verification_eeprom extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'dcp_procedure_verification_eeprom';    // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $mirror_boot_disk_defined;        // string(3)  not_null enum
    public $auto_boot_on_error;              // string(3)  not_null enum
    public $auto_boot;                       // string(3)  not_null enum

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Dcp_procedure_verification_eeprom',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
