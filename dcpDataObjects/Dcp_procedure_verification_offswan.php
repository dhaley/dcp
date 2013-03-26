<?php
/**
 * Table Definition for dcp_procedure_verification_offswan
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Dcp_procedure_verification_offswan extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'dcp_procedure_verification_offswan';    // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $moved_off_swan;                  // string(3)  not_null enum
    public $autofs_disabled;                 // string(3)  not_null enum

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Dcp_procedure_verification_offswan',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
