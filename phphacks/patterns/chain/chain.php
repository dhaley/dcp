<?php
abstract class URLHandler
{
  abstract function getRealURL( $url );
}

class URLMapper
{
  private $handlers = array();

  private function URLMapper()
  {
  }

  public function addHandler( $handler )
  {
    $this->handlers []= $handler;
  }

  public function mapURL( $url )
  {
    foreach( $this->handlers as $h )
    {
      $mapped = $h->getRealURL( $url );
      if ( isset( $mapped ) ) return $mapped;
    }
    return $url;
  }

  public static function instance()
  {
    static $inst = null;
    if( !isset( $inst ) ) { $inst = new URLMapper(); }
    return $inst;
  }
}

class ImageURLHandler extends URLHandler
{
  private $base;
  private $imgurl;

  public function ImageURLHandler( $base, $imgurl )
  {
    $this->base = $base;
    $this->imgurl = $imgurl;
  }

  public function getRealURL( $url )
  {
    if ( preg_match( "|^".$this->base."(.*?)$|", $url, $matches ) )
    {
      return $this->imgurl.$matches[1];
    }
    return null;
  }
}

class StoryURLHandler extends URLHandler
{
  private $base;
  private $story_url;

  public function StoryURLHandler( $base, $story_url )
  {
    $this->base = $base;
    $this->story_url = $story_url;
  }

  public function getRealURL( $url )
  {
    if ( preg_match( "|^".$this->base."(.*?)/(.*?)/(.*?)$|", $url, $matches ) )
    {
      return $this->story_url.$matches[1].$matches[2].$matches[3];
    }
    return null;
  }
}


$ih = new ImageURLHandler( "http://mysite.com/images/", "http://mysite.com/image.php?img=" );
URLMapper::instance()->addHandler( $ih );
$ih = new StoryURLHandler( "http://mysite.com/story/", "http://mysite.com/story.php?id=" );
URLMapper::instance()->addHandler( $ih );

$testurls = array();
$testurls []= "http://mysite.com/index.html";
$testurls []= "http://mysite.com/images/dog";
$testurls []= "http://mysite.com/story/11/05/05";
$testurls []= "http://mysite.com/images/cat";
$testurls []= "http://mysite.com/image.php?img=lizard";

foreach( $testurls as $in )
{
  $out = URLMapper::instance()->mapURL( $in );
  print "$in\n -->  $out\n\n";
}
?>
