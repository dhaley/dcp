<?php
$image = $_GET["image"];
$maxy = $_GET["y"];

$im = @imagecreatefromjpeg( "pics/".$image );
$curx = imagesx( $im );
$cury = imagesy( $im );
$ratio = $maxy / $cury;
$newx = $curx * $ratio;
$newy = $cury * $ratio;

$oim = imagecreatetruecolor( $newx, $newy );
imageantialias( $oim, true );
imagecopyresized( $oim, $im, 0, 0, 0, 0,
	$newx, $newy, $curx, $cury );

header( "content-type: image/jpeg" );
imagejpeg( $oim );
?>
