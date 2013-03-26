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

  public function iterate( $func )
  {
    foreach( $this->records as $r )
    {
      call_user_func( $func, $r );
    }
  }
}

$min = 100000;
function find_min_salary( $rec )
{
  global $min;
  if( $rec->salary < $min ) { $min = $rec->salary; }
}

$rl = new RecordList();
$rl->iterate( "find_min_salary", $min );
echo( $min."\n" );
?>
