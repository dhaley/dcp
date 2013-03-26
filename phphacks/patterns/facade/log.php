<?php
require( "log_impl.php" );

function log_start( $fileName )
{
  Log::instance()->start( $fileName );
}

function log_message( $message )
{
  Log::instance()->add( $message );
}

function log_end()
{
  Log::instance()->end();
}
?>
