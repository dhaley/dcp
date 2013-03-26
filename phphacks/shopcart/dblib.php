<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/shopcart';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

function get_db() { global $db; return $db; }

function get_products( )
{
  global $db;
  $res = $db->query( "SELECT * FROM product", array( ) );
  $out = array();
  if ( $res != null )
    while( $res->fetchInto( $row, DB_FETCHMODE_ASSOC ) ) { $out []= $row; }
  return $out;
}

function product_info( $id )
{
  global $db;

  $res = $db->query( "SELECT * FROM product WHERE id=?",
    array( $id ) );

  if ( $res != null )
  {
    $res->fetchInto( $row, DB_FETCHMODE_ASSOC );
    return $row;
  }
  return null;
}
?>
