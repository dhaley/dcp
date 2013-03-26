<?php
/**
 * Table Definition for processor_type
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Processor_type extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'processor_type';                  // table name
    public $processor_type_id;               // int(2)  not_null primary_key
    public $processor_type_name;             // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Processor_type',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
