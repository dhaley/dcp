<?php
require_once( "dblib.php" );
session_start();
?>
<html>
<head>
<title>Your Cart</title>
<script language="Javascript">
function submit_delete()
{
	document.getElementById( "delform" ).submit();
	return null;
}
</script>
<style type="text/css">
h1 { border-bottom: 1px solid black; font-size: medium; margin-bottom: 10px; }
</style>
</head>
<body>
<?php
if ( isset( $_SESSION['cart'] ) && count( $_SESSION['cart'] ) > 0 ) {
?>
<!-- CART : <?php echo( join( ",", array_keys( $_SESSION['cart'] ) ) ); ?> -->
<form id="delform" action="delete.php" method="post">
<table width="600">
<tr>
<th width="3%"></th>
<th width="77%">Product</th>
<th width="20%">Price</th>
</tr>
<?php
foreach( array_keys( $_SESSION['cart'] ) as $product )
{
	$prod = product_info( $product );
?>
<tr>
<td><input type="checkbox" name="ids[]" value="<?php echo( $product ); ?>" /></td>
<td><?php echo( $prod['name'] ); ?></td>
<td align="right"><?php echo( $prod['price'] ); ?></td>
</tr>
<?php } ?>
<tr>
<td></td>
<td align="center"><a href="javascript:submit_delete()">Delete checked items</a>
&nbsp; &nbsp; &nbsp; &nbsp;
<a href="index.php">Return to store</a>
&nbsp; &nbsp; &nbsp; &nbsp;
<a href="buy.php">Buy these items</a>
</tr>
</table>
</form>
<?php } else { ?>
You should go and <a href="index.php">buy some stuff</a>.
<?php } ?>
</body>
</html>
