<?php

require_once "dcpDatabase.php";

  // Definition of dcp class dcpRegtool
  // methods will get, set and retrieve Regtool data
  //

class dcpRegtool extends dcpDatabase {

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
    $SQL .= " SYS.system_id, ";
    $SQL .= " SYS.status, ";
    $SQL .= " SYS.primary_hostname, ";
    $SQL .= " SYS.primary_domain, ";
    $SQL .= " SYS.serial_number, ";
    $SQL .= " SYS.location, ";
    $SQL .= " SYS.hostid, ";
    $SQL .= " SUPPORT_TRANS.support_name, ";
    $SQL .= " SYS_MOD_MAST.system_model_name, ";
    $SQL .= " SUPPORT_TRANS2.support_name, ";
    $SQL .= " SUPPORT_TRANS3.support_name, ";
    $SQL .= " SUPPORT_TRANS4.support_name, ";
    $SQL .= " BUS_UNIT.division ";
    $SQL .= " FROM system SYS, ";
    $SQL .= " system_support SYS_SUPPORT, support_translate SUPPORT_TRANS, ";
    $SQL .= " system_class_master SYS_CLASS_MAST, system_model_master SYS_MOD_MAST, ";
    $SQL .= " system_support SYS_SUPPORT2, support_translate SUPPORT_TRANS2, ";
    $SQL .= " system_support SYS_SUPPORT3, support_translate SUPPORT_TRANS3, ";
    $SQL .= " system_support SYS_SUPPORT4, support_translate SUPPORT_TRANS4, ";
    $SQL .= " system_support SYS_SUPPORT5, support_translate SUPPORT_TRANS5, ";
    $SQL .= " business_unit BUS_UNIT ";
    $SQL .= " WHERE ";
    $SQL .= " SYS.system_id = SYS_SUPPORT.system_id ";
    $SQL .= " AND SYS_SUPPORT.support_id = SUPPORT_TRANS.support_id ";
    $SQL .= " AND SUPPORT_TRANS.support_category_name = 'EDS Service Level' ";
    $SQL .= " AND SYS.system_class_id = SYS_CLASS_MAST.system_class_id ";
    $SQL .= " AND (SYS_CLASS_MAST.system_class_name = 'APPLICATION_SERVER' or SYS_CLASS_MAST.system_class_name = 'NETWORK_SERVER') ";
    $SQL .= " AND SYS.system_model_id = SYS_MOD_MAST.system_model_id ";
    $SQL .= " AND SYS.system_id = SYS_SUPPORT2.system_id ";
    $SQL .= " AND SYS_SUPPORT2.support_id = SUPPORT_TRANS2.support_id ";
    $SQL .= " AND SUPPORT_TRANS2.support_category_name = 'Operation Environment' ";
    $SQL .= " AND SYS.system_id = SYS_SUPPORT3.system_id ";
    $SQL .= " AND SYS_SUPPORT3.support_id = SUPPORT_TRANS3.support_id ";
    $SQL .= " AND SUPPORT_TRANS3.support_category_name = 'Network Access' ";
    $SQL .= " AND SYS.system_id = SYS_SUPPORT4.system_id ";
    $SQL .= " AND SYS_SUPPORT4.support_id = SUPPORT_TRANS4.support_id ";
    $SQL .= " AND SUPPORT_TRANS4.support_category_name = 'In Production' ";
    $SQL .= " AND SYS.system_id = SYS_SUPPORT5.system_id ";
    $SQL .= " AND SYS_SUPPORT5.support_id = SUPPORT_TRANS5.support_id ";
    $SQL .= " AND SUPPORT_TRANS5.support_name like 'EDS%' ";
    $SQL .= " AND substring(SYS.chargeback_dept,4,3) *= convert(char(3),BUS_UNIT.bus_unit_id) ";
    $SQL .= " AND SYS.status = 'R' ";
    $SQL .= " AND SYS.primary_hostname = '" . $this->host_name . "' ";
    $SQL .= " AND SYS.primary_domain = '" . $this->domain_name . "' ";

    $result = $this->connection->query($SQL);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
 
    $num_rows = $result->numRows();

    if ( ($num_rows) && ($num_rows > 0) ) {
      //      $this->row = $result->fetchRow(DB_FETCHMODE_ASSOC);
      $this->row = $result->fetchRow();      
    }
  }

  // constructor function
  function __construct($host_name,$domain_name) {
    $this->host_name = $host_name;
    $this->domain_name = $domain_name;
    require "regtool_db.inc";  
    $this->_initialize($dsn);
  }
  
  }

?>