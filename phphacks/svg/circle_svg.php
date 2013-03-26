<?php
header( "content-type: text/xml" );

$points_count = 20;

$points = array();
for( $p=0; $p<$points_count; $p++ )
{
	$d = ( 360 / $points_count ) * $p;
	$x = 50 + ( cos( deg2rad( $d ) ) * 50 );
	$y = 50 + ( sin( deg2rad( $d ) ) * 50 );
	$points []= array( 'x' => $x, 'y' => $y );
}

echo ("<?xml version=\"1.0\" standalone=\"no\"?>\n" );
?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.0//EN"
  "http://www.w3.org/TR/SVG/DTD/svg10.dtd">
<svg style="shape-rendering:geometricPrecision;" viewBox="0 0 100 100" xml:space="preserve" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns="http://www.w3.org/2000/svg" preserveAspectRatio="xMidYMid meet">
<?php
foreach( $points as $start ) {
	$sx = $start['x'];
	$sy = $start['y'];
foreach( $points as $end ) {
	$ex = $end['x'];
	$ey = $end['y'];
?>
   <path fill-rule="nonzero" style="fill:#000000;stroke:#FF0000;stroke-width:0.2" d="M<?php echo( $sx." ".$sy ); ?> L<?php echo( $ex." ".$ey ); ?> Z"/>
<?php
} }
?>
</svg>
