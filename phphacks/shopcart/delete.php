<?php
session_start();

foreach( $_POST['ids'] as $did )
	unset( $_SESSION['cart'][$did] );

header( "location: checkout.php" );
?>
