<?PHP
// ex5_map_points.php
// Build a map using a single GeoTIFF
// and a text file of coordinates/labels.
// Does not require a mapserver '.map' file to run.
// Tyler Mitchell, August, 2005

// Load MapScript extension
if (!extension_loaded("MapScript"))
  dl('php_mapscript.'.PHP_SHLIB_SUFFIX);

// Create a map object. Provide empty string if not 
// using an existing map file
$oMap = ms_newMapObj("");

// Set size of the output map image
$oMap->setSize(600,300);

// Set the geographic extents of the map.
$oMap->setExtent(-180,-90,180,90);

// Create a map symbol, used as a brush pattern 
// for drawing map features (lines, points, etc.)
$nSymbolId = ms_newSymbolObj($oMap, "circle");
$oSymbol = $oMap->getsymbolobjectbyid($nSymbolId);
$oSymbol->set("type", MS_SYMBOL_ELLIPSE);
$oSymbol->set("filled", MS_TRUE);
$aPoints[0] = 1;
$aPoints[1] = 1;
$oSymbol->setpoints($aPoints);

// Create a data layer and associate it with the map.
// This is the raster layer showing some cloud imagery
$oLayerClouds = ms_newLayerObj($oMap);
$oLayerClouds->set( "name", "clouds");
$oLayerClouds->set( "type", MS_LAYER_RASTER);
$oLayerClouds->set( "status", MS_DEFAULT);
$oLayerClouds->set( "data","data/global_clouds.tif");

// Create another layer to hold point locations
$oLayerPoints = ms_newLayerObj($oMap);
$oLayerPoints->set( "name", "custom_points");
$oLayerPoints->set( "type", MS_LAYER_POINT);
$oLayerPoints->set( "status", MS_DEFAULT);

// Open file with coordinates and label text (x,y,label)
$fPointList = file("data/points.txt");

// For each line in the text file
foreach ($fPointList as $sPointItem)
{
   $aPointArray = explode(",",$sPointItem);
   // :TRICKY: Note although we are using points
   // we must use a line object (newLineObj)
   // here I call it a CoordList object for simplicity 
   $oCoordList = ms_newLineObj();
   $oPointShape = ms_newShapeObj(MS_SHAPE_POINT);
   $oCoordList->addXY($aPointArray[0],$aPointArray[1]);
   $oPointShape->add($oCoordList);
   $oPointShape->set( "text", chop($aPointArray[2]));
   $oLayerPoints->addFeature($oPointShape);
}

// Create a class object to set feature drawing styles.
$oMapClass = ms_newClassObj($oLayerPoints);

// Create a style object defining how to draw features
$oPointStyle = ms_newStyleObj($oMapClass);
$oPointStyle->color->setRGB(250,0,0);
$oPointStyle->outlinecolor->setRGB(255,255,255);
$oPointStyle->set( "symbolname", "circle");
$oPointStyle->set( "size", "10");

// Create label settings for drawing text labels
$oMapClass->label->set( "position", MS_AUTO);
$oMapClass->label->color->setRGB(250,0,0);
$oMapClass->label->outlinecolor->setRGB(255,255,255);


// Render the map into an image object
$oMapImage = $oMap->draw();

// Save the map to an image file
$oMapImage->saveImage("worldmap.png");

?>