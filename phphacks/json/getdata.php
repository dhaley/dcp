<?php
require( 'JSON.php' );

$records = array();
$records []= array( 'id' => 1, 'last' => 'Herrington', 'first' => 'Jack' );
$records []= array( 'id' => 2, 'last' => 'Herrington', 'first' => 'Megan' );
$records []= array( 'id' => 3, 'last' => 'Herrington', 'first' => 'Lori' );

$json = new JSON();
echo( $json->encode( $records ) );
?>
