 <?php

require 'Structures/DataGrid/DataSource.php';
require_once 'DB.php';

class MysqlDataSource extends Structures_DataGrid_DataSource {
 
    var $db;
    var $orderBy = '';
    
    function MysqlDataSource() {
      require "db.inc";
      echo "$dsn is the string<p>";
      $this->db = DB::connect($dsn);
    }

    function count() {
	$query = "SELECT COUNT(*) ";
	$query .= " FROM sun_server ";
        return $this->db->getOne($query);
    }

    function sort($sortSpec, $sortDir = 'ASC') {
        $this->orderBy = "ORDER BY $sortSpec $sortDir"; 
    }

    function fetch($offset = 0, $len = null) {
        
        $limit = is_null($len) ? "LIMIT $offset,18446744073709551615" 
                               : "LIMIT $offset,$len";
    
	$query = "SELECT * ";
	$query .= " FROM sun_server ";
	$query .= $this->_orderBy . " $limit";

        return $this->db->getAll($query);
    }
}

?> 