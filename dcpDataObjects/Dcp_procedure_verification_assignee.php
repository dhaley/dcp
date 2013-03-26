<?php
/**
 * Table Definition for dcp_procedure_verification_assignee
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Dcp_procedure_verification_assignee extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'dcp_procedure_verification_assignee';    // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $assignee;                        // string(50)  not_null primary_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Dcp_procedure_verification_assignee',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
