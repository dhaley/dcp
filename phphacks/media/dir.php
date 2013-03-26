<?php
require_once( "db.php" );
$db =& DB::connect("mysql://root@localhost/media", array());
if (PEAR::isError($db)) { die($db->getMessage()); }
?>
<html>
<body>
<?php
$res = $db->query( "SELECT * FROM media" );
while ($res->fetchInto($row)) { ?>
<a href="download.php?id=<?php echo( $row[0] ); ?>">
<?php echo( $row[1] ); ?></a><br/>
<?php } ?>
</body>
</html>
