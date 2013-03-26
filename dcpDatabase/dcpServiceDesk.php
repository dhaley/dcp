<?php

require_once "dcpDatabase.php";
// Definition of dcp class dcpServiceDesk
// methods will get, set and retrieve ServiceDesk data
//

class dcpServiceDesk extends dcpDatabase {
  // Member variables
  var $sdesk_num;

  // functions
  function populate () {

    //select datediff(second, '1970-01-01 00:00:00',submit_time) from Request where request_id = 6312985    
    $SQL = "SELECT DISTINCT Request.login, datediff(second, '1970-01-01 00:00:00', Request.submit_time), datediff(second, '1970-01-01 00:00:00', Request.close_time), Request.usr_sunid, ";
    $SQL .= " usr_nm = (Request.usr_firstnm + ' ' + Request.usr_lastnm), Request.usr_dept, Request.priority, ";
    $SQL .= " Request.new_priority, Request.status, Request.short_desc ";
    $SQL .= " FROM Request ";
    $SQL .= " WHERE Request.request_id = " . $this->sdesk_num;


    $result = $this->connection->query($SQL);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
 
    $num_rows = $result->numRows();

    if ( ($num_rows) && ($num_rows > 0) ) {
      //$this->row = $result->fetchRow(DB_FETCHMODE_ASSOC);
      $this->row = $result->fetchRow();      
    }

  }

  // constructor function
  function __construct($sdesk_num) {
    $this->sdesk_num = $sdesk_num;
    require_once "servicedesk_db.inc";
    $this->_initialize($dsn);
  }
  
  }

?>