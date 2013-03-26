<?php
interface Listener
{
  public function invoke( $caller, $data );
}

class ListenerList implements Iterator
{
  private $listeners = array();

  public function __construct()
  {
  }

  public function add( $listener )
  {
    $this->listeners []= $listener;
  }

  public function invoke( $caller, $data )
  {
    foreach( $this as $listener )
    {
      $listener->invoke( $caller, $data );
    }
  }

  public function rewind()
  {
    reset($this->listeners);
  }

  public function current()
  {
    return current($this->listeners);
  }

  public function key()
  {
    return key($this->listeners);
  }

  public function next()
  {
    return next($this->listeners);
  }

  public function valid()
  {
    return ( $this->current() !== false );
  }
}

class SimpleListener implements Listener
{
  private $v;
  public function __construct( $v ) { $this->v = $v; }
  public function invoke( $caller, $data )
  {
    echo( $this->v." invoked with with '$data'\n" );
  }
  public function __tostring() { return "Listener ".$this->v; }
}

$ll = new ListenerList();

$ll->add( new SimpleListener( "a" ) );
$ll->add( new SimpleListener( "b" ) );
$ll->add( new SimpleListener( "c" ) );

print("Listeners:\n\n");
foreach( $ll as $listener )
{
  print( $listener );
  print( "\n" );
}

print("\nInvoking Listeners:\n\n");
$ll->invoke( null, "Some data" );
?>
