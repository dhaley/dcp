<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/migpass';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$res = $db->query( "SELECT id, name, pass FROM users", array() );

$sth = $db->prepare( "UPDATE users SET pass=MD5(?) WHERE id=?" );

while( $res->fetchInto( $row ) )
{
    print( $row[0]." - ".$row[1]." - ".$row[2]."\n" );
}
?>
