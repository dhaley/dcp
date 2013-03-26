<?php
require_once("DB.php");

$dsn = 'mysql://root:password@localhost/books';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$sth = $db->prepare( "INSERT INTO author VALUES ( null, ? )" );
$db->execute( $sth, array( $_POST['name'] ) );
?>
