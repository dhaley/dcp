<?php
class Circle implements DrawingObject
{
  private $radius = null;
  private $color = null;
  private $x = null;
  private $y = null;

  function drawObject( $env )
  {
    $r2 = $this->radius / 2;
    imagefilledellipse( $env->image(),
      $this->x - $r2, $this->y - $r2,
      $this->radius, $this->radius,
      $env->color( $this->color )
    );
  }

  function setParam( $name, $value )
  {
    if ( $name == "radius" ) $this->radius = $value;
    if ( $name == "color" ) $this->color = $value;
    if ( $name == "x" ) $this->x = $value;
    if ( $name == "y" ) $this->y = $value;
  }
}
?>
