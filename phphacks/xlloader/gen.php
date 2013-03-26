<?php
$tables = array();
$indata = 0;

function encode( $text )
{
  $text = preg_replace( "/'/", "''", $text );
  return "'".$text."'";
}

function start_element( $parser, $name, $attribs )
{ 
  global $tables, $indata;
  if ( $name == "WORKSHEET" )
  {
  	$tables []= array(
  		'name' => $attribs['SS:NAME'],
  		'data' => array()
  	);
  }
  if ( $name == "ROW" )
  {
  	$tables[count($tables)-1]['data'] []= array();
  }
  if ( $name == "DATA" )
  {
  	$indata = 1;
  }
}
function text( $parser, $text )
{
  global $tables, $indata;
  if ( $indata )
  {
  	$data =& $tables[count($tables)-1]['data'];
  	$data[count($data)-1] []= $text;
  }
}
function end_element( $parser, $name )
{
  global $indata;
  if ( $name == "DATA" )
  	$indata = 0;
}

$parser = xml_parser_create();
xml_set_element_handler( $parser, "start_element", "end_element" );
xml_set_character_data_handler( $parser, "text" );
while( !feof( STDIN ) ) {
  $text = fgets( STDIN );
  xml_parse( $parser, $text );
}
xml_parser_free( $parser );

foreach( $tables as $table ) {
  $name = $table['name'];
  $data =& $table['data'];
  $cols = implode( ", ", $data[0] ); 
  for( $in = 1; $in < count( $data ); $in++ ) {
  	$sqldata = implode( ", ", array_map( "encode", $data[$in] ) ); 
?>
INSERT INTO <?php echo( $name )?> ( <?php echo( $cols ) ?> ) VALUES ( <?php echo( $sqldata ); ?> );

<?php } } ?>
