<?php
require_once( "db.php" );
$db =& DB::connect("mysql://root@localhost/media", array());
if (PEAR::isError($db)) { die($db->getMessage()); }

$res = $db->query( "SELECT filename, mime_type FROM media WHERE id = ?", array( $_GET['id'] ) );
$res->fetchInto($row);
$filename = $row[0];
$type = $row[1];

$datafile = "media/".$_GET['id'].".dat";

header( "Content-type: $type" );
header( "Content-Length: ".@filesize( $datafile ) );
header( 'Content-Disposition: attachment; filename="'.$filename.'"' );

readfile(  $datafile);
?>
