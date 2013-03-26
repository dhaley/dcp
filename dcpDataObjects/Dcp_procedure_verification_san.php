<?php
/**
 * Table Definition for dcp_procedure_verification_san
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Dcp_procedure_verification_san extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'dcp_procedure_verification_san';    // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $san_cr_num;                      // int(10)  
    public $san_switch_port_requested_date;    // datetime(19)  binary
    public $san_connected_date;              // datetime(19)  binary

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Dcp_procedure_verification_san',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
