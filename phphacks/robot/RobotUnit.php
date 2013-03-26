<?php
require_once 'HTTP/Client.php';
require_once 'PHPUnit2/Framework/TestCase.php';

class RobotUnit extends PHPUnit2_Framework_TestCase
{
  var $client = null;

  private function check_html( $testname, $values )
  {
    $resp = $this->client->currentResponse();
    $body = $resp['body'];
  
    preg_match( "/\<\!\-\- CART \: (.*?) \-\-\>/", $body, $found );
  
    return ( $found[1] == join(",", $values ) );
  }

  function test1()
  {
    $this->client = new HTTP_Client();
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );

    $this->client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 1 ) );
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );
    $this->assertTrue( $this->check_html( "Add one", array( 1 ) ) );
  }

  function test2()
  {
    $this->client = new HTTP_Client();
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );

    $this->client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 1 ) );
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );
    $this->assertTrue( $this->check_html( "Add one", array( 1 ) ) );

    $this->client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 2 ) );
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );
    $this->assertTrue( $this->check_html( "Add two", array( 1, 2 ) ) );
  }

  function test3()
  {
    $this->client = new HTTP_Client();
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );

    $this->client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 1 ) );
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );
    $this->assertTrue( $this->check_html( "Add one", array( 1 ) ) );

    $this->client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 2 ) );
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );
    $this->assertTrue( $this->check_html( "Add two", array( 1, 2 ) ) );

    $this->client->post( "http://localhost/phphacks/shopcart/add.php", array( 'prod_id' => 3 ) );
    $this->client->get( "http://localhost/phphacks/shopcart/index.php" );
    $this->assertTrue( $this->check_html( "Add three", array( 1, 2, 3 ) ) );

    $this->client->get( "http://localhost/phphacks/shopcart/checkout.php" );
    $this->assertTrue( $this->check_html( "Checkout", array( 1, 2, 3 ) ) );

    $this->client->post( "http://localhost/phphacks/shopcart/delete.php", array( 'ids[]' => 2 ) );
    $this->client->get( "http://localhost/phphacks/shopcart/checkout.php" );
    $this->assertTrue( $this->check_html( "Remove two", array( 1, 3 ) ) );
  }
}
?>
