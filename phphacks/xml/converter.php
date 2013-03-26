<?php
header( "content-type: text/xml" );
?><temperature><?php echo( ($_GET["temp"]*1.8)+32 ) ?></temperature>
