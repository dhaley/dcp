<?php
abstract class TextGraphDataSource
{
  abstract function getCount();
  abstract function getName( $row );
  abstract function getValue( $row );
}

class TextGraph
{
  private $data;
  private $dmin;
  private $dmax;

  public function TextGraph( $data )
  {
    $this->data = $data;
  }

  protected function calculateMinMax()
  {
    $this->dmin = 100000;
    $this->dmax = -100000;
    for( $r = 0; $r < $this->data->getCount(); $r++ )
    {
      $v = $this->data->getValue( $r );
      if ( $v < $this->dmin ) { $this->dmin = $v; }
      if ( $v > $this->dmax ) { $this->dmax = $v; }
    }
  }

  public function render()
  {
    $this->calculateMinMax();
    $ratio = 40 / ( $this->dmax - $this->dmin );
    for( $r = 0; $r < $this->data->getCount(); $r++ )
    {
      $n = $this->data->getName( $r );
      $v = $this->data->getValue( $r );
      $s = ( $v - $this->dmin ) * $ratio;
      echo( sprintf( "%10s : ", $n ) );
      for( $st = 0; $st < $s; $st++ ) { echo("*"); }
      echo( "\n" );
    }
  }
}

class Record
{
  public $name;
  public $age;
  public $salary;
  public function Record( $name, $age, $salary )
  {
    $this->name = $name;
    $this->age = $age;
    $this->salary = $salary;
  }
}

class RecordList
{
  private $records = array();

  public function RecordList()
  {
    $this->records []= new Record( "Jimmy", 23, 26000 );
    $this->records []= new Record( "Betty", 24, 29000 );
    $this->records []= new Record( "Sally", 28, 42000 );
    $this->records []= new Record( "Jerry", 28, 120000 );
    $this->records []= new Record( "George", 43, 204000 );
  }

  public function getRecords()
  {
    return $this->records;
  }
}

class RecordGraphAdapter extends TextGraphDataSource
{
  private $records;

  public function RecordGraphAdapter( $rl )
  {
    $this->records = $rl->getRecords();
  }
  public function getCount( )
  {
    return count( $this->records );
  }
  public function getName( $row )
  {
    return $this->records[ $row ]->name;
  }
  public function getValue( $row )
  {
    return $this->records[ $row ]->salary;
  }
}

$rl = new RecordList();

$ga = new RecordGraphAdapter( $rl );

$tg = new TextGraph( $ga );
$tg->render();
?>
