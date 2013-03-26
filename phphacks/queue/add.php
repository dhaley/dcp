<?php
require_once( 'queue.php' );

add_to_queue( 'mail_notification',
  array(
    'jack@oreilly.com',
    'You owe use some money. Pay up.'
  ) );
?>
