<?php
function checklinks_start()
{
    ob_start();
}

function checklinks_end()
{
  $doc = ob_get_clean();
  preg_match_all( "/\<a.*?href=[\"|\'](.*?)[\"|\']\>/", $doc, $found );
  print( $doc );

  $badlinks = array();
  foreach( $found[1] as $link )
  {
    $ch = curl_init( $link );
    ob_start();
    curl_exec( $ch );
    $out = ob_get_clean();
    if ( curl_errno( $ch ) != 0 )
       $badlinks []= $link;
    curl_close( $ch );
  }

  if ( count( $badlinks ) > 0 ) {
?>
<br/>
<table style="background: red;" cellspacing="2" cellpadding="2" width="100%">
<tr><td style="white; color: white; text-align:center;">Bad links</td></tr>
<tr><td style="background: white;">
<?php foreach( $badlinks as $link ) { echo( $link."<br/>" ); } ?>
</td></tr>
</table>
<?php } } ?>
