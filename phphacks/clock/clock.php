<?php
$bit_names = array( 1, 2, 4, 8, 10, 20 );
$bit_masks = array(
  array( '0', '0x1', '1' ),
  array( '1', '0x2', '2' ),
  array( '2', '0x4', '4' ),
  array( '3', '0x8', '8' ),
  array( '4', '0x10', '16' ),
  array( '5', '0x20', '32' )
);

$size = 40;

function bit_table( $name )
{
  global $size;
?>
<table width="<?php echo($size*2); ?>" cellspacing="2" cellpadding="0">
<tr>
<td id="<?php echo( $name ); ?>_1" width="<?php echo($size); ?>" height="<?php echo($size); ?>" /></td>
<td id="<?php echo( $name ); ?>_2" width="<?php echo($size); ?>" height="<?php echo($size); ?>" /></td>
</tr>
<tr>
<td id="<?php echo( $name ); ?>_4" width="<?php echo($size); ?>" height="<?php echo($size); ?>" /></td>
<td id="<?php echo( $name ); ?>_8" width="<?php echo($size); ?>" height="<?php echo($size); ?>" /></td>
</tr>
<tr>
<td id="<?php echo( $name ); ?>_10" width="<?php echo($size); ?>" height="<?php echo($size); ?>" /></td>
<td id="<?php echo( $name ); ?>_20" width="<?php echo($size); ?>" height="<?php echo($size); ?>" /></td>
</tr>
</table>
<?php
}
?>
<html>
<head>
<script>
var second_bits = [];
var minute_bits = [];
var hour_bits = [];

function startup()
{
<?php foreach( $bit_names as $name ) { ?>
  second_bits.push( document.getElementById( "second_<?php echo( $name ) ?>" ) );
  minute_bits.push( document.getElementById( "minute_<?php echo( $name ) ?>" ) );
  hour_bits.push( document.getElementById( "hour_<?php echo( $name ) ?>" ) );
<?php } ?>

  set_clock();

  window.setInterval( "set_clock()", 200 );
}

function set_state( obj, val, on_color )
{
  obj.style.background = val ? on_color : "white";
}

function set_clock()
{
  var now = new Date();
  var seconds = now.getSeconds();
  var minutes = now.getMinutes();
  var hours = now.getHours();

<?php foreach( $bit_masks as $mask ) { ?>
  set_state( second_bits[<?php echo($mask[0] ); ?>], ( ( seconds & <?php echo($mask[1] ); ?> ) == <?php echo($mask[2] ); ?> ), "red" );
  set_state( minute_bits[<?php echo($mask[0] ); ?>], ( ( minutes & <?php echo($mask[1] ); ?> ) == <?php echo($mask[2] ); ?> ), "green" );
  set_state( hour_bits[<?php echo($mask[0] ); ?>], ( ( hours & <?php echo($mask[1] ); ?> ) == <?php echo($mask[2] ); ?> ), "blue" );
<?php } ?>
}
</script>
</head>
<body onload="startup();">
<table cellpadding="5" cellspacing="0">
<tr><td>
<?php bit_table( "second" ); ?>
</td><td>
<?php bit_table( "minute" ); ?>
</td><td>
<?php bit_table( "hour" ); ?>
</td></tr></table>
</body>
</html>
