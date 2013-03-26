<?
$map = imagecreatefrompng("map.png");
$star = imagecreatefromgif("star.gif");
imagecopy( $map, $star, 5, 180, 0, 0, imagesx( $star ), imagesy( $star ) );
header("Content-type: image/png");
imagepng($map);
?>
