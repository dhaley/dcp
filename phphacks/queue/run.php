<?php
require_once( "queue.php" );

function mail_notification( $user, $text )
{
  print "Mailing $user:\n$text\n\n";
}

run_queue();
?>
