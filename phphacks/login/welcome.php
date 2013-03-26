<?php
session_start();
if ( $_SESSION['user'] == null || $_SESSION['user'] < 1 )
{
		header( "Location: index.php" );
		exit;
}

require_once( "DB.php" );
$dsn = 'mysql://root:password@localhost/time';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

$res = $db->query( "SELECT name FROM users WHERE id=?",
	array( $_SESSION['user'] ) );
$res->fetchInto( $row );
?>
<html>
<head><title>Welcome</title></head>
<body>
Welcome <?php echo( $row[0] ); ?><br/><br/>
<a href="logout.php">Logout</a>
</body>
</html>
