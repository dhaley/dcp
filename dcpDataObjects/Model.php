<?php
/**
 * Table Definition for model
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Model extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'model';                           // table name
    public $model_id;                        // int(2)  not_null primary_key
    public $model_name;                      // string(50)  not_null unique_key

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Model',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
