<?php
class GraphicSpace
{
  var $image;
  var $colors;

  var $xoffset;
  var $yoffset;
  var $xscale;
  var $yscale;

  function GraphicSpace()
  {
    $this->colors = array();
  }

  function get_image() { return $this->image; }
  function set_image( $im )
  {
    $this->image = $im;
  }
  
  function get_color( $id ) { return $this->colors[ $id ]; }
  function set_color( $id, $color ) { $this->colors[ $id ] = $color; }

  function set_viewport( $left, $top, $right, $bottom )
  {
    $this->xoffset = $left;
    $this->yoffset = $top;

    $this->xscale = imagesx( $this->image ) / ( $right - $left );
    $this->yscale = imagesy( $this->image ) / ( $bottom - $top );
  }

  function transform_x( $x ) { return ( $x - $this->xoffset ) * $this->xscale; }
  function transform_y( $y ) { return ( $y - $this->yoffset ) * $this->yscale; }
  function scale_x( $x ) { return $x * $this->xscale; }
  function scale_y( $y ) { return $y * $this->yscale; }
}

class RenderItem
{
  var $left;
  var $right;
  var $top;
  var $bottom;
  var $color;
  var $z;

  function RenderItem( $left, $top, $right, $bottom, $color, $z )
  {
    $this->left = $left;
    $this->right = $right;
    $this->top = $top;
    $this->bottom = $bottom;
    $this->color = $color;
    $this->z = $z;
  }

  function get_left() { return $this->left; }
  function get_right() { return $this->right; }
  function get_top() { return $this->top; }
  function get_bottom() { return $this->bottom; }
  function get_z() { return $this->z; }

  function render( $gs ) { }
  function transform( $x, $y ) { }
}

class Line extends RenderItem
{
  var $sx;
  var $sy;
  var $ex;
  var $ey;
  var $thickness;

  function Line( $sx, $sy, $ex, $ey, $color, $z, $thickness )
  {
    $this->RenderItem( min( $sx, $ex ), min( $sy, $ey ),
           max( $sx, $ex ), max( $sy, $ey ),
           $color, $z );
    $this->sx = $sx;
    $this->sy = $sy;
    $this->ex = $ex;
    $this->ey = $ey;
    $this->thickness = $thickness;
  }
  function render( $gs )
  {
    if ( $this->thickness > 1 )
      imagesetthickness( $gs->get_image(), $this->thickness );
    $this->drawline( $gs->get_image(),
      $gs->transform_x( $this->sx ),
      $gs->transform_y( $this->sy ),
      $gs->transform_x( $this->ex ),
      $gs->transform_y( $this->ey ),
      $gs->get_color( $this->color ) );
    if ( $this->thickness > 1 )
      imagesetthickness( $gs->get_image(), 1 );
  }
  function drawline( $im, $sx, $sy, $ex, $ey, $color )
  {
    imageline( $im, $sx, $sy, $ex, $ey, $color );
  }
}

class DashedLine extends Line
{
  function drawline( $im, $sx, $sy, $ex, $ey, $color )
  {
    imagedashedline( $im, $sx, $sy, $ex, $ey, $color );
  }
}

class Ball extends RenderItem
{
  var $text;

  function Ball( $x, $y, $size, $color, $text, $z )
  {
    $width = $size / 2;
    if ( $text )
      $width += 20;
    $this->RenderItem( $x, $y,
           $x + $width, $y + ( $size / 2 ),
           $color, $z );
    $this->text = $text;
    $this->size = $size;
  }
  
  function render( $gs )
  {
    imagefilledellipse( $gs->get_image(),
      $gs->transform_x( $this->left ),
      $gs->transform_y( $this->top ),
      $gs->scale_x( $this->size ),
      $gs->scale_x( $this->size ),
      $gs->get_color( $this->color ) );
    if ( strlen( $this->text ) )
      imagestring($gs->get_image(), 0,
        $gs->transform_x( $this->left ) + 7,
        $gs->transform_y( $this->top )-5, $this->text,
        $gs->get_color( $this->color ) );
  }
}

function zsort( $a, $b )
{
  if ( $a->get_z() == $b->get_z() )
    return 0;
  return ( $a->get_z() > $b->get_z() ) ? 1 : -1;
}

class RenderQueue
{
  var $items;

  function RenderQueue() { $this->items = array(); }
  function add( $item ) { $this->items [] = $item; }
  function render( $gs )
  {
    usort( &$this->items, "zsort" );
    foreach( $this->items as $item ) { $item->render( $gs ); }
  }
  function get_size()
  {
    $minx = 1000; $maxx = -1000;
    $miny = 1000; $maxy = -1000;
    foreach( $this->items as $item )
    {
      if ( $item->get_left() < $minx )
        $minx = $item->get_left();
      if ( $item->get_right() > $maxx )
        $maxx = $item->get_right();
      if ( $item->get_top() < $miny )
        $miny = $item->get_top();
      if ( $item->get_bottom() > $maxy )
        $maxy = $item->get_bottom();
    }
    return array( left => $minx, top => $miny, right => $maxx, bottom => $maxy );
  }
}

$width = 400;
$height = 400;

function calcpoint( $d, $r )
{
  $x = cos( deg2rad( $d ) ) * $r;
  $y = sin( deg2rad( $d ) ) * $r;
  return array( $x, $y );
}

$render_queue = new RenderQueue();

$ox = null;
$oy = null;

for( $d = 0; $d < 380; $d += 10 )
{
  list( $x, $y ) = calcpoint( $d, 10 );

  $render_queue->add( new Ball( $x, $y, 1, "line", "", 10 ) );
  $render_queue->add( new Line( 0, 0, $x, $y, "red", 1, 1 ) );

  if ( $ox != null && $oy != null )
  {
    $render_queue->add( new Line( $ox, $oy, $x, $y, "red", 1, 1 ) );
  }
  $ox = $x;
  $oy = $y;
}

$gsize = $render_queue->get_size();

$fudgex = ( $gsize['right'] - $gsize['left'] ) * 0.1;
$gsize['left'] -= $fudgex;
$gsize['right'] += $fudgex;
$fudgey = ( $gsize['bottom'] - $gsize['top'] ) * 0.1;
$gsize['top'] -= $fudgey;
$gsize['bottom'] += $fudgey;

print_r( $gsize );

$im = imagecreatetruecolor( $width, $height );
imageantialias( $im, true );
$bg = imagecolorallocate($im, 255, 255, 255);
imagefilledrectangle( $im, 0, 0, $width, $height, $bg );

$gs = new graphicspace();
$gs->set_image( $im );
$gs->set_color( 'back', $bg );
$gs->set_color( 'line', imagecolorallocate($im, 96, 96, 96) );
$gs->set_color( 'red', imagecolorallocate($im, 255, 0, 0) );
$gs->set_viewport( $gsize['left'], $gsize['top'], $gsize['right'], $gsize['bottom'] );

$render_queue->render( $gs );

imagepng( $im, "test.png" );
imagedestroy( $im );
?>
