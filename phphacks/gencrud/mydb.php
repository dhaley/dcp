<?php
require_once( "dbwrap.php" );

class Book 
{
  var $id;
  var $title;
  var $publisher_id;
  var $author_id;

  function Book()
  {
    $this->id = null;
  }

  function load($id)
  {
    $data = selectOne( "SELECT * FROM book WHERE id = ?", array( $id ) );
    $this->id = $data['id'];
    $this->title = $data['title'];
    $this->publisher_id = $data['publisher_id'];
    $this->author_id = $data['author_id'];
  }

  function get_id() { return $this->id; }

  function set_id( $val ) { $this->id = $val; }

  function get_title() { return $this->title; }

  function set_title( $val ) { $this->title = $val; }

  function get_publisher_id() { return $this->publisher_id; }

  function set_publisher_id( $val ) { $this->publisher_id = $val; }

  function get_author_id() { return $this->author_id; }

  function set_author_id( $val ) { $this->author_id = $val; }

  function update()
  {
    if ( $this->id != null ) { $this->updateRecord(); }
    else { $this->insertRecord(); }
  }

  function insertRecord()
  {
    return executeCommand( "INSERT INTO book ( id, title, publisher_id, author_id ) VALUES ( 0, ?, ?, ? )",
      array( $this->title, $this->publisher_id, $this->author_id ) );
  }

  function updateRecord()
  {
    return executeCommand( "UPDATE book SET title=?, publisher_id=?, author_id=? WHERE id=?",
      array( $this->title, $this->publisher_id, $this->author_id, $this->id ) );
  }

  function deleteRecord( $id )
  {
    return executeCommand( "DELETE FROM book WHERE id=?", array( $id ) );
  }
}

class Publisher 
{
  var $id;
  var $name;

  function Publisher()
  {
    $this->id = null;
  }

  function load($id)
  {
    $data = selectOne( "SELECT * FROM publisher WHERE id = ?", array( $id ) );
    $this->id = $data['id'];
    $this->name = $data['name'];
  }

  function get_id() { return $this->id; }

  function set_id( $val ) { $this->id = $val; }

  function get_name() { return $this->name; }

  function set_name( $val ) { $this->name = $val; }

  function update()
  {
    if ( $this->id != null ) { $this->updateRecord(); }
    else { $this->insertRecord(); }
  }

  function insertRecord()
  {
    return executeCommand( "INSERT INTO publisher ( id, name ) VALUES ( 0, ? )",
      array( $this->name ) );
  }

  function updateRecord()
  {
    return executeCommand( "UPDATE publisher SET name=? WHERE id=?",
      array( $this->name, $this->id ) );
  }

  function deleteRecord( $id )
  {
    return executeCommand( "DELETE FROM publisher WHERE id=?", array( $id ) );
  }
}

class Author 
{
  var $id;
  var $name;

  function Author()
  {
    $this->id = null;
  }

  function load($id)
  {
    $data = selectOne( "SELECT * FROM author WHERE id = ?", array( $id ) );
    $this->id = $data['id'];
    $this->name = $data['name'];
  }

  function get_id() { return $this->id; }

  function set_id( $val ) { $this->id = $val; }

  function get_name() { return $this->name; }

  function set_name( $val ) { $this->name = $val; }

  function update()
  {
    if ( $this->id != null ) { $this->updateRecord(); }
    else { $this->insertRecord(); }
  }

  function insertRecord()
  {
    return executeCommand( "INSERT INTO author ( id, name ) VALUES ( 0, ? )",
      array( $this->name ) );
  }

  function updateRecord()
  {
    return executeCommand( "UPDATE author SET name=? WHERE id=?",
      array( $this->name, $this->id ) );
  }

  function deleteRecord( $id )
  {
    return executeCommand( "DELETE FROM author WHERE id=?", array( $id ) );
  }
}

?>