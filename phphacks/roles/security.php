<?php
require_once( "dblib.php" );

function check_roles( $user, $roles )
{
  foreach( $roles as $role )
  {
    if ( !has_role( $user, $role ) )
    {
?>
You do not have permissions to access this page.<br/><br/>
Return to the <a href="welcome.php">home page</a>.
<?php
      exit;
    }
  }
}
?>
