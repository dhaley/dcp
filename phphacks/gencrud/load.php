<?php
require_once( "mydb.php" );

$auth = new Author();
$auth->load( 1 );
?>
Name: <?php echo( $auth->get_name() ); ?>
