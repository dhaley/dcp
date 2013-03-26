<?php

// Definition of dcpDatabase::dcpSun_server
// methods will get, set and retrieve sun_server object data
//


  // This class is for Re-creating sun_server objects from Regtool Values
  //
  //

class dcpSun_ServerFromRegtool extends dcpDatabase {
  // Member variables

  private $System_id, $Status, $Hostname, $Serial_number, $Location_name, $Hostid, $Eds_service_level, $System_model_name, $Op_Env, $Network, $Production_status, $Division;

  // functions

  function getRegToolProdStatus () 
  {
    return $this->Production_status;
  }
  
  function getHostnamebyRegtool ($primary_hostname,$primary_domain) {
    return "$primary_hostname" . "." . "$primary_domain";
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
  
  
  function getModelID () 
  {
    $System_model_name = $this->getSystemModelName();    
    $result = $this->connection->query("SELECT model_id FROM model WHERE model_name = '$System_model_name' ");

    if (PEAR::isError($result)) {
      die($result->getMessage());
    }
    $model_num_rows = $result->numRows();
    if ($model_num_rows == 0)
      {
	$model_id = $this->connection->nextId("model_id");
	$sth = $this->connection->prepare('INSERT INTO model (model_id,model_name) VALUES (?,?)');
 	if (PEAR::isError($sth)) {
 	  die($sth->getMessage());
 	}
	$data = array($model_id,$System_model_name);
 	$res =& $this->connection->execute($sth, $data);
	if (PEAR::isError($res)) {
	  die($res->getMessage());
	}
	return $model_id;
      }
    else {
      $row = $result->fetchRow(DB_FETCHMODE_ASSOC);
      $model_id = $row['model_id'];
      return $model_id;
    }
  }


  function getLocationID () 
  {
    $location_name = $this->getLocationName();

    $result = $this->connection->query("SELECT location_id FROM location WHERE location_name = '$location_name' ");

    if (PEAR::isError($result)) {
      die($result->getMessage());
    }
    $location_num_rows = $result->numRows();
    if ($location_num_rows == 0)
      {
	$location_id = $this->connection->nextId("location_id");
	$sth = $this->connection->prepare('INSERT INTO location (location_id,location_name) VALUES (?,?)');
 	if (PEAR::isError($sth)) {
 	  die($sth->getMessage());
 	}
	$data = array($location_id,$location_name);
 	$res =& $this->connection->execute($sth, $data);
	if (PEAR::isError($res)) {
	  die($res->getMessage());
	}
	return $location_id;
      }
    else {
      $row = $result->fetchRow(DB_FETCHMODE_ASSOC);
      $location_id = $row['location_id'];
      return $location_id;
    }
  }


  function getnetwrkIsrID () 
  {
    $netwrk_isr_name = $this->getNetwrkIsrName();

    $result = $this->connection->query("SELECT netwrk_isr_id FROM netwrk_isr WHERE netwrk_isr_name = '$netwrk_isr_name' ");

    if (PEAR::isError($result)) {
      die($result->getMessage());
    }
    $netwrk_isr_num_rows = $result->numRows();
    if ($netwrk_isr_num_rows == 0)
      {
	$netwrk_isr_id = $this->connection->nextId("netwrk_isr_id");
	$sth = $this->connection->prepare('INSERT INTO netwrk_isr (netwrk_isr_id,netwrk_isr_name) VALUES (?,?)');
 	if (PEAR::isError($sth)) {
 	  die($sth->getMessage());
 	}
	$data = array($netwrk_isr_id,$netwrk_isr_name);
 	$res =& $this->connection->execute($sth, $data);
	if (PEAR::isError($res)) {
	  die($res->getMessage());
	}
	return $netwrk_isr_id;
      }
    else {
      $row = $result->fetchRow(DB_FETCHMODE_ASSOC);
      $netwrk_isr_id = $row['netwrk_isr_id'];
      return $netwrk_isr_id;
    }
  }

  function getslevelID () 
  {
    $slevel_name = $this->getSlevelName();

    $result = $this->connection->query("SELECT slevel_id FROM slevel WHERE slevel_name = '$slevel_name' ");

    if (PEAR::isError($result)) {
      die($result->getMessage());
    }
    $slevel_num_rows = $result->numRows();
    if ($slevel_num_rows == 0)
      {
	$slevel_id = $this->connection->nextId("slevel_id");
	$sth = $this->connection->prepare('INSERT INTO slevel (slevel_id,slevel_name) VALUES (?,?)');
 	if (PEAR::isError($sth)) {
 	  die($sth->getMessage());
 	}
	$data = array($slevel_id,$slevel_name);
 	$res =& $this->connection->execute($sth, $data);
	if (PEAR::isError($res)) {
	  die($res->getMessage());
	}
	return $slevel_id;
      }
    else {
      $row = $result->fetchRow(DB_FETCHMODE_ASSOC);
      $slevel_id = $row['slevel_id'];
      return $slevel_id;
    }
  }

  function getOpEnvID () 
  {
    $op_env_name = $this->getOpEnvName();

    $result = $this->connection->query("SELECT op_env_id FROM op_env WHERE op_env_name = '$op_env_name' ");

    if (PEAR::isError($result)) {
      die($result->getMessage());
    }
    $op_env_num_rows = $result->numRows();
    if ($op_env_num_rows == 0)
      {
	$op_env_id = $this->connection->nextId("op_env_id");
	$sth = $this->connection->prepare('INSERT INTO op_env (op_env_id,op_env_name) VALUES (?,?)');
 	if (PEAR::isError($sth)) {
 	  die($sth->getMessage());
 	}
	$data = array($op_env_id,$op_env_name);
 	$res =& $this->connection->execute($sth, $data);
	if (PEAR::isError($res)) {
	  die($res->getMessage());
	}
	return $op_env_id;
      }
    else {
      $row = $result->fetchRow(DB_FETCHMODE_ASSOC);
      $op_env_id = $row['op_env_id'];
      return $op_env_id;
    }
  }
  
  function insertFromRegtool () {
    $System_id = $this->getSysId();
    $model_id = $this->getModelID();
    $location_id = $this->getLocationID();
    $netwrk_isr_id = $this->getnetwrkIsrID();
    $slevel_id = $this->getslevelID();
    $op_env_id = $this->getOpEnvID();
    $regtool_prod_status = $this->getRegToolProdStatus();

    $result = $this->connection->query("SELECT * FROM sun_server where sysid = $System_id");
    if (PEAR::isError($result)) {
      die($result->getMessage());
    }
    $num_rows = $result->numRows(); // save for later

    if ($num_rows == 0)
       {
	 error_log("new row from Regtool");
 	$sth = $this->connection->prepare('INSERT INTO sun_server (sysid, hostname, status, hostid, serial_number, division, model_id, location_id, netwrk_isr_id, slevel_id, op_env_id, regtool_prod_status) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)');

 	if (PEAR::isError($sth)) {
 	  die($sth->getMessage());
 	}
	$data = array($System_id, $this->Hostname, $this->Status, $this->Hostid, $this->Serial_number, $this->Division, $model_id, $location_id, $netwrk_isr_id, $slevel_id, $op_env_id, $regtool_prod_status);
 	$res =& $this->connection->execute($sth, $data);
	
 	if (PEAR::isError($res)) {
	  error_log($res->getMessage());
 	  die($res->getMessage());
 	}
       }
    else 
       {
 	// We need to update table
	 error_log("UPDATE row from Regtool");
	 $stmt = "UPDATE sun_server SET hostname = '$this->Hostname', status = '$this->Status', hostid = '$this->Hostid', serial_number = '$this->Serial_number', division = '$this->Division', model_id = '$model_id', location_id = '$location_id', netwrk_isr_id = '$netwrk_isr_id', slevel_id = '$slevel_id', op_env_id = '$op_env_id', regtool_prod_status = '$regtool_prod_status' WHERE sysid = '$System_id'";

	 $result = $this->connection->query($stmt);
	 if (PEAR::isError($result)) {
	   echo "An error occurred while trying to run your query.<br>\n";
	   echo "Error message: " . $result->getMessage() . "<br>\n";
	   die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
	 }
       }
  }

  function populateRegTool ($row) {
    list ($this->System_id,  $this->Status, $Primary_hostname, $Primary_domain, $this->Serial_number, $this->Location_name, $this->Hostid, $this->Eds_service_level, $this->System_model_name, $this->Op_Env, $this->Network, $this->Production_status, $this->Division) = $row;
      
    $this->Hostname = $this->getHostnamebyRegtool($Primary_hostname, $Primary_domain);

  }

  }

?>