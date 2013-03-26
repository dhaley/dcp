<?php
abstract class OutputBuilder
{
  abstract function getOutput();
  abstract function startBody();
  abstract function endBody();
  abstract function addText( $text );
  abstract function addBreak();
}

class HTMLBuilder extends OutputBuilder
{
  private $buffer = "";

  public function getOutput()
  {
    return "<html>\n".$this->buffer."\n</html>\n";
  }
  public function startBody() { $this->add( "<body>" ); }
  public function endBody() { $this->add( "</body>" ); }
  public function addText( $text ) { $this->add( $text ); }
  public function addBreak() { $this->add( "<br>\n" ); }

  protected function add( $text ) { $this->buffer .= $text; }
}

class XHTMLBuilder extends HTMLBuilder
{
  public function addBreak() { $this->add( "<br />\n" ); }
}

class TextBuilder extends OutputBuilder
{
  private $buffer = "";

  public function getOutput()
  {
    return $this->buffer."\n";
  }
  public function startBody() { }
  public function endBody() { }
  public function addText( $text ) { $this->add( $text ); }
  public function addBreak() { $this->add( "\n" ); }

  protected function add( $text ) { $this->buffer .= $text; }
}

function buildDocument( $builder )
{
  $builder->startBody();
  $builder->addText( 'Jack,' );
  $builder->addBreak();
  $builder->addText( 'You own us $10,000. Have a NICE day.' );
  $builder->endBody();
}

print "HTML:\n\n";

$html = new HTMLBuilder();
buildDocument( $html );
echo( $html->getOutput() );

print "\nXHTML:\n\n";

$xhtml = new XHTMLBuilder();
buildDocument( $xhtml );
echo( $xhtml->getOutput() );

print "\nText:\n\n";

$text = new TextBuilder();
buildDocument( $text );
echo( $text->getOutput() );
?>
