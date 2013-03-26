<?php
require_once( "mydb.php" );
$pub = new Publisher();
?>
<html>
<body>
<table>
<?php
$rows = $pub->getAll();
foreach( $rows as $row ) {
?>
<tr><td><?php echo( $row['id'] ); ?></td>
<td><?php echo( $row['name'] ); ?></td></tr>
<?php } ?>
</table>
</body>
</html>
