<?php
require_once( "dblib.php" );
session_start();
$products = get_products();
?>
<html>
<head>
<title>My Products</title>
</head>
<style type="text/css">
h1 { border-bottom: 1px solid black; font-size: medium; margin-bottom: 10px; }
</style>
<script>
function buy( prod_id )
{
	document.getElementById( 'prod_id' ).value = prod_id;
	document.getElementById( 'buyform' ).submit();
	return null;
}
</script>
<body>
<form id="buyform" action="add.php" method="post">
<input type="hidden" name="prod_id" id="prod_id" value="" />
</form>
<table width="600" border="0" cellspacing="0" cellpadding="5">
<tr>
<td width="70%" valign="top">
<h1>Products</h1>
<table width="100%">
<?php foreach( $products as $product ) { ?>
<tr>
<td width="70%"><?php echo( $product['name'] ); ?></td>
<td width="15%" align="right">$<?php echo( $product['price'] ); ?></td>
<td width="15%" align="center"><a href="javascript:buy( <?php echo( $product['id'] ); ?> );">buy</a>
</tr>
<?php } ?>
</table>
</td>
<td width="30%" valign="top">
<h1>Shopping cart</h1>
<?php
if( isset( $_SESSION['cart'] ) ) {
?>
<!-- CART : <?php echo( join( ",", array_keys( $_SESSION['cart'] ) ) ); ?> -->
<table width="100%" cellspacing="0" cellpadding="5">
<?php
foreach( array_keys( $_SESSION['cart'] ) as $product ) {
$info = product_info( $product );
?>
<tr><td>
<?php echo( $info['name' ] ); ?>
</td></tr>
<?php } ?>
<tr><td align="center">
<a href="checkout.php">Checkout</a>
</td></tr>
</table>
<?php
}
?>
</td>
</tr>
</table>
</body>
</html>
