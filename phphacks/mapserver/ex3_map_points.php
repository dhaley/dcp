<?PHP
// ex1_map_basic.php
// Tyler Mitchell, August 2005
// Build a map using a pre-made map file

// Load MapScript extension
if (!extension_loaded("MapScript"))
  dl('php_mapscript.'.PHP_SHLIB_SUFFIX);

// Create a map object.
$oMap = ms_newMapObj("ex4_map_points.map");

// Render the map into an image object
$oMapImage = $oMap->draw();

// Save the map to an image file
$oMapImage->saveImage("worldmap.png");

?>
