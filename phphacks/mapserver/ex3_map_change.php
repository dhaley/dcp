<?PHP
// ex3_map_change.php
// Tyler Mitchell, August 2005
// Build a map using a pre-made map file
// and change one property

// Load MapScript extension
if (!extension_loaded("MapScript"))
  dl('php_mapscript.'.PHP_SHLIB_SUFFIX);

// Create a map object
$oMap = ms_newMapObj("ex2_map_basic.map");

// Change the map object's extent property
$oMap->setExtent(-130,20,-70,70);

// Render the map into an image object
$oMapImage = $oMap->draw();

// Save the map to an image file
$oMapImage->saveImage("worldmap.png");

?>