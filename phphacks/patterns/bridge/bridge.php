<?php
require( "sql.php" );

class TableCreator
{
  static function createTable( $name )
  {
    TableCreatorImp::createTable( $name );
  }
}

TableCreator::createTable( "customer" );
?>
