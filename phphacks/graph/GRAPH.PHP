<?
$width = 400;
$height = 300;

$data = array();
for( $i = 0; $i < 500; $i++ )
{
	$data []= sin( deg2rad( ( $i / 500 ) * 360 ) );
}

$xstart = $width/10;
$ystart = $height - ($height/10);

$image = imagecreate($width, $height);
$back = imagecolorallocate($image, 255, 255, 255);
$border = imagecolorallocate($image, 64, 64, 64);

imageline( $image, $xstart, 0, $xstart, $ystart, $border );
imageline( $image, $xstart, $ystart, $width, $ystart, $border );

imagestring( $image, 2, $xstart-20, $ystart-10, "1", $border );
imagestring( $image, 2, $xstart-20, 0, "-1", $border );
imagestring( $image, 2, $xstart, $ystart+5, "0", $border );
imagestring( $image, 2, $width-20, $ystart+5, "360", $border );

$datatop = 1;
$databottom = -1;

$oldx = 0;
$oldy = 0;
$datacount = count( $data );
$xscale = ( $width - $xstart ) / $datacount;
$yscale = $ystart / ( $datatop - $databottom );
$midline = $ystart / 2;
for( $i = 0; $i < $datacount; $i++ )
{
	$x = $xstart + ( $i * $xscale );
	$y = $midline - ( $data[$i] * $yscale );
	if ( $i > 0 )
	{
		imageline( $image, $oldx, $oldy, $x, $y, $border );
	}
	$oldx = $x;
	$oldy = $y;
}

header("Content-type: image/png");
imagepng($image);
imagedestroy($image);
?>
