<?php
/**
 * Table Definition for op_env
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Op_env extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'op_env';                          // table name
    public $op_env_id;                       // int(2)  not_null primary_key
    public $op_env_name;                     // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Op_env',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
