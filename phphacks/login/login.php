<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/time';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$res = $db->query( "SELECT id FROM users WHERE name=? AND password=MD5(?)",
	array( $_POST['user'], $_POST['password'] ) );

$row = array( null );
if ( $res != null )
	$res->fetchInto( $row );

if ( $row[0] != null )
{
		session_start();
		$_SESSION['user'] = $row[0];
		header( "Location: welcome.php" );
}
else
{
		header( "Location: index.php?bad=1" );
}
?>
