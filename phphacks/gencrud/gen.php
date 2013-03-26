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
  $updsets = array();
  $updfields = array();
  $insfields = array();
  $insvalues = array();
  $insvars = array();

  foreach( $table['fields'] as $field ) {
	$insfields []= $field['name'];
    if ( $field['pk'] )
	{
      $pk = $field['name'];
	  $insvalues []= 0;
	}
	else
	{
	  $updsets []= $field['name']."=?";
	  $updfields []= '$this->'.$field['name'];

	  $insvalues []= '?';
	  $insvars []= '$this->'.$field['name'];
	}
  }

  $insvars = join( $insvars, ", " );
  $insvalues = join( $insvalues, ", " );
  $insfields = join( $insfields, ", " );
  $updfields []= '$this->'.$pk;
  $updfields = join( $updfields, ", " );
  $updsets = join( $updsets, ", " );
?>
class <?php echo( ucfirst( $table['name'] ) ) ?> 
{
<?php
  foreach( $table['fields'] as $field ) {
?>
  var $<?php echo( $field['name'] ); ?>;
<?php
}
?>

  function <?php echo( ucfirst( $table['name'] ) ) ?>()
  {
    $this->id = null;
  }

  function load($id)
  {
    $data = selectOne( "SELECT * FROM <?php echo( $table['name'] ) ?> WHERE <?php echo( $pk ); ?> = ?", array( $id ) );
<?php
  foreach( $table['fields'] as $field ) {
?>
    $this-><?php echo( $field['name'] ); ?> = $data['<?php echo( $field['name'] ); ?>'];
<?php
}
?>
  }

<?php
  foreach( $table['fields'] as $field ) {
?>
  function get_<?php echo( $field['name'] ) ?>() { return $this-><?php echo( $field['name'] ) ?>; }

  function set_<?php echo( $field['name'] ) ?>( $val ) { $this-><?php echo( $field['name'] ) ?> = $val; }

<?php
}
?>
  function update()
  {
    if ( $this->id != null ) { $this->updateRecord(); }
    else { $this->insertRecord(); }
  }

  function insertRecord()
  {
    return executeCommand( "INSERT INTO <?php echo( $table['name'] ) ?> ( <?php echo($insfields); ?> ) VALUES ( <?php echo($insvalues); ?> )",
      array( <?php echo( $insvars ); ?> ) );
  }

  function updateRecord()
  {
    return executeCommand( "UPDATE <?php echo( $table['name'] ) ?> SET <?php echo($updsets); ?> WHERE <?php echo( $pk ); ?>=?",
      array( <?php echo( $updfields ); ?> ) );
  }

  function deleteRecord( $id )
  {
    return executeCommand( "DELETE FROM <?php echo( $table['name'] ) ?> WHERE <?php echo( $pk ); ?>=?", array( $id ) );
  }
}

<?php }
echo( "?>" );

$php = ob_get_clean();

$fh = fopen( "mydb.php", "w" );
fwrite( $fh, $php );
fclose( $fh );
?>
