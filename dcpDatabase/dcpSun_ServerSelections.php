<?php

class dcpSun_ServerSelections
{

  // Member variables
  private $contents = array();

  
  public function dcpSun_ServerSelections ( $connection, $table_name )
  {
    $this->connection = $connection;
    $res = $this->connection->query( "SELECT * FROM $table_name" );

    //    while ($res->fetchInto($row, DB_FETCHMODE_ASSOC)) {
    //      array_push( $this->contents, $row );
    //    }

    while ($row =& $res->fetchRow() ) 
       {
	 $id = $row[0];
	 $name = $row[1];
	 $this->contents[$id] = $name;
       }
  }
  
  public function getContents ()
  {
    return $this->contents;
  }

}