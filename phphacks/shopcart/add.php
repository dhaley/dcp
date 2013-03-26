<?php
session_start();
if ( !isset( $_SESSION['cart'] ) )
	$_SESSION['cart'] = array();
$_SESSION['cart'][$_POST['prod_id']] = 1;
header( "location: index.php" );
?>
