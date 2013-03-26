<?php
/**
 * Table Definition for os_version
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Os_version extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'os_version';                      // table name
    public $os_version_id;                   // int(2)  not_null primary_key
    public $os_version_name;                 // string(50)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Os_version',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
