<?php

class dcpSun_ServerOsSelections
{

  // Member variables
  private $contents = array();

  
  public function dcpSun_ServerOsSelections ( $connection )
  {
    $this->connection = $connection;
    $res = $this->connection->query( "SELECT * FROM os_choices" );

    while ($row =& $res->fetchRow() ) 
       {
	 $id = array_shift($row);
	 $name = implode(' ', $row);
	 $this->contents[$id] = $name;
       }
  }
  
  public function getContents ()
  {
    return $this->contents;
  }

}