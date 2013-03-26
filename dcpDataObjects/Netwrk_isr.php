<?php
/**
 * Table Definition for netwrk_isr
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Netwrk_isr extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'netwrk_isr';                      // table name
    public $netwrk_isr_id;                   // int(2)  not_null primary_key
    public $netwrk_isr_name;                 // string(100)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Netwrk_isr',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
