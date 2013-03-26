<?php
require( "DB.php" );
$db =& DB::connect("mysql://root:password@localhost/queue", array());
if (PEAR::isError($db)) { die($db->getMessage()); }

function add_to_queue( $func, $args )
{
  global $db;

  $dom = new DomDocument();
  $root = $dom->createElement( "arguments" );
  foreach( $args as $argtext )
  {
    $arg = $dom->createElement( "argument" );
    $arg->appendChild( $dom->createTextNode( $argtext ) );
    $root->appendChild( $arg );
  }
  $dom->appendChild( $root );

  $sth = $db->prepare( "INSERT INTO queue VALUES ( 0, ?, ? )" );
  $db->execute( $sth, array( $func, $dom->saveXML() ) );
}

function run_queue()
{
  global $db;
  
  $delsth = $db->prepare( "DELETE FROM queue WHERE id = ?" );

  $res = $db->query( "SELECT id, func, args FROM queue" );
  while( $res->fetchInto( $row ) )
  {
    $id = $row[0];
    $func = $row[1];
    $argxml = $row[2];

    $dom = new DomDocument();
    $dom->loadXML( $argxml );
    $args = array();
    foreach( $dom->getElementsByTagName( "argument" ) as $node )
    {
      $args []= $node->nodeValue;
    }

    call_user_func_array( $func, $args );

    $db->execute( $delsth, array( $id ) );
  }
}
?>
