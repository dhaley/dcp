<?php
/**
 * Table Definition for slevel
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Slevel extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'slevel';                          // table name
    public $slevel_id;                       // int(2)  not_null primary_key
    public $slevel_name;                     // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Slevel',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
