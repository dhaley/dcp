<?php

require_once "dcpDatabase.php";
require_once 'dcpDataObjects/Server_frmware_disks.php';
require_once 'dcpDataObjects/Server_frmware_hba.php';

// Definition of dcpDatabase::dcpSun_server
// methods will get, set and retrieve sun_server object data
//


  // This class is for Re-creating sun_server objects from Regtool Values
  //
  //

class dcpSun_Server extends dcpDatabase {
  // Member variables

  private $System_id, $Status, $Hostname, $Serial_number, $Location_name, $Hostid, $Eds_service_level, $System_model_name, $Op_Env, $Network, $Production_status, $Division;

  // functions

  function getRegToolProdStatus () 
  {
    return $this->Production_status;
  }
  
  function getHostname () {
    return $this->Hostname;
  }

  function getSysId () {
    return $this->System_id;
  }

  function getSystemModelName () 
  {
    return $this->System_model_name;
  }

  function getLocationName () 
  {
    return $this->Location_name;
  }

  function getNetwrkIsrName ()
  {
    return $this->Network;
  }

  function getSlevelName ()
  {
    return $this->Eds_service_level;

  }

  function getOpEnvName ()
  {
    return $this->Op_Env;
  }
  
  function populateObject ($sysid)
  {
    $this->System_id = $sysid;

  }

  public function setFrmware_obp_id ($frmware_obp_id) 
  {
    $sysid = $this->getSysId();
    $stmt = "UPDATE sun_server SET frmware_obp_id = '$frmware_obp_id' WHERE sysid = '$sysid'";

    $result = $this->connection->query($stmt);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
  }

  public function setFrmware_alom_id ($frmware_alom_id)
  {
    $sysid = $this->getSysId();
    $stmt = "UPDATE sun_server SET frmware_alom_id = '$frmware_alom_id' WHERE sysid = '$sysid'";
    $result = $this->connection->query($stmt);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
  }

  public function setFrmware_hypervisor_id ($frmware_hypervisor_id)
  {
    $sysid = $this->getSysId();
    $stmt = "UPDATE sun_server SET frmware_hypervisor_id = '$frmware_hypervisor_id' WHERE sysid = '$sysid'";
    $result = $this->connection->query($stmt);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
  }

  public function setFrmware_hba_id ($frmware_hba_id)
  {
    $sysid = $this->getSysId();
    $server_hba = new dcpDataObjects_Server_frmware_hba;
    $server_hba->sysid = "$sysid";
    $hba_number_of_rows = $server_hba->find();
    while ($server_hba->fetch()) {
      $server_hba->delete();
    }
    foreach ($frmware_hba_id as $value) 
      {
	$server_hba = new dcpDataObjects_Server_frmware_hba;
	$server_hba->sysid = "$sysid";
	$server_hba->frmware_hba_id = "$value";
	$id = $server_hba->insert();
      }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public function setFrmware_disks_id ($frmware_disks_id)
  {
    $sysid = $this->getSysId();
    $server_disk = new dcpDataObjects_Server_frmware_disks;
    $server_disk->sysid = "$sysid";
    $number_of_rows = $server_disk->find();
    while ($server_disk->fetch()) {
      $server_disk->delete();
    }
    foreach ($frmware_disks_id as $value) 
      {
	$server_disk = new dcpDataObjects_Server_frmware_disks;
	$server_disk->sysid = "$sysid";
	$server_disk->frmware_disks_id = "$value";
	$id = $server_disk->insert();
      }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public function setOs_instance_id ($os_instance_id)
  {
    $sysid = $this->getSysId();    
    $stmt = "UPDATE sun_server SET os_instance_id = '$os_instance_id' WHERE sysid = '$sysid'";
    $result = $this->connection->query($stmt);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
  }


  public function setConsole_id ($console_id)
  {
    $sysid = $this->getSysId();    
    $stmt = "UPDATE sun_server SET console_id = '$console_id' WHERE sysid = '$sysid'";
    $result = $this->connection->query($stmt);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
  }

  
  // constructor function
  function __construct($connection,$sysid) {
    $this->connection = $connection;
    $this->System_id = $sysid;
  }

  
  }

?>