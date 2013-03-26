<?php
$dir = opendir( "pics" );
$pics = array();
while( $fname = readdir( $dir ) )
{
  if ( preg_match( "/[.]jpg$/", $fname ) )
    $pics []= $fname;
}
closedir( $dir );

foreach( $pics as $fname )
{
  $im = imagecreatefromjpeg( "pics/$fname" );
  $ox = imagesx( $im );
  $oy = imagesy( $im );

  $nx = 100;
  $ny = floor( $oy * ( 100 / $ox ) );

  $nm = imagecreatetruecolor( $nx, $ny );

  imagecopyresized( $nm, $im, 0, 0, 0, 0, $nx, $ny, $ox, $oy );

  print "Creating thumb for $fname\n";

  imagejpeg( $nm, "thumbs/$fname" );
}

print "Creating index.html\n";

ob_start();
?>
<html>
<head><title>Thumbnails</title></head>
<body>
<table cellspacing="0" cellpadding="2" width="500">
<tr>
<?php
$index = 0;
foreach( $pics as $fname ) {
?>
<td valign="middle" align="center">
<a href="pics/<?php echo( $fname ); ?>"><img src="thumbs/<?php echo( $fname ); ?>" border="0" /></a>
</td>
<?php
$index += 1;
if ( $index % 5 == 0 ) { echo( "</tr><tr>" ); }
}
?>
</tr>
</table>
</body>
</html>
<?php
$html = ob_get_clean();
$fh = fopen( "index.html", "w" );
fwrite( $fh, $html );
fclose( $fh );
?>
