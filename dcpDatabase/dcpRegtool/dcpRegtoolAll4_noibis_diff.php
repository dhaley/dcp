<?php

require_once "dcpDatabase/dcpRegtool.php";

  // Definition of dcp class dcpRegtool
  // methods will get, set and retrieve Regtool data
  //

class dcpRegtoolAll4_noibis_diff extends dcpRegtool {

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
    $SQL .= " system_model_name, ";
    $SQL .= " location, ";
    $SQL .= " hostid, ";
    $SQL .= " access_level, ";
    $SQL .= " eds_service_level, ";
    $SQL .= " operation_env, ";
    $SQL .= " network_access, ";
    $SQL .= " notes, ";
    $SQL .= " in_production, ";
    $SQL .= " division ";
    $SQL .= " FROM app_server_report ";
    $SQL .= " WHERE status = 'R' ";
    //    $SQL .= " AND access_level like 'EDS%' ";
    $SQL .= " AND access_level = 'EDS' or access_level = 'EDS BU HOSTING'";
    // $SQL .= " AND primary_hostname not like '%aclt%' ";
    // $SQL .= " AND primary_hostname not like '%bbrm%' ";
    // $SQL .= " AND primary_hostname not like '%bclt%' ";
    // $SQL .= " AND primary_hostname not like '%ibis%' ";
    // $SQL .= " AND primary_hostname not like '%pbrm%' ";
    // $SQL .= " AND primary_hostname not like '%pclt%' ";
    // $SQL .= " AND primary_hostname not like '%nb-cltmas%' ";
    // $SQL .= " AND primary_hostname not like '%nb-brmmas%' ";
    $SQL .= " AND system_model_name != 'Cyclades' ";
    //$SQL .= " AND notes not like '%NT%' ";

    $SQL .= " UNION ALL ";

    $SQL .= " SELECT ";
    $SQL .= " 'network_server' AS system_class, ";
    $SQL .= " system_id, ";
    $SQL .= " status, ";
    $SQL .= " primary_hostname, ";
    $SQL .= " primary_domain, ";
    $SQL .= " serial_number, ";
    $SQL .= " system_model_name, ";
    $SQL .= " location, ";
    $SQL .= " hostid, ";
    $SQL .= " access_level, ";
    $SQL .= " eds_service_level, ";
    $SQL .= " operation_env, ";
    $SQL .= " network_access, ";
    $SQL .= " notes, ";    
    $SQL .= " in_production, ";
    $SQL .= " division ";
    $SQL .= " FROM network_server_report ";
    $SQL .= " WHERE status = 'R' ";
    //    $SQL .= " AND access_level like 'EDS%' ";
    $SQL .= " AND access_level = 'EDS' or access_level = 'EDS BU HOSTING'";
    // $SQL .= " AND primary_hostname not like '%aclt%' ";
    // $SQL .= " AND primary_hostname not like '%bbrm%' ";
    // $SQL .= " AND primary_hostname not like '%bclt%' ";
    // $SQL .= " AND primary_hostname not like '%ibis%' ";
    // $SQL .= " AND primary_hostname not like '%pbrm%' ";
    // $SQL .= " AND primary_hostname not like '%pclt%' ";
    // $SQL .= " AND primary_hostname not like '%nb-cltmas%' ";
    // $SQL .= " AND primary_hostname not like '%nb-brmmas%' ";
    $SQL .= " AND system_model_name != 'Cyclades' ";
    //    $SQL .= " AND notes not like '%NT%' ";

    $SQL .= " ORDER by primary_hostname, primary_domain, location ";

	
    $result = $this->connection->query($SQL);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }


    $fh = fopen('/tmp/all_hosts_no_regtool_diff', 'w') or die ("can't open file");
    
    $num_rows = $result->numRows();
    echo "<h3>Number of hosts under PSC Sysadmin Team support: $num_rows</h3>";
    

    
    // $chris = fopen('/opt/coolstack/apache2/htdocs/dcp/dcpDatabase/dcpRegtool/all.txt','r') or die("can't open all.txt: $php_errormsg");
    // while($s = fgets($chris)) {
    //   $s = rtrim($s);
    //   $chris_hosts["$s"] = 1;
    // }

    if ( ($num_rows) && ($num_rows > 0) ) {
      $num = 1;
      echo "<table>\n";
      echo "<tr>";
      echo "<th>#</th> ";
      echo "<th>hostname</th>";
      echo "<th>domain</th> ";
      echo "<th>system class</th> ";
      //echo "<th>status</th> ";
      echo "<th>EDS Service Level</th> ";
      echo "<th>Platform</th>";
      echo "<th>Access Level</th>";
      echo "<th>Operation Environment</th> ";
      echo "<th>Network Access</th> <th>In Production</th> ";
      echo "<th>Division</th>  ";
      echo "</tr>\n"; 

      while ($row = $result->fetchRow(DB_FETCHMODE_ASSOC)) {

	$hostname = $row['primary_hostname'] . "." . $row['primary_domain'];

	$os = 'Solaris';
	if ( preg_match_all('/indows/i',$row['notes'], $matches) )
	  {
	    $os = 'MS-Windows';
	  }
	elseif ( preg_match_all('/nt small/i',$row['notes'], $matches) )
	  {
	    $os = 'MS-Windows';
	  }
	
	// if ( (! isset ($chris_hosts["$hostname"]) ) &&
	//      !( ($row['system_class'] == 'network_server' ) && ($row['access_level'] == 'EDS ITE' ) )
	//      )
	//   {
	    echo "<tr>";
	    echo "<td>$num</td>";
	    echo "<td>".$row['primary_hostname']."</td> ";
	    echo "<td>".$row['primary_domain']."</td>";

	$string = $num . "," . $row['primary_hostname'] . "." . $row['primary_domain'] .
	  "," . $row['system_class'] . "," . $row['access_level'] . "," .
	  $os .  "," . $row['eds_service_level'] . "," .  $row['operation_env'] . "," .
	  $row['network_access'] . "," .$row['in_production'] . "," .
	  $row['division'] . 
	  "\n";

	//$string = $row['primary_hostname'] . "." . $row['primary_domain'] . "\n";
	
	if (-1 == fwrite($fh,"$string")) { die ("can't wire data"); }
	
	echo "<td>".$row['system_class']."</td>";
	//echo "<td>".$row['system_id']."</td>";
	//echo "<td>".$row['status']."</td>";
	echo "<td>".$row['access_level'] . "</td>";
	echo "<td>$os</td>";
	echo "<td>".$row['eds_service_level'] . "</td>"; 

	echo "</td><td>".$row['operation_env']."</td>";
	echo "<td>".$row['network_access']."</td><td>".$row['in_production']."</td>";
	echo "<td>".$row['division']."</td>";
	echo "</tr>\n";
	$num++;
	//}
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