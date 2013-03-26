<?php
class CustomerName
{
  public $first = "";
  public $middle = "";
  public $last = "";
}

class CustomerAddress
{
  public $line1 = "";
  public $line2 = "";
  public $city = "";
  public $state = "";
  public $zip = "";
}

class Customer
{
  public $id = null;
  public $name = null;
  public $address = null;

  public function Customer()
  {
    $this->name = new CustomerName();
    $this->address = new CustomerAddress();
  }

  public function Load( $id )
  {
    $this->id = $id;
    $this->name->first = "George";
    $this->name->middle = "W";
    $this->name->last = "Bush";
    $this->address->line1 = "1600 Pennsylvania Ave.";
    $this->address->line2 = "";
    $this->address->city = "Washington";
    $this->address->state = "DC";
    $this->address->zip = "20006";
  }

  public function Update()
  {
    // Update the record in the database
    // or insert the record if there is no id
  }

  public function __toString()
  {
    return $this->name->first." ".$this->name->last;
  }
}

$cust = new Customer();
$cust->Load( 1 );
print( $cust );
print( "\n" );
?>
