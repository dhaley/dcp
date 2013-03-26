<?php
require_once( "dblib.php" );

session_start();
if ( $_SESSION['user'] == null || $_SESSION['user'] < 1 )
{ header( "Location: index.php" ); exit; }

$db = get_db();

$res = $db->query( "SELECT name FROM users WHERE id=?", array( $_SESSION['user'] ) );
$res->fetchInto( $row );
?>
<html>
<head><title>Welcome</title></head>
<body>
Welcome <?php echo( $row[0] ); ?><br/><br/>
<?php
if ( has_role( $_SESSION['user'], 'manager' ) ) {
?>
<a href="manage.php">Manage the users</a><br/><br/>
<?php } ?>
<a href="logout.php">Logout</a>
</body>
</html>
