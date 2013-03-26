<html><body>
<div style="font-family:courier; font-size:small;">
$data = array(<br/>
<?
$fieldnames = array(
  $_POST['field0' ],
  $_POST['field1' ],
  $_POST['field2' ],
  $_POST['field3' ],
  $_POST['field4' ] );
$rows = split( "\n", $_POST['data'] );
$index = 0;
foreach( $rows as $row )
{
  if ( $index != 0 )
    print( ",<br/>" );
  $index++;

  print( "  array(" );
  $fields = split( ",", $row );
  for( $f = 0; $f < count( $fields ); $f++ )
  {
    $data = $fields[ $f ];
    $data = preg_replace( "/\\\\\"/", "\"", $data );

    if ( $f > 0 )
      print( ", " );
    print( $fieldnames[ $f ] );
    print( " => " );
    print( $data );
  }
  print( "  )" );
}
?><br/>
);
</div>
</body></html>
