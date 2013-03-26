<?php
require_once( "db.php" );
$db =& DB::connect("mysql://root@localhost/media", array());
if (PEAR::isError($db)) { die($db->getMessage()); }

if ( $_FILES['file']['tmp_name'] )
{
	$sth = $db->prepare( "INSERT INTO media VALUES ( 0, ?, ? )" );
	$db->execute( $sth, array( $_FILES['file']['name'], $_FILES['file']['type'] ) );

	$res = $db->query( "SELECT last_insert_id()" );
	$res->fetchInto( $row );

	$newid = $row[0];

	move_uploaded_file( $_FILES['file']['tmp_name'], "media/".$newid.".dat" );
}

header( "location: dir.php" );
?>
