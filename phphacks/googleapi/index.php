<?php
require_once("Services/Google.php");

$ignore = array( 'the','for','and','with','the','new','are','but','its','that','was',
'your', 'yours', 'also', 'all', 'use', 'could', 'would', 'should', 'when', 'they',
'far', 'one', 'two', 'three', 'you', 'most', 'how', 'these', 'there', 'now', 'our',
'from', 'only', 'here', 'will' );
$ignorehash = array();
foreach( $ignore as $word ) { $ignorehash[ $word ] = 1; }

$term = "Code Generation";
if( array_key_exists( 'term', $_GET ) )
  $term = $_GET['term'];

$key = "<GOOGLE KEY>";

$google = new Services_Google( $key );
$google->queryOptions['limit'] = 50;
$google->search( $term );

$data = array();
foreach($google as $key => $result)
{
  $data []= array(
    'title' => $result->title,
    'snippet' => $result->snippet,
    'URL' => $result->URL
  );
}

function jsencode( $text )
{
  $text = preg_replace( '/\'/', '', $text );
  return $text;
}

function get_words( $text )
{
  $text = preg_replace( '/\<(.*?)\>/', '', $text );
  $text = preg_replace( '/[.]/', '', $text );
  $text = preg_replace( '/,/', '', $text );
  $text = html_entity_decode( $text );
  $text = preg_replace( '/\<(.*?)\>/', '', $text );
  $text = preg_replace( '/[\'|\"|\-|\+|\:|\;|\@|\/|\\\\|\#|\!|\(|\)]/', '', $text );
  $text = preg_replace( '/\s+/', ' ', $text );

  $words = array();
  foreach( split( ' ', $text ) as $word )
  {
    $word = strtolower( $word );
    $word = preg_replace( '/^\s+/', '', $word );
    $word = preg_replace( '/\s+$/', '', $word );
    if( strlen( $word ) > 2 )
      $words []= $word;
  }
  return $words;
}

$found = array();

$id = 0;
foreach( $data as $row )
{
  $row['id'] = $id; $id += 1;

  $words = @get_words( $row['snippet'] );
  foreach( $words as $word )
  {
    if ( !array_key_exists( $word, $found ) )
    {
      $found[$word] = array();
      $found[$word]['word'] = $word;
      $found[$word]['count'] = 0;
      $found[$word]['rows'] = array();
    }
    $found[$word]['count'] += 1;
    $found[$word]['rows'][$row['URL']] = $row;
  }
}

$good = array();

foreach( array_keys( $found ) as $text )
{
  if ( $found[$text]['count'] > 1 && array_key_exists( $text, $ignorehash ) == false )
    $good []= $found[$text];
}

$min = 1000000;
$max = -1000000;

function row_compare( $a, $b ) { return strcmp( $a['word'], $b['word'] ); }

usort( $good, 'row_compare' );

foreach( $good as $row )
{
  if ( $row['count'] < $min ) $min = $row['count'];
  if ( $row['count'] > $max ) $max = $row['count'];
}

$ratio = 10.0 / (float)( $max - $min );
?>
<html>
<head>
<style type="text/css">
.word-link { line-height: 18pt; }
.title { border-bottom: 1px dotted black; margin-top: 5px; }
.snippet { margin-left: 20px; font-size:small; margin-top: 5px; margin-bottom: 5px; }
</style>
<script language="Javascript">
var pages = [
<?php 
foreach( $data as $row ) {
?>
{
  url: '<?php echo( $row['URL'] ); ?>',
  snippet: '<?php echo( jsencode( $row['snippet'] ) ); ?>',
  title: '<?php echo( jsencode( $row['title'] ) ); ?>'
},
<?php 
}
?>
];

function display( items )
{
  var obj = document.getElementById( 'found' );
  var html = "";
  for( i in items )
  {
    var p = pages[ items[ i ] ];
    html += "<div class=\"title\"><a href=\""+p.url+"\" target=\"_blank\">"+p.title+"</a></div>";
    html += "<div class=\"snippet\">"+p.snippet+"</div>";
  }
  obj.innerHTML = html;
}
</script>
</head>
<body>
<table width="600" cellspacing="0" cellpadding="5">
<tr>
<td colspan="2">
<form>
Search term: <input type="text" name="term" value="<?php echo($term); ?>" />&nbsp;
<input type="submit" value="Search">
</form>
</td>
</tr>
<tr>
<td width="50%" valign="top">
<?php
foreach( $good as $row )
{
$val = (float)( $row['count'] - $min );
$fontsize = floor( 10.0 + ( $val * $ratio ) );
$row_ids = array();
foreach( $row['rows'] as $r ) { $row_ids []= $r['id']; }
$rows = join(',', $row_ids );
?>
<a class="word-link" href="javascript:display([<?php echo($rows); ?>]);" style="font-size:<?php echo($fontsize); ?>pt;"><?php echo( $row['word'] ); ?></a>&nbsp;
<?php } ?>
</td>
<td width="50%" id="found" valign="top">
</td>
</tr>
</table>
</body>
</html>
