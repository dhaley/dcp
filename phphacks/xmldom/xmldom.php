<?php
$books = array(
  array (
      id => 1,
      author => "Jack Herrington",
      name => "Code Generation in Action"
    ),
  array (
      id => 2,
      author => "Jack Herrington",
      name => "Podcasting Hacks"
    ),
  array (
      id => 3,
      author => "Jack Herrington",
      name => "PHP Hacks"
    )
  );

$dom = new DomDocument();
$dom->formatOutput = true;

$root = $dom->createElement( "books" );
$dom->appendChild( $root );

foreach( $books as $book )
{
  $bn = $dom->createElement( "book" );
  $bn->setAttribute( 'id', $book['id'] );

  $author = $dom->createElement( "author" );
  $author->appendChild( $dom->createTextNode( $book['author'] ) );
  $bn->appendChild( $author );

  $name = $dom->createElement( "name" );
  $name->appendChild( $dom->createTextNode( $book['name'] ) );
  $bn->appendChild( $name );

  $root->appendChild( $bn );
}

header( "Content-type: text/xml" );
echo $dom->saveXML();
?>
