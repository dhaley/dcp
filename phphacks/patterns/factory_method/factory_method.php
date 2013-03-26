<?php
class Record
{
  public $id = null;
  public $first = null;
  public $last = null;

  public function Record( $id, $first, $last )
  {
    $this->id = $id;
    $this->first = $first;
    $this->last = $last;
  }
}

class RecordReader
{
  function readRecords()
  {
    $records = array();
  
    $records []= $this->newRecord( 1, "Jack", "Herrington" );
    $records []= $this->newRecord( 2, "Lori", "Herrington" );
    $records []= $this->newRecord( 3, "Megan", "Herrington" );
  
    return $records;
  }
  protected function newRecord( $id, $first, $last )
  {
    return new Record( $id, $first, $last );
  }
}

$rr = new RecordReader();
$records = $rr->readRecords();
foreach( $records as $r )
{
  print $r->id." - ".$r->first." - ".$r->last."\n";
}
?>
