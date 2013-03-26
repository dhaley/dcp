<?
$map = imagecreatefrompng("map.png");
$star = imagecreatefromgif("star.gif");
imagecopyresized( $map, $star, 25, 205, 0, 0,
    imagesx( $star )/5, imagesy( $star )/5,
    imagesx( $star ), imagesy( $star ) );
header("Content-type: image/png");
imagepng($map);
?>
