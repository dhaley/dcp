<?php
require_once 'PEAR.php';
require_once 'Services/Amazon.php';

$devtoken = "0T3VDGN1DDDN1EAA1S02";
$userid = "codegeneratio-20";
$amazon = &new Services_Amazon( $devtoken, $userid );

function list_products( $products )
{
?>
<table width="100%" cellspacing="0" cellpadding="3" border="0">
<?php
foreach( $products as $product ) {
?>        
<tr>
<td valign="top" width="10%" valign="middle" align="center">
<a href="<?php echo($product['url']); ?>" target="_new"><img src="<?php echo($product['imagesmall']); ?>" border="0" /></a>
</td>
<td valign="top" width="90%">
<div class="title"><a href="<?php echo($product['url']); ?>" target="_new"><?php echo( $product['name'] ); ?></a></div>
<div class="author"><?php echo($product['creator']); ?></div>
<div class="date">Release Date: <?php echo($product['release']); ?></div>
<div class="price">Price: <?php echo($product['price']); ?></div>
</td>
</tr>
<?php } ?> 
</table>
<?php
}

function find_books( $keyword  )
{
  global $amazon;

  $out = array();
  $products = $amazon->searchKeyword($keyword, "books", 1);
  if( $products != null )
  {
    foreach($products as $product)
    {
      $creator = 'by ' . implode(', ', $product['authors']);
     
      $price = '';
      if( $product['listprice'] != $product['ourprice'] )
         $price = '<strike>'.$product['listprice'].'</strike> '.$product['ourprice'];
      else
         $price = $product['listprice'];

      if ( strlen( $product['name'] ) > 0 )
        $out[ $product['asin'] ] = array(
          'url' => $product['url'],
          'imagesmall' => $product['imagesmall'],
          'name' => $product['name'],
          'release' => $product['release'],
          'manufacturer' => $product['manufacturer'],
          'asin' => $product['asin'],
          'creator' => $creator,
          'price' => $price
        );
    }
  }
  return $out;
}

$terma = isset( $_GET['terma'] ) ? $_GET['terma'] : 'mysql';
$termb = isset( $_GET['termb'] ) ? $_GET['termb'] : 'php';

$lista = find_books( $terma );
$listb = find_books( $termb );

$overlaps = array();
$onlya = array();
$onlyb = array();

foreach( array_keys( $lista ) as $asin )
{
  if ( array_key_exists( $asin, $listb ) )
    $overlaps[ $asin ] = $lista[$asin];
  else
    $onlya[ $asin ] = $lista[$asin];
}
foreach( array_keys( $listb ) as $asin )
{
  if ( !array_key_exists( $asin, $lista ) )
    $onlyb[ $asin ] = $listb[$asin];
}

?>
<html>
<head>
<title>Amazon Search Compare</title>
<style type="text/css">
th { border-bottom: 1px solid black; background: #eee; margin-bottom: 5px; font-size: small; }
td { font-size: small; }
.title { font-weight: bold; font-size: medium; }
.author { margin-left: 30px; font-style: italic; }
</style>
</head>
<body>
<form>
<div style="width:600px;">

<table width="100%" cellspacing="0" cellpadding="0" border="0">
<tr><th width="50%"><input type="text" name="terma" value="<?php echo( $terma ); ?>" /></th>
<th width="50%"><input type="text" name="termb" value="<?php echo( $termb ); ?>" /><input type="submit" value="Go" /></th></tr>
</table>

<table width="100%" cellspacing="0" cellpadding="0" border="0">
<tr><td><?php list_products( array_values( $overlaps ) ); ?></td></tr>
</table>

<table width="100%" cellspacing="0" cellpadding="0" border="0">
<tr><td valign="top" width="50%"><?php list_products( array_values( $onlya ) ); ?></td>
<td valign="top" width="50%"><?php list_products( array_values( $onlyb ) ); ?></td></tr>
</table>

</div>
</form>
</body>
</html>
