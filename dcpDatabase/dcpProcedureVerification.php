<?php

// Definition of dcpDatabase::dcpProcedureVerification
// methods will get, set and retrieve dcp_procedure_verification object data
//

class dcpProcedureVerification extends dcpDatabase {
  // Member variables
  private $login, $submit_time, $close_time, $usr_sunid, $usr_nm, $usr_dept, $priority;
  private $new_priority, $request_status, $short_desc;
  var $sdesk_num;
  //  var $sysid;

  var $full_optional_tables_labels = array('dcp_procedure_verification_eeprom' => 'eeprom Modifications required', 'dcp_procedure_verification_svm' => 'svm utilized', 'dcp_procedure_verification_zfs' => 'zfs employed', 'dcp_procedure_verification_clt' => 'host in CLT', 'dcp_procedure_verification_san' => 'host san attached', 'dcp_procedure_verification_cluster' => 'cluster enabled', 'dcp_procedure_verification_x86' => 'x86 architecture', 'dcp_procedure_verification_offswan' => 'located OffSwan', 'dcp_procedure_verification_onswan' => 'located OnSwan', 'dcp_procedure_verification_vlan' => 'vlan utilized');

  var $full_optional_tables = array(
				    'dcp_procedure_verification_eeprom' => array('mirror_boot_disk_defined' => 'Mirror boot disk defined', 'auto_boot_on_error' => 'eeprom Auto boot on error', 'auto_boot' => 'eeprom Auto boot'),
				    'dcp_procedure_verification_svm' => array('metadb_defined_on_two_disks' => 'metadb defined on 2 disks', 'boot_from_mirror_enabled' => 'Boot from mirror enabled', 'lvm_md_tab_updated' => 'lvm mdtab updated'),
				    'dcp_procedure_verification_zfs' => array('boot_zpool' => 'Boot zpool'),
				    'dcp_procedure_verification_clt' => array('cam_sheet_sent' => 'CAM sheet set', 'cam_sheet_sent_date' => 'CAM sheet sent date'),
				    'dcp_procedure_verification_san' => array('san_cr_num' => 'San Change Control Num #', 'san_switch_port_requested_date' => 'San switch port requsted date', 'san_connected_date' => 'San connected date'),
				    'dcp_procedure_verification_cluster' => array('cluster_eis_certified' => 'Cluster EIS certified'),
				    'dcp_procedure_verification_x86' => array('fdisk_label_x86' => 'Fdisk label'),
				    'dcp_procedure_verification_offswan' => array('moved_off_swan' => 'Moved off SWAN', 'autofs_disabled' => 'Autofs Disabled'),
				    'dcp_procedure_verification_onswan' => array('autofs_enabled' => 'Autofs enabled', 'throughput_rate_verified' => 'Throughput rate verified')					  
				    );

  // functions

  function getLogin () 
  {
    return $this->login;
  }


  function getSubmitTime () 
  {
    $mysqltime = gmdate ("Y-m-d H:i:s", $this->submit_time);
    return $mysqltime;
  }

  function getCloseTime ()
  {
    if (preg_match ('/[\S]+/', $this->close_time) )
      {
	$mysqltime = gmdate ("Y-m-d H:i:s", $this->close_time);
	return $mysqltime;
      }
    else 
      {
	return 0;
      }
  }

  function getUserSunid () 
  {
    return $this->usr_sunid;
  }

  function getUserName () 
  {
    $this->usr_nm;
    $upper_usr_nm = ucwords($this->usr_nm);
    return $upper_usr_nm;
  }

  function getUserDept () 
  {
    return $this->usr_dept;
  }

  function getPriority () 
  {
    return $this->priority;
  }

    function getNewPriority () 
  {
    return $this->new_priority;
  }

    function getRequestStatus () 
  {
    return $this->request_status;
  }

    function getShortDesk () 
  {
    return $this->short_desc;
  }

  function insertFromServiceDesk () {
    $login = $this->getLogin();
    $submit_time = $this->getSubmitTime();
    $close_time = $this->getCloseTime();
    $usr_sunid = $this->getUserSunid();
    $usr_nm = $this->getUserName();
    $usr_dept = $this->getUserDept();
    $priority = $this->getPriority();
    $new_priority = $this->getNewPriority();
    $request_status = $this->getRequestStatus();
    $short_desc = $this->getShortDesk();

    $result = $this->connection->query("SELECT * FROM dcp_procedure_verification where sdesk_num = $this->sdesk_num");
    if (PEAR::isError($result)) {
      die($result->getMessage());
    }
    $num_rows = $result->numRows(); // save for later

    if ($num_rows == 0)
       {

  	$sth = $this->connection->prepare('INSERT INTO dcp_procedure_verification (sdesk_num, login, submit_time, close_time, usr_sunid, usr_nm, usr_dept, priority, new_priority, request_status, short_desc) VALUES (?,?,?,?,?,?,?,?,?,?,?)');

  	if (PEAR::isError($sth)) {
  	  die($sth->getMessage());
  	}
  	$data = array($this->sdesk_num, $login, $submit_time, $close_time, $usr_sunid, $usr_nm, $usr_dept, $priority, $new_priority, $request_status, $short_desc);
  	$res =& $this->connection->execute($sth, $data);
	
  	if (PEAR::isError($res)) {
  	  die($res->getMessage());
  	}
       }
    else 
       {
  	// We need to update table
  	 $stmt = "UPDATE dcp_procedure_verification SET login = '$login', submit_time = '$submit_time', close_time = '$close_time', usr_sunid = '$usr_sunid', usr_nm = '$usr_nm', usr_dept = '$usr_dept', priority = '$priority', new_priority = '$new_priority', request_status = '$request_status', short_desc = '$short_desc' where sdesk_num = '$this->sdesk_num' ";

  	 $result = $this->connection->query($stmt);
  	 if (PEAR::isError($result)) {
  	   echo "An error occurred while trying to run your query.<br>\n";
  	   echo "Error message: " . $result->getMessage() . "<br>\n";
  	   die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
  	 }
       }
  }

  function populateServiceDesk ($row) {
    list ($this->login, $this->submit_time, $this->close_time, $this->usr_sunid, $this->usr_nm, $this->usr_dept, $this->priority, $this->new_priority, $this->request_status, $this->short_desc) = $row;
  }


  function linkRegToolHost ($sysid) 
  {
    $stmt = "UPDATE dcp_procedure_verification SET sysid = '$sysid' WHERE sdesk_num = '$this->sdesk_num' ; ";
    $result = $this->connection->query($stmt);
    if (PEAR::isError($result)) {
      error_log("An error occurred while trying to run your query.<br>\n");
      error_log("Error message: " . $result->getMessage() . "<br>\n");
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
  }
  

  function getOptionalTables () 
  {
    $optional_tables_valid = array();
    foreach ($this->full_optional_tables as $table => $array)
      {
	$result = $this->connection->query( "SELECT * FROM $table where sdesk_num = '$this->sdesk_num'; " );
	if (PEAR::isError($result)) {
	  echo "An error occurred while trying to run your query.<br>\n";
	  echo "Error message: " . $result->getMessage() . "<br>\n";
	  die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
	}
	$num_rows = $result->numRows();
	if ( $num_rows == 1)
	  {
	    $optional_tables_valid[$table] = $array;
	  }
      }
    
    return $optional_tables_valid;
  }


  
//  constructor function
  function __construct($connection,$sdesk_num) {
    $this->connection = $connection;
    $this->sdesk_num = $sdesk_num;
  }


  }  

?>
