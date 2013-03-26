<?php
require_once( "mydb.php" );

$auth = new Author();
$auth->set_name( "Jack" );
$auth->update();
?>
