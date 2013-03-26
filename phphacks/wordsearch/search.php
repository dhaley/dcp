<html>
<body>
<?php
$wordlist = array();

$dom = new DOMDocument();
if ( $_FILES['file']['tmp_name'] )
{
  $dom->load( $_FILES['file']['tmp_name'] );
  $found = $dom->getElementsByTagName( "t" );
  foreach( $found as $element )
  {
    $words = split( ' ', $element->nodeValue );
    foreach( $words as $word )
    {
      $word = preg_replace( '/[,]|[.]/', '', $word );
      $word = preg_replace( '/^\s+/', '', $word );
      $word = preg_replace( '/\s+$/', '', $word );
      if ( strlen( $word ) > 0 )
      {
        $word = strtolower( $word );
        $wordlist[ $word ] = 0;
      }
    }
  }
}

$words = array_keys( $wordlist );
sort( $words );

foreach( $words as $word ) {
?>
<?php echo( $word ); ?><br/>
<?php } ?>
</body>
</html>
