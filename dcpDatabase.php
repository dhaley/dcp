<?php

require_once "DB.php";

  // Definition of dcp base class dcpDatabase
  // base methods for common database object functionality
  //

class dcpDatabase {

  // Member variables
  var $connection;
  var $result;
  var $row;
  
  // functions

  function _initialize ($dsn) {
    $this->initdb($dsn);
    $this->populate();
  }
  
  function initdb ($dsn_string) {
    $this->connection = DB::connect($dsn_string);
    if (DB::isError($connection))
      die($connection->getMessage());
  }

  function getRow () {
    if ( isset ($this->row) ) {
      return $this->row;
    }
    else {
      return 0;
    }
  }

  
  // constructor function
  function __construct($connection) {
    $this->connection = $connection;
  }
  

  }

?>