<?php
header( "Content-type:text/x-vCard" );

$first = "Howard";
$last = "Dean";
$email = "dean@dnc.org";
?>

BEGIN:VCARD
VERSION:2.1
N:<?php echo($last); ?>;<?php echo($first); ?> 
FN:<?php echo($first); ?> <?php echo($last); ?> 
EMAIL;PREF;INTERNET:<?php echo($email); ?> 
REV:20050626T024452Z 
END:VCARD
