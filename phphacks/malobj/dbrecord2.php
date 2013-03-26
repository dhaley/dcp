<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/books';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

class DBRecord
{
  var $h;
  var $table;
  var $id;

  public function DBRecord( $table, $id )
  {
      global $db;
      $res = $db->query( "SELECT * from $table WHERE id=?", array( $id ) );
      $res->fetchInto( $row, DB_FETCHMODE_ASSOC );
    $this->{'h'} = $row;
    $this->{'table'} = $table;
    $this->{'id'} = $id;
  }
  
  public function __call( $method, $args )
  {
    return $this->{'h'}[strtolower($method)];
  }

  public function __get( $id )
  {
      print "Getting $id\n";
    return $this->{'h'}[strtolower($id)];
  }

  public function __set( $id, $value )
  {
    $this->{'h'}[strtolower($id)] = $value;
  }

  public function Update()
  {
    global $db;

    $fields = array();
    $values = array();

    foreach( array_keys( $this->{'h'} ) as $key )
    {
      if ( $key != "id" )
      {
        $fields []= $key." = ?";
        $values []= $this->{'h'}[$key];
      }
    }
    $fields = join( ",", $fields );
    $values []= $this->{'id'};

    $sql = "UPDATE {$this->{'table'}} SET $fields WHERE id = ?";
    $sth = $db->prepare( $sql );
    $db->execute( $sth, $values );
  }
}
?>
