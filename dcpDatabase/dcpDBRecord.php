<?php

class dcpDBRecord extends dcpDatabase
{
  var $h;
  var $table;
  var $sdesk_num;

  public function dcpDBRecord( $connection, $table, $sdesk_num )
  {
    $this->connection = $connection;

    $SQL = "SELECT * from $table WHERE sdesk_num = '$sdesk_num' ";
    
    $result =& $this->connection->query($SQL);
    if (PEAR::isError($result)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $result->getMessage() . "<br>\n";
      die("A more detailed error description: " . $result->getDebugInfo() . "<br>\n");
    }
    $num_rows = $result->numRows();


    if ( $num_rows == 0)
      {
	error_log("num rows is $num_rows for $table");	
	$sth = $this->connection->prepare("INSERT INTO $table (sdesk_num) VALUES (?)");
	if (PEAR::isError($sth)) {
	  die($sth->getMessage());
	}
	$data = array($sdesk_num);
	$result2 =& $this->connection->execute($sth, $data);
	if (PEAR::isError($res)) {
	  die($result2->getMessage());
	}
      }

    $res =& $this->connection->query($SQL);
    if (PEAR::isError($res)) {
      echo "An error occurred while trying to run your query.<br>\n";
      echo "Error message: " . $res->getMessage() . "<br>\n";
      die("A more detailed error description: " . $res->getDebugInfo() . "<br>\n");
    }
    $res->fetchInto( $row, DB_FETCHMODE_ASSOC );

    
    $this->{'h'} = $row;
    $this->{'table'} = $table;
    $this->{'sdesk_num'} = $sdesk_num;
  }
  
  public function __call( $method, $args )
  {
    return $this->{'h'}[strtolower($method)];
  }

  public function __get( $sdesk_num )
  {
      print "Getting $sdesk_num\n";
    return $this->{'h'}[strtolower($sdesk_num)];
  }

  public function __set( $sdesk_num, $value )
  {
    $this->{'h'}[strtolower($sdesk_num)] = $value;
  }

  public function Update()
  {
    $fields = array();
    $values = array();

    foreach( array_keys( $this->{'h'} ) as $key )
    {
      if ( $key != "sdesk_num" )
      {
        $fields []= $key." = ?";
        $values []= $this->{'h'}[$key];
      }
    }
    $fields = join( ",", $fields );
    $values []= $this->{'sdesk_num'};

    $sql = "UPDATE {$this->{'table'}} SET $fields WHERE sdesk_num = ?";
    $sth = $this->connection->prepare( $sql );
    $this->connection->execute( $sth, $values );
  }

}
?>
