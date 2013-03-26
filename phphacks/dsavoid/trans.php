<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/transtest';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) {
   die($db->getMessage());
}

function check_transid( $id )
{
  global $db;
  $res = $db->query( "SELECT COUNT(transid) FROM transcheck WHERE transid=?",
    array($id) );
  $res->fetchInto($row);
  return $row[0];
}

function add_transid( $id ) 
{
  global $db;
  $sth = $db->prepare( "INSERT INTO transcheck VALUES( ?, now() )" );
  $db->execute( $sth, array( $id ) );
}

function get_transid()
{
  $id = mt_rand();
  while( check_transid( $id ) ) { $id = mt_rand(); }
  return $id;
}
?>
