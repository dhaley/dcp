<html>
<body>
<?php
require_once( 'Contact_Vcard_Parse.php' );
if ( $_FILES['file']['tmp_name'] )
{
   $parse = new Contact_Vcard_Parse();
   $cardinfo = $parse->fromFile( $_FILES['file']['tmp_name'] );
   foreach( $cardinfo as $card )
   {
     $first = $card['N'][0]['value'][0][0];
     $last = $card['N'][0]['value'][1][0];
     $email = $card['EMAIL'][0]['value'][0][0];
?>
<a href="mailto:<?php echo( $email ); ?>">
<?php echo( $first ); ?> <?php echo( $last ); ?>
</a><br/>
<?php
   }
}
?>
</body>
</html>
