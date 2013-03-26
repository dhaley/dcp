<?php
class Record
{
  public $id = null;
  public $first = null;
  public $last = null;

  public function __construct( $id, $first, $last )
  {
    $this->id = $id;
    $this->first = $first;
    $this->last = $last;
  }
}

class USRecord extends Record
{
  public $addr1 = null;
  public $addr2 = null;
  public $city = null;
  public $state = null;
  public $zip = null;

  public function __construct( $id, $first, $last,
    $addr1, $addr2, $city, $state, $zip )
  {
     parent::__construct( $id, $first, $last );
   $this->addr1 = $addr1;
   $this->addr2 = $addr2;
   $this->city = $city;
   $this->state = $state;
   $this->zip = $zip;
  }
}

class ForeignRecord extends Record
{
  public $addr1 = null;
  public $addr2 = null;
  public $city = null;
  public $state = null;
  public $postal = null;
  public $country = null;

  public function __construct( $id, $first, $last,
    $addr1, $addr2, $city, $state, $postal, $country )
  {
     parent::__construct( $id, $first, $last );
   $this->addr1 = $addr1;
   $this->addr2 = $addr2;
   $this->city = $city;
   $this->state = $state;
   $this->postal = $postal;
   $this->country = $country;
  }
}

class RecordFactory
{
  public static function createRecord( $id, $first, $last,
    $addr1, $addr2, $city, $state, $postal, $country )
  {
  if ( strlen( $country ) > 0 && $country != "USA" )
      return new ForeignRecord( $id, $first, $last,
        $addr1, $addr2, $city, $state, $postal, $country );
  else
      return new USRecord( $id, $first, $last,
        $addr1, $addr2, $city, $state, $postal );
  }
}

function readRecords()
{
  $records = array();

  $records []= RecordFactory::createRecord(
   1, "Jack", "Herrington", "4250 San Jaquin Dr.", "",
   "Los Angeles", "CA", "90210", ""
  );
  $records []= RecordFactory::createRecord(
   1, "Megan", "Cunningham", "2220 Toorak Rd.", "",
   "Toorak", "VIC", "3121", "Australia"
  );

  return $records;
}

$records = readRecords();
foreach( $records as $r )
{
  $class = new ReflectionClass( $r );
  print $class->getName()." - ".$r->id." - ".$r->first." - ".$r->last."\n";
}
?>
