<html>
<body>
<?php
require_once( "cache/lite.php" );
require_once( "net/geo.php" );

$ip = $_SERVER['REMOTE_ADDR'];
$ip = "64.246.30.37";

$geo = new Net_Geo();
$res = $geo->getRecord( "64.246.30.37" );
?>
<table>
<tr><td>IP</td><td><?php echo( $ip ); ?></td></tr>
<tr><td>City</td><td><?php echo( $res['CITY'] ); ?></td></tr>
<tr><td>State</td><td><?php echo( $res['STATE'] ); ?></td></tr>
<tr><td>Country</td><td><?php echo( $res['COUNTRY'] ); ?></td></tr>
<tr><td>Latitude</td><td><?php echo( $res['LAT'] ); ?></td></tr>
<tr><td>Longitude</td><td><?php echo( $res['LONG'] ); ?></td></tr>
</table>
</body>
</html>
