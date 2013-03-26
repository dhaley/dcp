<?php
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");    // Date in the past
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); // always modified
header("Cache-Control: no-store, no-cache, must-revalidate");  // HTTP/1.1
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");                          // HTTP/1.0
header('Content-type: application/xml');
echo("<?xml version=\"1.0\" ?>\n"); 
?>
<GRAPH TYPE="BAR">
  <TITLE>Revenues 2005</TITLE>

  <YAXIS>Dollars
    <RANGE MIN="0" MAX="50000" />
  </YAXIS>
  <XAXIS>Period
  </XAXIS>

<DATA>
    
<?php
  $colors = array( "0xFF0000", "0xFFFF00", "0xFF00FF", "0x00FFFF", "0x00FF00" ); 

  srand((double)microtime()*1000000);

  for ($i = 1; $i < 7; $i++)
  {
    $clr = $colors[ ($i - 1) % count($colors)  ] ;
    $val = rand(10000,45000); 
    echo("<D$i>$val<COLOR C=\"$clr\" /></D$i>\n");
  }
  /*
  <D1>20000<COLOR C="0xFF0000" /></D1>
  <D2>25000<COLOR C="0xFFFF00" /></D2>
  <D3>27000<COLOR C="0xFF00FF" /></D3>
  <D4>42000<COLOR C="0x00FFFF" /></D4>
  <D5>48000<COLOR C="0x00FF00" /></D5>
  */
?>

</DATA>
</GRAPH>
