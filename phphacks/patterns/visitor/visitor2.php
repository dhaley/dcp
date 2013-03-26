<?php
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

abstract class RecordVisitor
{
  abstract function visitRecord( $rec );
}

class RecordList
{
  private $records = array();

  public function RecordList()
  {
    $this->records []= new Record( "Larry", 22, 35000 );
    $this->records []= new Record( "Harry", 25, 37000 );
    $this->records []= new Record( "Mary", 42, 65000 );
    $this->records []= new Record( "Sally", 45, 80000 );
  }

  public function iterate( $vis )
  {
    foreach( $this->records as $r )
    {
      call_user_func( array( $vis, "visitRecord" ), $r );
    }
  }
}

class MinSalaryFinder extends RecordVisitor
{
  public $min = 1000000;
  public function visitRecord( $rec )
  {
    if( $rec->salary < $this->min ) { $this->min = $rec->salary; }
  }
}

$rl = new RecordList();
$msl = new MinSalaryFinder();
$rl->iterate( $msl );
echo( $msl->min."\n" );
?>
