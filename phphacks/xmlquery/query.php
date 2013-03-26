<?php
$dbuser = "root";
$dbpassword = "password";
$dbserver = "localhost";
$dbname = "test";

$db = mysql_connect( $dbserver, $dbuser, $dbpassword );
mysql_select_db( $dbname );

$query = "SELECT * FROM user";
if ( $_GET["query"] )
  $query = $_GET["query"];

$res = mysql_query( $query, $db );

header( "content-type: text/xml" );
?>
<result>
<?php while( $row = mysql_fetch_assoc($res) ) { ?>
 <row>
 <?php foreach( $row as $key => $value ) { ?>
  <data field="<?php echo( $key ); ?>"><?php echo( htmlentities( $value ) ); ?></data>
 <?php } ?>
 </row>
<?php } ?>
</result>
