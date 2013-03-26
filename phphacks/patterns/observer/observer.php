<?php
class Log
{
  public function message( $sender, $messageType, $data )
  {
    print $messageType." - ".$data."\n";
  }
}

class SubscriptionList
{
  var $list = array();

  public function add( $obj, $method )
  {
    $this->list []= array( $obj, $method );
  }

  public function invoke()
  {
    $args = func_get_args();
    foreach( $this->list as $l ) { call_user_func_array( $l, $args ); }
  }
}

class CustomerList
{
  public $listeners;

  public function CustomerList()
  {
    $this->listeners = new SubscriptionList();
  }

  public function addUser( $user )
  {
    $this->listeners->invoke( $this, "add", "$user" );
  }
}

$l = new Log();
$cl = new CustomerList();
$cl->listeners->add( $l, 'message' );
$cl->addUser( "starbuck" );
?>
