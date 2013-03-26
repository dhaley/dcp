<html>
<?
function placegraphic( $file )
{
	list( $width, $height ) = getimagesize("rss.png");
	echo( "<img src=\"$file\" width=\"$width\" height=\"$height\" />" );
}
?>
<body>
<? placegraphic( "rss.png" ); ?>
</body>
</html>
