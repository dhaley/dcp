<? require_once( "trans.php" ); ?>
<html>
<body>
<?php if ( check_transid( $_POST["transid"] ) ) { ?>
This form has already been submitted.
<?php } else {
add_transid( $_POST["transid"] );
?>
Ok, you bought our marvelous product. Thanks!
<?php } ?>
</body>
</html>
