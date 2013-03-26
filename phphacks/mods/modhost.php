<?php
class DrawingEnvironment
{
  private $img = null;
  private $x = null;
  private $y = null;
  private $colors = array();

  public function __construct( $x, $y )
  {
    $this->img = imagecreatetruecolor( $x, $y );

    $this->addColor( 'white', 255, 255, 255 );
    $this->addColor( 'black', 0, 0, 0 );
    $this->addColor( 'red', 255, 0, 0 );
    $this->addColor( 'green', 0, 255, 0 );
    $this->addColor( 'blue', 0, 0, 255 );

    imagefilledrectangle( $this->image(),
      0, 0, $x, $y, $this->color( 'white' ) );
  }

  public function image() { return $this->img; }
  public function size_x() { return $this->x; }
  public function size_y() { return $this->y; }
  public function color( $c ) { return $this->colors[$c]; }

  public function save( $file )
  {
    imagepng( $this->img, $file );
  }
  
  protected function addColor( $name, $r, $g, $b )
  {
    $col = imagecolorallocate($this->img, $r, $g, $b);
    $this->colors[ $name ] = $col;
  }
}

interface DrawingObject
{
  function drawObject( $env );
  function setParam( $name, $value );
}

function loadModules( $dir )
{
  $classes = array();

  $dh = new DirectoryIterator( $dir );
  foreach( $dh as $file )
  {
    if( $file->isDir() == 0 && preg_match( "/[.]php$/", $file ) )
    {
      include_once( $dir."/".$file );
      $class = preg_replace( "/[.]php$/", "", $file );
      $classes []= $class;
    }
  }

  return $classes;
}

$classes = loadModules( "mods" );

$dom = new DOMDocument();
$dom->load( $argv[1] );
$nl = $dom->getElementsByTagName( "image" );
$root = $nl->item( 0 );

$size_x = $root->getAttribute( 'x' );
$size_y = $root->getAttribute( 'y' );
$file = $root->getAttribute( 'file' );

$de = new DrawingEnvironment( $size_x, $size_y );

$obs_spec = array();

$el = $root->firstChild;
while( $el != null )
{
  if ( $el->tagName != null )
  {
    $params = array();
    for( $i = 0; $i < $el->attributes->length; $i++ )
    {
      $p = $el->attributes->item( $i )->nodeName;
      $v = $el->attributes->item( $i )->nodeValue;
      $params[ $p ] = $v;
    }
    
    $obs_spec []= array(
      'type' => $el->tagName,
      'params' => $params
    );
  }
  $el = $el->nextSibling;
}

foreach( $obs_spec as $os )
{
  $ob = null;
  eval( '$ob = new '.$os['type'].'();' );
  foreach( $os[ 'params' ] as $key => $value )
    $ob->setParam( $key, $value );
  $ob->drawObject( $de );
}

$de->save( $file );
?>
