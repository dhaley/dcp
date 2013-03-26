<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/books';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

function selectOne( $sql, $args )
{
  global $db;
  $res = $db->query( $sql, $args );
  $res->fetchInto($row, DB_FETCHMODE_ASSOC);
  return $row;
}

function selectBlock( $sql, $args )
{
  global $db;
  $res = $db->query( $sql, $args );
  $rows = array();
  while( $res->fetchInto($row, DB_FETCHMODE_ASSOC) ) { $rows []= $row; }
  return $rows;
}

function executeCommand( $sql, $args )
{
  global $db;
  $sth = $db->prepare( $sql );
  return $db->execute( $sth, $args );
}
?>
