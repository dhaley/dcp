<?php
function hsb( $h, $s, $v )
{
  $r = $g = $b = 0;
  if ( $s == 0 ) 
  { 
    $r = $g = $b = $v;
  }
  else
  {
    $h = $h / 60;
    $i = floor( $h );
    $f = $h - $i;
    $p = $v * ( 1 - $s );
    $q = $v * ( 1 - $s * $f );
    $t = $v * ( 1 - $s * ( 1 - $f ) );
    switch( $i ) {
      case 0: $r = $v; $g = $t; $b = $p; break;
      case 1: $r = $q; $g = $v; $b = $p; break;
      case 2: $r = $p; $g = $v; $b = $t; break;
      case 3: $r = $p; $g = $q; $b = $v; break;
      case 4: $r = $t; $g = $p; $b = $v; break;
      default: $r = $v; $g = $p; $b = $q; break;
    }
  }
  return array( $r, $g, $b );
}

function hsb2hex( $h, $s, $b )
{
   list( $r, $g, $b ) = hsb( $h, $s, $b );
   return sprintf( "#%02x%02x%02x", $r, $g, $b );
}
?>
<html>
<head>
<script language="Javascript">
function mover( id )
{
  var obj = document.getElementById( id );
  obj.style.borderColor = "black";
}
function mout( id )
{
  var obj = document.getElementById( id );
  obj.style.borderColor = "white";
}
function selectColor( color )
{
  document.getElementById( "color" ).value = color;
}
function hover( color )
{
  document.getElementById( "hoverColor" ).innerHTML = color;
}
</script>
<style type="text/css">
body { font-family: arial, verdana, sans-serif; }
#color { font-family: courier; }
#hoverColor { font-family: courier; }
</style>
</head>
<body>
Color: <input id="color" type="text" size="8" />
<table cellspacing="10" cellpadding="0"><tr><td>
<table cellspacing="0" cellpadding="0">
<?php
$id = 1;
for( $h = 0; $h < 360; $h += 18 ) { ?>
<tr>
<?php for( $b = 255; $b >= 0; $b -= 10 ) {
$color = hsb2hex( $h, $b / 255, $b );
 ?>
<td>
<div id="cp<?php echo( $id ); ?>" style="height:10px; width:10px; border:1px solid white; background:<?php echo( $color ); ?>;" onmouseover="mover('cp<?php echo( $id ); ?>');hover('<?php echo( $color ); ?>');" onmouseout="mout('cp<?php echo( $id ); ?>')" onclick="selectColor('<?php echo( $color ); ?>');"></div>
</td>
<?php
$id += 1;
} ?>
</tr>
<?php } ?>
</table>
</td><td valign="top">
<div id="hoverColor"></div>
</td></tr></table>
</body>
</html>
