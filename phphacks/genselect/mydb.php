<?php
require_once( "dbwrap.php" );

class Book 
{
  function getOne( $id )
  {
    return selectOne( "SELECT * FROM book WHERE id = ?", array( $id ) );
  }
  function getAll()
  {
    return selectBlock( "SELECT * FROM book", array() );
  }
}

class Publisher 
{
  function getOne( $id )
  {
    return selectOne( "SELECT * FROM publisher WHERE id = ?", array( $id ) );
  }
  function getAll()
  {
    return selectBlock( "SELECT * FROM publisher", array() );
  }
}

class Author 
{
  function getOne( $id )
  {
    return selectOne( "SELECT * FROM author WHERE id = ?", array( $id ) );
  }
  function getAll()
  {
    return selectBlock( "SELECT * FROM author", array() );
  }
}

?>
