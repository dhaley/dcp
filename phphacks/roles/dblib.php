<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/roles';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

function get_db() { global $db; return $db; }

function get_role_id( $role )
{
  global $db;
  $res = $db->query( "SELECT id FROM roles WHERE name=?", array( $role ) );
  if ( $res != null )
  {
    $res->fetchInto( $row );
    return $row[0];
  }
  return null;
}

function has_role( $user, $role )
{
  global $db;

  $role_id = get_role_id( $role );

  $res = $db->query( "SELECT user_id FROM user_role WHERE user_id=? AND role_id=?",
    array( $user, $role_id ) );

  if ( $res != null )
  {
    $res->fetchInto( $row );
    return ( (int)$row[0] == (int)$user ) ? true : false;
  }
  return false;
}
?>
