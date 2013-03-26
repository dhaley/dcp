<?php
class StateList
{
  private $states = array();

  private function StateList()
  {
  }
  
  public function addState( $state )
  {
    $this->states []= $state;
  }

  public function getStates()
  {
    return $this->states;
  }

  public static function instance()
  {
    static $states = null;
    if ( !isset($states) ) $states = new StateList();
    return $states;
  }
}

StateList::instance()->addState( "Florida" );
var_dump( StateList::instance()->getStates() );

StateList::instance()->addState( "Kentucky" );
var_dump( StateList::instance()->getStates() );
?>
