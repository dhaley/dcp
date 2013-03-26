<?php
require_once( "security.php" );

session_start();
if ( $_SESSION['user'] == null || $_SESSION['user'] < 1 )
{ header( "Location: index.php" ); exit; }

check_roles( $_SESSION['user'], array( 'manager' ) );
?>
<html>
<body>
From here you manage the users.<br/><br/>
Back to the <a href="welcome.php">home page</a>.
</body>
</html>
