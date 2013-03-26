<?php
require_once( "DB.php" );
require_once( "Text/Wiki.php" );

$g_wiki = new Text_Wiki();

$g_wiki->enableRule('html');
$g_wiki->enableRule('list');

function wikiToHTML( $text )
{
  global $g_wiki;

  $text = preg_replace( "/\=\=\=\s* Pronunciation.*?\n\=\=\=/is", "\n===", $text );
  $text = preg_replace( "/\=\=\=\=\=\s*(.*?)\s*\=\=\=\=\=/", "\n+++++ $1", $text );
  $text = preg_replace( "/\=\=\=\=\s*(.*?)\s*\=\=\=\=/", "++++ $1", $text );
  $text = preg_replace( "/\=\=\=\s*(.*?)\s*\=\=\=/", "+++ $1", $text );
  $text = preg_replace( "/\=\=\s*(.*?)\s*\=\=/", "++ $1", $text );
  $text = preg_replace( "/\=\s*(.*?)\s*\=/", "++ $1", $text );
  $text = preg_replace( "/\[\[image:.*?\]\]/i", "", $text );
  $text = preg_replace( "/\[\[it:.*?\]\]/i", "", $text );
  $text = preg_replace( "/\[\[.*?\|(.*?)\]\]/", "$1", $text );
  $text = preg_replace( "/\[\[(.*?)\]\]/", "$1", $text );
  $text = preg_replace( "/\[(.*?)\]/", "$1", $text );
  $text = preg_replace( "/\n\#([^#])/", "\n# $1", $text );
  $text = preg_replace( "/\n\*([^*])/", "\n* $1", $text );
  $text = preg_replace( "/\<\!\-\-.*?\-\-\>/mi", "", $text );
  $text = preg_replace( "/\n\|.*?\|\s*\n/", "", $text );
  $text = preg_replace( "/\n\{\|.*\n/", "", $text );
  $text = preg_replace( "/\n\|\}.*\n/", "", $text );
  $text = preg_replace( "/\n\|\}\n/", "", $text );
  $text = preg_replace( "/\{\{.*?\}\}/", "", $text );
  $text = preg_replace( "/\|\}/", "", $text );
  $text = preg_replace( "/\|.*?\|/", "", $text );
  $text = preg_replace( "/\'\'\'\'\'\'/", "'''\n'''", $text );

  return $g_wiki->transform( $text, 'Xhtml' );
}

function goodWord( $word )
{
  if ( preg_match( "/^[A-Za-z]/", $word ) )
  {
    if ( preg_match( "/[^A-Za-z.-]/", $word ) ) return false;
    if ( preg_match( "/\-$/", $word ) ) return false;
    if ( preg_match( "/\[.]$/", $word ) ) return false;
    if ( preg_match( "/^.-/", $word ) ) return false;
    if ( preg_match( "/^.[.]/", $word ) ) return false;

    $cutword = preg_replace( "/[^A-Za-z]/", "", $word );

    if ( strlen( $cutword ) < 4 ) return false;
    if ( strlen( $cutword ) > 20 ) return false;

    return true;
  }
  return false;
}

function goodText( $text )
{
  if ( preg_match( "/#REDIRECT/i", $text ) )
    return false;
  return true;
}

$g_words = array();
$g_wurl = array();

$dsn = 'mysql://root:password@localhost/wp';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$blocksize = 100;
$total_html = "";
$block = 0;
$block_id = 0;


function writeBlock( $block, $html )
{
  $fh = fopen( "pages/words/".$block.".html", "w" );
  fwrite( $fh, "<html><head>\n" );
  fwrite( $fh, "<link rel=\"stylesheet\" type=\"text/css\" href=\"../default.css\" />\n" );
  fwrite( $fh, "</head><body><div style='width:478px'>\n" );
  fwrite( $fh, $html );
  fwrite( $fh, "</div></body></html>\n" );
  fclose( $fh );
}

