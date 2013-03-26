<? echo( "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" ) ?>
<playlist version="1" xmlns="http://xspf.org/ns/0/">
<title>My Radio</title>
<annotation>http://localhost</annotation>
<trackList>    
<?
$dir = opendir( "." );
while ($file = readdir($dir)) {
if ( preg_match( "/[.]mp3$/i", $file ) ) {
?>
<track>
<location>http://localhost/xspf/<? print($file) ?></location>
<annotation><? print( $file ) ?></annotation>
</track>
<? } } ?>
</trackList>
</playlist>
