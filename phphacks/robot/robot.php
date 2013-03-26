<?php
require_once 'HTTP/Client.php';

function check_html( $testname, $client, $values )
{
  $resp = $client->currentResponse();
  $body = $resp['body'];

  preg_match( "/\<\!\-\- CART \: (.*?) \-\-\>/", $body, $found );

  print "$testname: ";
  print ( $found[1] == join(",", $values ) ) ? "passed" : "failed";
  print "\n";
}

$client = new HTTP_Client();

$client->get( "http://localhost/phphacks/shopcart/index.php" );

$client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 1 ) );
$client->get( "http://localhost/phphacks/shopcart/index.php" );
check_html( "Add one", $client, array( 1 ) );

$client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 2 ) );
$client->get( "http://localhost/phphacks/shopcart/index.php" );
check_html( "Add two", $client, array( 1, 2 ) );

$client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 3 ) );
$client->get( "http://localhost/phphacks/shopcart/index.php" );
check_html( "Add three", $client, array( 1, 2, 3 ) );

$client->get( "http://localhost/phphacks/shopcart/checkout.php" );
check_html( "Checkout", $client, array( 1, 2, 3 ) );

$client->post( "http://localhost/phphacks/shopcart/delete.php", array( 'ids[]' => 2 ) );
$client->get( "http://localhost/phphacks/shopcart/checkout.php" );
check_html( "Remove two", $client, array( 1, 3 ) );
?>
