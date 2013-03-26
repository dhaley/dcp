<?php
/**
 * Table Definition for server_frmware_hba
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Server_frmware_hba extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'server_frmware_hba';              // table name
    public $sysid;                           // real(14)  not_null primary_key unsigned
    public $frmware_hba_id;                  // int(2)  not_null primary_key multiple_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Server_frmware_hba',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
