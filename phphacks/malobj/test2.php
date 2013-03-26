<?php
require_once( "DBrecord2.php" );

$rec = new DBRecord( "author", 2 );
print $rec->Name()."\n";
$rec->Name = "New Name";
$rec->Update();
?>
