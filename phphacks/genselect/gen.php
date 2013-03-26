<?php
$tables = array();

function start_element( $parser, $name, $attribs )
{ 
  global $tables;
  if ( $name == "TABLE" )
  {
    $table = array();
    $fields = array();

    $table['name'] = $attribs['NAME'];
    $table['fields'] = array();

    $tables []= $table;
  }
  if ( $name == "FIELD" )
  {
    $field = array();
    $field['name'] = $attribs['NAME'];
    $field['type'] = $attribs['TYPE'];
    $field['pk'] = ( $attribs['PRIMARY-KEY'] ==  "true" ) ? 1 : 0;
    $tables[count($tables)-1]['fields'] []= $field;
  }
}
function end_element( $parser, $name ) { }

$parser = xml_parser_create();
xml_set_element_handler($parser, "start_element", "end_element" );
while( !feof( STDIN ) ) {
  $text = fgets( STDIN );
  xml_parse( $parser, $text );
}
xml_parser_free( $parser );

ob_start();

echo( "<?php\n" );
?>
require_once( "dbwrap.php" );

<?php

foreach( $tables as $table ) {
  $pk = null;
  foreach( $table['fields'] as $field ) {
    if ( $field['pk'] )
      $pk = $field['name'];
  }
?>
class <?php echo( ucfirst( $table['name'] ) ) ?> 
{
  function getOne( $id )
  {
    return selectOne( "SELECT * FROM <?php echo( $table['name'] ) ?> WHERE <?php echo( $pk ); ?> = ?", array( $id ) );
  }
  function getAll()
  {
    return selectBlock( "SELECT * FROM <?php echo( $table['name'] ) ?>", array() );
  }
}

<?php }
echo( "?>" );

$php = ob_get_clean();

$fh = fopen( "mydb.php", "w" );
fwrite( $fh, $php );
fclose( $fh );
    
?>
