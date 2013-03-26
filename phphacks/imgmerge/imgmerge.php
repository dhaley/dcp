<?php
$targetsize_x = 4000;
$targetsize_y = 4000;
$outfile = "merged.jpg";
$quality = 100;

$im = @imagecreatetruecolor( $targetsize_x, $targetsize_y );

$sources = array();
$dh = opendir( "." );
while (($file = readdir($dh)) !== false)
{
	if ( preg_match( "/[.]jpg$/", $file ) &&
             $file != $outfile )
	{
		$sources []= imagecreatefromjpeg( $file );
	}
}

$x = 0;
$y = 0;
$index = 0;

while( true )
{
	$width = imagesx( $sources[ $index ] );
	$height = imagesy( $sources[ $index ] );

	imagecopy( $im, $sources[ $index ],
		$x, $y, 0, 0, $width, $height );

	$x += $width;
	if ( $x >= $targetsize_x )
	{
		$x = 0;
		$y += $height;
		if ( $y >= $targetsize_y )
			break;
	}

	$index += 1;
	if ( $index >= count( $sources ) )
		$index = 0;
}

imagejpeg( $im, $outfile, $quality );

imagedestroy( $im );
?>
