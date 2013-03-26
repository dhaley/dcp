<?php

class dcpProcedureVerificationFromServiceDesk extends dcpDatabase {

  // Member variables
  private $login, $submit_time, $close_time, $usr_sunid, $usr_nm, $usr_dept, $priority;
  private $new_priority, $request_status, $short_desc;
  var $sdesk_num;

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

  // constructor function
  function __construct($connection,$sdesk_num) {
    $this->connection = $connection;
    $this->sdesk_num = $sdesk_num;    
  }
  

  }  

?>