 <?php

require 'Structures/DataGrid/DataSource.php';
require_once 'DB.php';

class RegtoolDataSource extends Structures_DataGrid_DataSource {
 
    var $db;
    var $orderBy = '';
    
    function RegtoolDataSource() {
      require "regtool_db.inc";      
      echo "$dsn is the dsn<p>";
	  $this->db = DB::connect($dsn);
	  if (DB::isError($this->db))
	    die($this->db->getMessage());

    }

    function count() {
	$query = "SELECT COUNT(*) ";
	$query .= " FROM app_server_report ";
	$query .= " WHERE status = 'R' ";
	$query .= " AND access_level like 'EDS%' ";
	$query .= " UNION ALL ";
	$query = "SELECT COUNT(*) ";
	$query .= " FROM network_server_report ";
	$query .= " WHERE status = 'R' ";
	$query .= " AND access_level like 'EDS%' ";

        return $this->db->getOne($query);
    }

    function sort($sortSpec, $sortDir = 'ASC') {
        $this->orderBy = "ORDER BY $sortSpec $sortDir"; 
    }

    function fetch($offset = 0, $len = null) {
        
        $limit = is_null($len) ? "LIMIT $offset,18446744073709551615" 
                               : "LIMIT $offset,$len";
    
	$query = "SELECT ";
	$query .= " 'app_server' AS system_class, ";
	$query .= " system_id, ";
	$query .= " status, ";
	$query .= " primary_hostname, ";
	$query .= " primary_domain, ";
	$query .= " serial_number, ";
	$query .= " location, ";
	$query .= " hostid, ";
	$query .= " eds_service_level, ";
	$query .= " system_model_name, ";
	$query .= " operation_env, ";
	$query .= " network_access, ";
	$query .= " in_production, ";
	$query .= " division ";
	$query .= " FROM app_server_report ";
	$query .= " WHERE status = 'R' ";
	$query .= " AND access_level like 'EDS%' ";

	// $query .= " UNION ALL ";
	// $query = "SELECT  ";
	// $query .= " 'app_server' AS system_class, ";
	// $query .= " system_id, ";
	// $query .= " status, ";
	// $query .= " primary_hostname, ";
	// $query .= " primary_domain, ";
	// $query .= " serial_number, ";
	// $query .= " location, ";
	// $query .= " hostid, ";
	// $query .= " eds_service_level, ";
	// $query .= " system_model_name, ";
	// $query .= " operation_env, ";
	// $query .= " network_access, ";
	// $query .= " in_production, ";
	// $query .= " division ";
	// $query .= " FROM network_server_report ";
	// $query .= " WHERE status = 'R' ";
	// $query .= " AND access_level like 'EDS%' ";

	//$query .= $this->_orderBy . " $limit";
	//$query .= $this->_orderBy . " primary_hostname, primary_domain";
        return $this->db->getAll($query);
    }
}

?> 