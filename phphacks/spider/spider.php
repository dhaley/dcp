<?php
require_once 'HTTP/Client.php';
require_once 'HTTP/Request/Listener.php';

$baseurl = "http://localhost/phphacks/spider/test/index.html";
$pages = array();

add_urls( $baseurl );

while( ( $page = next_page() ) != null )
{
  add_urls( $page );
}

function next_page()
{
  global $pages;
  foreach( array_keys( $pages ) as $page )
  {
    if ( $pages[ $page ] == null )
      return $page;
  }
  return null;
}

function add_urls( $page )
{
  global $pages;

  $start = microtime();
  $urls = get_urls( $page );
  $resptime = microtime() - $start;
  
  print "$page...\n";

  $pages[ $page ] = array( 'resptime' => floor( $resptime * 1000 ), 'url' => $page );

  foreach( $urls as $url )
  {
    if ( !array_key_exists( $url, $pages ) )
      $pages[ $url ] = null;
  }
}

function get_urls( $page )
{
  $base = preg_replace( "/\/([^\/]*?)$/", "/", $page );

  $client = new HTTP_Client();
  $client->get( $page );
  $resp = $client->currentResponse();
  $body = $resp['body'];

  $out = array();
  
  preg_match_all( "/(\<a.*?\>)/is", $body, $matches );
  foreach( $matches[0] as $match )
  {
    preg_match( "/href=(.*?)[\s|\>]/i", $match, $href );
    if ( $href != null )
    {
      $href = $href[1];
      $href = preg_replace( "/^\"/", "", $href );
      $href = preg_replace( "/\"$/", "", $href );
      if ( preg_match( "/^mailto:/", $href ) )
      {
      }
      elseif ( preg_match( "/^http:\/\//", $href ) )
      {
        if ( preg_match( '/^$base/', $href ) )
          $out []= $href;
      }
      else
      {
        $out []= $base.$href;
      }
    }
  }

  return $out;
}

ob_start();
?>
<html>
<head>
<title>Spider report</title>
</head>
<body>
<table width="600">
<tr>
<th>URL</th>
<th>Response Time (ms)</th>
</tr>
<?php foreach( array_values( $pages ) as $page ) { ?>
<tr>
<td><?php echo( $page['url' ] ); ?></td>
<td><?php echo( $page['resptime' ] ); ?></td>
</tr>
<?php } ?>
</table>
</body>
</html>
<?php
$html = ob_get_clean();
$fh = fopen( "report.html", "w" );
fwrite( $fh, $html );
fclose( $fh );
?>
