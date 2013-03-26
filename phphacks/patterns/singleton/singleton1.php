<?php
require( 'DB.php' );

class Database
{
  private $dbh;

  private function Database()
  {
    $dsn = 'mysql://root:password@localhost/test';
    $this->dbh =& DB::Connect( $dsn, array() );
    if (PEAR::isError($this->dbh)) { die($this->dbh->getMessage()); }
  }

  public static function get_handle()
  {
    static $db = null;
    if ( !isset($db) ) $db = new Database();
    return $db->dbh;
  }
}

echo( Database::get_handle()."\n" );
echo( Database::get_handle()."\n" );
echo( Database::get_handle()."\n" );
?>
