<?php
/**
 * Table Definition for model_id_seq
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Model_id_seq extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'model_id_seq';                    // table name
    public $id;                              // int(10)  not_null primary_key unsigned auto_increment

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Model_id_seq',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
