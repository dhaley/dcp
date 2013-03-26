<?php
if( !extension_loaded('gtk')) {
  dl( 'php_gtk.'.PHP_SHLIB_SUFFIX);
}

$start_regex = "/name:\\s*(.*?)\\n/";
$start_text = "name: Jack\nname:Lori\nname:Megan\n";

function delete_event() { return false; }

function shutdown() { gtk::main_quit(); }

function run()
{
  global $rb_regex, $tb_text, $ft;

  $regex = $rb_regex->get_chars(0, -1);
  $text = $tb_text->get_chars(0, -1);

  preg_match_all( $regex, $text, $found );

  $ft->clear();
  $i = 0;
  foreach( $found[1] as $f )
  {
    $ft->insert( $i, array( $f ) );
    $i++;
  }
}

$window = &new GtkWindow();
$window->set_usize( 700, 400 );
$window->set_title( "Regular Expression Tester" );
$window->connect('destroy', 'shutdown');
$window->connect('delete-event', 'delete_event');

$bb = new GtkTable();

$rb = new GtkTable();

$rb_label = new GtkLabel( "Regex:" );
$rb->attach( $rb_label, 0, 1, 0, 1, GTK_SHRINK, GTK_SHRINK, 5, 5 );
$rb_regex = new GtkEntry( );
$rb_regex->insert_text( $start_regex, 0 );
$rb->attach( $rb_regex, 1, 2, 0, 1, GTK_FILL, GTK_SHRINK, 5, 5 );
$rb_run = new GtkButton( "Run" );
$rb_run->connect('clicked', 'run');
$rb->attach( $rb_run, 2, 3, 0, 1, GTK_SHRINK, GTK_SHRINK, 5, 5 );

$tb_label = new GtkLabel( "Text:" );
$rb->attach( $tb_label, 0, 1, 1, 2, GTK_SHRINK, GTK_SHRINK, 5, 5 );
$tb_text = new GtkText( );
$tb_text->set_editable( true );
$tb_text->insert_text( $start_text, 0 );
$rb->attach( $tb_text, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 5, 5 );

$bb->attach( $rb,0,1,0,1,GTK_SHRINK,GTK_FILL,5,5 );

$ft = new GtkCList( 1 );
 
$bb->attach( $ft,1,2,0,1 );

$window->add( $bb );

$window->show_all();

gtk::main();
?>
