<?php
require_once( "Services/Weather.php" );

$weather = new Services_Weather();
$wdc = $weather->service( 'Weatherdotcom' );

function get_average( $zip )
{
  global $wdc;

  $fc = $wdc->getForecast( $zip, 7 );
  $dayavg = 0;
  foreach ( $fc['days'] as $day )
  {
    $high = $day['temperatureHigh'];
    $low = $day['temperatureLow'];
    $dayavg += $high;
    $dayavg += $low;
  }
  return floor(($dayavg/14));
}

$zipa = isset( $_GET['zipa'] ) ? $_GET['zipa'] : '94587';
$zipb = isset( $_GET['zipb'] ) ? $_GET['zipb'] : '19081';
$desired = isset( $_GET['desired'] ) ? $_GET['desired'] : '65';

$tempa = get_average( $zipa );
$tempb = get_average( $zipb );

$da = abs( $desired - $tempa );
$db = abs( $desired - $tempb );
$victor = ( $da < $db ) ? 1 : 2;
$stylea = ( $victor == 1 ) ? "background: #bbb;" : "";
$styleb = ( $victor == 2 ) ? "background: #bbb;" : "";
?>
<html>
<head>
<title>Average Temperature Showdown</title>
<style type="text/css">
td { text-align: center; }
</style>
</head>
<body>
<form>
<table width="600">
<tr>
<th>Desired</th>
<th style="<?php echo($stylea); ?>"><input type="text" name="zipa" value="<?php echo( $zipa ); ?>" size="6" /></th>
<th style="<?php echo($styleb); ?>"><input type="text" name="zipb" value="<?php echo( $zipb ); ?>" size="6" /></th>
</tr>
<tr>
<td><input type="text" name="desired" value="<?php echo( $desired ); ?>" size="3" /></td>
<td style="<?php echo($stylea); ?>"><?php echo( $tempa ); ?></td>
<td style="<?php echo($styleb); ?>"><?php echo( $tempb ); ?></td>
</tr>
<tr>
<td colspan="3"><input type="submit" value="Compare" /></td>
</tr>
</table>
</form>
</body>
</html>
