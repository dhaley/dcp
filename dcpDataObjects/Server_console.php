<?php
/**
 * Table Definition for server_console
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Server_console extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'server_console';                  // table name
    public $console_id;                      // int(2)  not_null primary_key
    public $console_hostname;                // string(128)  not_null
    public $console_port;                    // int(2)  not_null

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Server_console',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE
}
