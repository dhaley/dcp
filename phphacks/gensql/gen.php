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

foreach( $tables as $table ) {
$pk = null;
?>
DROP TABLE IF EXISTS <?php echo( $table['name'] ) ?>;
CREATE TABLE <?php echo( $table['name'] ) ?> (
<?php
$first = 1;
foreach( $table['fields'] as $field ) {
?>
  <?php echo( $first ? "" : "," ) ?>
<?php echo( $field['name'] ) ?> <?php echo( $field['type'] ) ?>
<?php if ( $field['pk'] ) {
$pk = $field['name'];
?> NOT NULL AUTO_INCREMENT<?php } ?>

<?php
$first = 0;
} ?>
<?php if ( $pk ) { ?>
  ,primary key( <?php echo( $pk ) ?> )
<?php } ?>
);
<?php }

$sql = ob_get_clean();

$fh = fopen( "db.sql", "w" );
fwrite( $fh, $sql );
fclose( $fh );
?>
