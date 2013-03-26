<?php
class Car
{
  public $name;
  public $speed;
  public $looks;
  public $mileage;
  public function Car( $name, $speed, $looks, $mileage )
  {
    $this->name = $name;
    $this->speed = $speed;
    $this->looks = $looks;
    $this->mileage = $mileage;
  }
}

class CarWeighter
{
  private function diff( $a, $b )
  {
    return abs( $a - $b );
  }

  public function weight( $a, $b )
  {
    $d = 0;
    $d += $this->diff( $a->speed, $b->speed );
    $d += $this->diff( $a->looks, $b->looks );
    $d += $this->diff( $a->mileage, $b->mileage );
    return ( 0 - $d );
  }
}

class CarChooser
{
  private $ideal;
  private $alg;

  function CarChooser( $ideal, $alg )
  {
    $this->ideal = $ideal;
    $this->alg = $alg;
  }

  public function choose( $carlist )
  {
    $minrank = null;
    $found = null;
    $alg = $this->alg;

    foreach( $carlist as $car )
    {
      $rank = $alg->weight( $this->ideal, $car );
      if ( !isset( $minrank ) ) $minrank = $rank;
      if ( $rank >= $minrank )
      {
        $minrank = $rank;
        $found = $car;
      }
    }

    return $found;
  }
}

function pickCar( $car )
{
  $carlist = array();
  $carlist []= new Car( "zippy", 90, 30, 10 );
  $carlist []= new Car( "mom'n'pop", 45, 30, 55 );
  $carlist []= new Car( "beauty", 40, 90, 10 );
  $carlist []= new Car( "enviro", 40, 40, 90 );

  $cw = new CarWeighter();
  $cc = new CarChooser( $car, $cw );
  $found = $cc->choose( $carlist );
  echo( $found->name."\n" );
}

pickCar( new Car( "ideal", 80, 40, 10 ) );
pickCar( new Car( "ideal", 40, 90, 10 ) );
?>
