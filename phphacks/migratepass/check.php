<?php
require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/migpass';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$user = "jack";
$pass = "toronto";

$res = $db->query( "SELECT id, name FROM users WHERE name=? AND pass=MD5(?)",
    array( $user, $pass ) );

while( $res->fetchInto( $row ) )
{
    print( $row[0]." - ".$row[1]."\n" );
}
?>
