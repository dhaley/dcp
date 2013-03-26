<?php
$images = array(
  array( 'lat' => -121.9033, 'lon' => 37.5029, 'img' => "mp0.jpg" ),
  array( 'lat' => -121.8949, 'lon' => 37.5050, 'img' => "mp1.jpg" ),
  array( 'lat' => -121.8889, 'lon' => 37.5060, 'img' => "mp2.jpg" ),
  array( 'lat' => -121.8855, 'lon' => 37.5076, 'img' => "mp3.jpg" ),
  array( 'lat' => -121.8835, 'lon' => 37.5115, 'img' => "mp4.jpg" ),
  array( 'lat' => -121.8805, 'lon' => 37.5120, 'img' => "mp5.jpg" )
);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Simple Google Maps Page</title>
<script src="http://maps.google.com/maps?file=api&v=1&key=<mapskey>" type="text/javascript"></script>
</head>
<body>
<table>
<tr>
<td valign="top">
<div id="map" style="width: 300px; height: 300px"></div>
</td>
<td valign="top">
<img src="mp0.jpg" id="mpimg">
</td>
</tr>
</table>
<script type="text/javascript">
var mp_images = [
<?php $first = true; foreach( $images as $img ) { ?>
<?php if ( $first == false ) { echo( ',' ); } ?>
  { lat: <?php echo( $img['lat'] ) ?>,
    lon: <?php echo( $img['lon'] ) ?>,
    img: "<?php echo( $img['img'] ) ?>" },
<?php $first = false; } ?>
];
var map = new GMap(document.getElementById("map"));
map.addControl(new GSmallMapControl());
map.centerAndZoom(new GPoint(-121.8858, 37.5088), 4);
map.setMapType( G_SATELLITE_TYPE );

var icon = new GIcon();
icon.shadow = "http://www.google.com/mapfiles/shadow50.png";
icon.iconSize = new GSize(20, 34);
icon.shadowSize = new GSize(37, 34);
icon.iconAnchor = new GPoint(9, 34);
icon.infoWindowAnchor = new GPoint(9, 2);
icon.infoShadowAnchor = new GPoint(18, 25);
icon.image = "http://www.google.com/mapfiles/marker.png";

var markers = {};
for( i in mp_images )
{
  markers[i] = new GMarker( new GPoint( mp_images[i].lat, mp_images[i].lon ), icon );
  GEvent.addListener(markers[i], "click", function( ) {
   for( m in markers ) {
     if ( markers[m] == this ) {
       document.getElementById( "mpimg" ).src = mp_images[m].img;
     }
   }
  } );
  map.addOverlay(markers[i]);
}
</script>
</body>
</html>
