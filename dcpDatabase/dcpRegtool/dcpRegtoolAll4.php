<?php

require_once "dcpDatabase/dcpRegtool.php";

//require_once "dcpDatabase/RegtoolDataSource.php";
require_once 'Structures/DataGrid.php';

require_once "DB.php";

require "regtool_db.inc";

//require_once 'Structures/DataGrid/DataSource.php';


  // Definition of dcp class dcpRegtool
  // methods will get, set and retrieve Regtool data
  //

class dcpRegtoolAll4 extends dcpRegtool {

  // Member variables
  var $host_name;
  var $domain_name;

  // functions

  function validateDomain () {
    foreach ($this->__domains as $realdomain ) {
      $pattern = "/^$realdomain\..+$/";
      if ( preg_match( $pattern , $this->domain_name ) ) {
 	$this->domain_name = $realdomain; # shorten primary domain
	return;
      }
    }
  }
  
  function validateHostname () { // make sure hostname and domain exist
    if ( preg_match('/^([^.]+)\.(.+)$/', $this->full_hostname,$hostname_parts ) ) {
      $this->host_name = $hostname_parts[1];
      $this->domain_name = $hostname_parts[2];
      $this->validateDomain();
      return 1;
    } else {
      return 0;
    }
  }

  function populate () {
    
    $SQL = "SELECT ";
    $SQL .= " 'app_server' AS system_class, ";
    $SQL .= " system_id, ";
    $SQL .= " status, ";
    $SQL .= " primary_hostname, ";
    $SQL .= " primary_domain, ";
    $SQL .= " serial_number, ";
    $SQL .= " location, ";
    $SQL .= " hostid, ";
    $SQL .= " eds_service_level, ";
    $SQL .= " system_model_name, ";
    $SQL .= " operation_env, ";
    $SQL .= " network_access, ";
    $SQL .= " in_production, ";
    $SQL .= " division ";
    $SQL .= " FROM app_server_report ";
    $SQL .= " WHERE status = 'R' ";
    $SQL .= " AND access_level like 'EDS%' ";

    $SQL .= " UNION ALL ";
    $SQL .= " SELECT ";
    $SQL .= " 'network_server' AS system_class, ";
    $SQL .= " system_id, ";
    $SQL .= " status, ";
    $SQL .= " primary_hostname, ";
    $SQL .= " primary_domain, ";
    $SQL .= " serial_number, ";
    $SQL .= " location, ";
    $SQL .= " hostid, ";
    $SQL .= " eds_service_level, ";
    $SQL .= " system_model_name, ";
    $SQL .= " operation_env, ";
    $SQL .= " network_access, ";
    $SQL .= " in_production, ";
    $SQL .= " division ";
    $SQL .= " FROM network_server_report ";
    $SQL .= " WHERE status = 'R' ";
    $SQL .= " AND access_level like 'EDS%' ";
    $SQL .= " ORDER by primary_hostname, primary_domain, location ";

    //$dg =& new Structures_DataGrid();

    // Get my data
    //$result = $this->connection->query($SQL);

    // if (PEAR::isError($result)) {
    //   echo "An error occurred while trying to run your query.<br>\n";
    //   echo "Error message: " . $result->getMessage() . "<br>\n";
    //   die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    // }

    //DB_DataObject::debugLevel(5);

    //  $datasource = new RegtoolDataSource();

    // Connect to server
    $connection = DB::connect($dsn);
    if (DB::isError($connection))
      die($connection->getMessage());


    //$count = $datasource->count();
    echo "There are $count cats in the farm\n\n";

    
    // Bind to DataGrid
    //$data = Structures_DataGrid_DataSource::create($result);
    //$dg->bindDataSource($data);

    // Print the DataGrid

    

  }

  // constructor function
  function __construct() {
    require "regtool_db.inc";
    //echo "DSN is $dsn";
    $this->_initialize($dsn);
  }
  
  }

?>