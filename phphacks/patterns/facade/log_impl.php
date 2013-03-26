<?php
class XMLLog
{
  private $fileName;
  private $doc;
  private $log;

  public function XMLLog( $fileName )
  {
    $this->fileName = $fileName;

    $this->doc = new DOMDocument();
    $this->doc->formatOutput = true;
    $this->log = $this->doc->createElement( "log" );
    $this->doc->appendChild( $this->log );
  }

  public function add( $message )
  {
    $mess_obj = $this->doc->createElement( "message" );
    $text = $this->doc->createTextNode( $message );
    $mess_obj->appendChild( $text );
    $this->log->appendChild( $mess_obj );
  }

  public function close()
  {
    $this->doc->save( $this->fileName );
  }
}

class TextLog
{
  private $fh;

  public function TextLog( $fileName )
  {
    $this->fh = fopen( $fileName, "w" );
  }

  public function add( $message )
  {
    fprintf( $this->fh, $message."\n" );
  }

  public function close()
  {
    fclose( $this->fh );
  }
}

class Log
{
  private $xmlLog = null;
  private $textLog = null;

  public function Log()
  {
  }

  public function start( $fileName )
  {
    $this->xmlLog = new XMLLog( $fileName.".xml" );
    $this->textLog = new TextLog( $fileName.".txt" );
  }

  public function add( $message )
  {
    $this->xmlLog->add( $message );
    $this->textLog->add( $message );
  }

  public function end()
  {
    $this->xmlLog->close();
    $this->textLog->close();
  }

  public static function instance()
  {
    static $inst = null;
    if ( !isset( $inst ) ) $inst = new Log();
    return $inst;
  }
}
?>
