<?php
require_once("DB.php");

$dsn = 'mysql://root:password@localhost/books';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$res = $db->query( "SELECT * FROM author WHERE id = ?", array( $id ) );
while( $res->fetchInto( $row ) )
{
	...
}
?>
