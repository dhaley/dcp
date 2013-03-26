<?php
$width = 400;
$height = 400;

$point_count = 10;

$points = array();

for( $point = 0; $point < $point_count; $point++ )
{
  $d = ( 360 / $point_count ) * $point;
  $x = ( $width / 2 ) - ( ( $width / 2 ) * sin( deg2rad( $d ) ) );
  $y = ( $height / 2 ) - ( ( $height / 2 ) * cos( deg2rad( $d ) ) );
  $points []= array( 'x' => $x, 'y' => $y );
}
?>
<html>
<head>
<script src="wz_jsgraphics.js"></script>
</head>
<body>
<div id="graph" style="width:<?php echo($width); ?>px;height:<?php echo($height); ?>px;position:relative;">
</div>
<script>
var jg = new jsGraphics( "graph" );
<?php
for( $start = 0; $start < count( $points ); $start++ ) {
  $sx = $points[$start]['x'];
  $sy = $points[$start]['y'];
for( $end = 0; $end < count( $points ); $end++ ) {
  $ex = $points[$end]['x'];
  $ey = $points[$end]['y'];
?>
jg.drawLine( <?php echo($sx); ?>,  <?php echo($sy); ?>, 
   <?php echo($ex); ?>, <?php echo($ey); ?> );
<?php
} } 
?>
jg.paint();
</script>
</body>
</html>
