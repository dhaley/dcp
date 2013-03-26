<?php
require_once( 'XML/RSS.php' );

function getValue( $node, $name )
{
  $nl = $node->getElementsByTagName( $name );
  return $nl->item(0)->nodeValue;
}

$feeds = array();
$feeds []= array(
  'name' => 'Top Stories',
  'url' => 'http://rss.cnn.com/rss/cnn_topstories.rss'
);
$feeds []= array(
  'name' => 'World',
  'url' => 'http://rss.cnn.com/rss/cnn_world.rss'
);
$feeds []= array(
  'name' => 'U.S.',
  'url' => 'http://rss.cnn.com/rss/cnn_us.rss'
);
$feeds []= array(
  'name' => 'Tech',
  'url' => 'http://rss.cnn.com/rss/cnn_tech.rss'
);

$feed = 0;
if ( isset( $_GET['feed'] ) ) $feed = $_GET['feed'];

ob_start();
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $feeds[$feed]['url'] );
curl_setopt($ch, CURLOPT_HEADER, 0);
curl_exec($ch);
curl_close($ch);
$rsstext = ob_get_clean();

$cols = array();
$cols []= "";
$cols []= "";
$cols []= "";
$col = 0;

$doc = new DOMDocument();
$doc->loadXML( $rsstext );
$il = $doc->getElementsByTagName( "item" );
for( $i = 0; $i < $il->length; $i++ )
{
  $item = $il->item( $i );
  $title = getValue( $item, "title" );
  $link = getValue( $item, "link" );
  $description = getValue( $item, "description" );

  $html = "<p class='story'><a href=\"$link\">$title</a></p>";

  $cols[ $col ] .= $html;
  $col++;
  if ( $col >= 3 ) $col = 0;
}
?>
<html>
<head>
<title><?php echo( $feeds[$feed]['name'] ) ?></title>
<style>
body { margin: 0px; padding: 0px; }
.link { font-weight: bold; margin-left: 10px; margin-right: 10px; }
</style>
</head>
<body>
<div style="width:478px;">
<div style="width:478px;border-bottom:1px solid black;margin-bottom: 5px;">
<?php $id = 0; foreach( $feeds as $f ) { ?>
<a class='link' href="index.php?feed=<?php echo($id); ?>">
<?php echo( $f['name'] ); ?></a>  
<?php $id++; } ?>
</div>
<table>
<tr>
<td valign="top" width="33%"><?php echo( $cols[0] ); ?></td>
<td valign="top" width="33%"><?php echo( $cols[1] ); ?></td>
<td valign="top" width="33%"><?php echo( $cols[2] ); ?></td>
</tr>
</table>
</div>
</body>
</html>
