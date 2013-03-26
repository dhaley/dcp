<?php

require_once "dcpDatabase/dcpRegtool.php";

  // Definition of dcp class dcpRegtool
  // methods will get, set and retrieve Regtool data
  //

class dcpRegtoolAll extends dcpRegtool {

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
    $SQL .= " SUPPORT_TRANS.support_name as 'eds_service_level', ";
    $SQL .= " SYS_MOD_MAST.system_model_name, ";
    $SQL .= " SUPPORT_TRANS2.support_name as 'operation_environment', ";
    $SQL .= " SUPPORT_TRANS3.support_name as 'network_access', ";
    $SQL .= " SUPPORT_TRANS4.support_name as 'in_production', ";
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
    $SQL .= " ORDER by primary_hostname, primary_domain, location ";

    //        $SQL .= " AND SYS.primary_hostname = 'dome' ";
    //        $SQL .= " AND SYS.primary_domain = 'central' ";

    $result = $this->connection->query($SQL);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }

    $fh = fopen('/tmp/all_hosts', 'w') or die ("can't open file");

    $num_rows = $result->numRows();
    echo "<h3>Number of hosts under PSC support: $num_rows</h3>";

    
    if ( ($num_rows) && ($num_rows > 0) ) {
      $num == 1;
      echo "<table>\n";
      echo "<tr>";
      //echo "<th>#</th> ";
      echo "<th>hostname</th> <th>domain</th> ";
      // echo "<th>sysid</th> <th>status</th> ";
      // echo "<th>EDS Service Level</th> <th>Operation Environment</th> ";
      // echo "<th>Network Access</th> <th>In Production</th> ";
      // echo "<th>Division</th>  ";
      echo "</tr>\n"; 

      while ($row = $result->fetchRow(DB_FETCHMODE_ASSOC)) {
	echo "<tr>";
	//echo "<td>$num</td>";
	echo "<td>".$row['primary_hostname']."</td>";
	echo "<td>".$row['primary_domain']."</td>";

	$string = $row['primary_hostname'] . " " . $row['primary_domain'] . "\n";
	if (-1 == fwrite($fh,"$string")) { die ("can't wire data"); }

	// echo "<td>".$row['system_id']."</td><td>".$row['status']."</td>";
	// echo "<td>".$row['eds_service_level']."</td><td>".$row['operation_environment']."</td>";
	// echo "<td>".$row['network_access']."</td><td>".$row['in_production']."</td>";
	// echo "<td>".$row['division']."</td>";
	echo "</tr>\n";
	$num++;
      } 
      echo "</table>\n"; 
      $result->free();
    }
    fclose($fh);
  }

  // constructor function
  function __construct() {
    require "regtool_db.inc";
    //echo "DSN is $dsn";
    $this->_initialize($dsn);
  }
  
  }

?>