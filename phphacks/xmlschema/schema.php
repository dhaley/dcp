<?php
$dbuser = "root";
$dbpassword = "password";
$dbserver = "localhost";
$dbname = "wordpress";

$db = mysql_connect( $dbserver, $dbuser, $dbpassword );

mysql_select_db( $dbname );

$tables_res = mysql_query( "SHOW TABLES FROM ".$dbname, $db );
$tables = array();
while( $tableinfo = mysql_fetch_row($tables_res) ) {
  $tables[] = $tableinfo[ 0 ];
}
mysql_free_result( $tables_res );

header( "content-type: text/xml" );
?>
<schema>
<?php foreach( $tables as $table ) { ?>
<table name="<?php echo( $table ); ?>">
<?php 
$fields_res = mysql_query( "SHOW FIELDS FROM ".$table, $db );
while( $fieldinfo = mysql_fetch_row($fields_res) ) {
?>
<field
  name="<?php echo( $fieldinfo[0]); ?>"
  type="<?php echo( $fieldinfo[1]); ?>"
  />
<?php } 
mysql_free_result( $fields_res );
?>
</table>
<?php } ?>
</schema>
