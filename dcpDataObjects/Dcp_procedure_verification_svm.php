<?php
/**
 * Table Definition for dcp_procedure_verification_svm
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Dcp_procedure_verification_svm extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'dcp_procedure_verification_svm';    // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $metadb_defined_on_two_disks;     // string(3)  not_null enum
    public $boot_from_mirror_enabled;        // string(3)  not_null enum
    public $lvm_md_tab_updated;              // string(3)  not_null enum

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Dcp_procedure_verification_svm',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
