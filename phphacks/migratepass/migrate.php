<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/migpass';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$res = $db->query( "SELECT id, pass FROM users", array() );

$sth = $db->prepare( "UPDATE users SET pass=MD5(?) WHERE id=?" );

while( $res->fetchInto( $row ) )
{
    $db->execute( $sth, array( $row[1], $row[0] ) );
}
?>