$res = $db->query( "SELECT cur_title as word, cur_text as text FROM cur WHERE cur_namespace=0"); // LIMIT 10000" );
while ( $res->fetchInto( $row, DB_FETCHMODE_ASSOC ) )
{
  $word = $row['word'];
  $text = $row['text'];
  if ( goodWord( $word ) && goodText( $text ) )
  {
    $c1 = strtolower( $word[0] );
    if ( !isset( $g_words[ $c1 ] ) ) $g_words[ $c1 ] = array();

    $c2 = strtolower( $word[1] );
    if ( !isset( $g_words[ $c1 ][ $c2 ] ) ) $g_words[ $c1 ][ $c2 ] = array();

    $oword = $word;
    $word = strtolower( $word );

    $g_words[ $c1 ][ $c2 ] []= $oword;

    $g_wurl[ $word ] = "../words/".$block_id.".html#".$block;

    print( "$word\n" );

    $total_html .= "<a name=\"".$block."\" />";
    $total_html .= "<div class='word-header'>".$oword."</div>";
    $total_html .= "<table width='100%' cellspacing='0' cellpadding='0'><tr><td>";
    $total_html .= wikiToHTML( $text );
    $total_html .= "</td></tr></table>";

    if ( $block >= $blocksize )
    {
      writeBlock( $block_id, $total_html );
      $block_id++;
      $block = 0;
      $total_html = "";
    }
    else
      $block++;
  }
}
writeBlock( $block_id, $total_html );

ob_start();
?>
<html><head><title>Index</title>
<link rel="stylesheet" type="text/css" href="default.css" />
</head><body><div style="width:478px;">
<div id="c1-header">
<?php
foreach( array_keys( $g_words ) as $c1 )
{
?>
<a href="lev1/<?php echo( $c1 ); ?>.html"><?php echo( $c1 ); ?></a>  
<?php
}
?>
</div></div></body></html>
<?php
$index = ob_get_clean();
$ih = fopen( "pages/index.html", "w" );
fwrite( $ih, $index );
fclose( $ih );

ob_start();
foreach( array_keys( $g_words ) as $c1 )
{
?>
<a href="../lev1/<?php echo( $c1 ); ?>.html"><?php echo( $c1 ); ?></a>  
<?php
}
$c1header = ob_get_clean();

foreach( array_keys( $g_words ) as $c1 )
{
  ob_start();
?>
<html><head><title><?php echo( $c1 ); ?></title>
<link rel="stylesheet" type="text/css" href="../default.css" />
</head><body><div style="width:478px;">
<div id="c1-header"><?php echo( $c1header ); ?></div>
<?php foreach( array_keys( $g_words[$c1] ) as $c2 ) { ?>
<a href="../lev2/<?php echo( $c1.$c2 ); ?>.html"><?php echo( $c1.$c2 ); ?></a>  
<?php } ?>
</div></body></html>
<?php
  $html = ob_get_clean();

  $fh = fopen( "pages/lev1/".$c1.".html", "w" );
  fwrite( $fh, $html );
  fclose( $fh );
}

foreach( array_keys( $g_words ) as $c1 )
{

ob_start();
foreach( array_keys( $g_words[$c1] ) as $c2 )
{
?>
<a href="<?php echo( $c1.$c2 ); ?>.html"><?php echo( $c1.$c2 ); ?></a>  
<?php
}
$c2header = ob_get_clean();

foreach( array_keys( $g_words[$c1] ) as $c2 )
{
  $words = $g_words[ $c1 ][ $c2 ];
  ob_start();
?>
<html><head><title><?php echo( $c1.$c2 ); ?></title>
<link rel="stylesheet" type="text/css" href="../default.css" />
</head><body><div style="width:478px;">
<div id="c1-header"><?php echo( $c1header ); ?></div>
<div id="c2-header"><?php echo( $c2header ); ?></div>
<?php foreach( $words as $word ) { ?>
<a href="<?php echo( $g_wurl[ strtolower( $word ) ] ); ?>"><?php echo( $word ); ?></a>  
<?php } ?>
</div></body></html>
<?php
  $html = ob_get_clean();

  $fh = fopen( "pages/lev2/".$c1.$c2.".html", "w" );
  fwrite( $fh, $html );
  fclose( $fh );
}
}
?>
