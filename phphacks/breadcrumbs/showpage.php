<?php
$id = $_GET['id'];
if ( strlen( $id ) < 1 )
  $id = "home";

$pages = array(
  home => array( id=>"home", parent=>"", title=>"Home", url=>"showpage.php?id=home" ),
  users => array( id=>"users", parent=>"home", title=>"Users", url=>"showpage.php?id=users" ),
  jack => array( id=>"jack", parent=>"users", title=>"Jack", url=>"showpage.php?id=jack" )
  );

function breadcrumbs( $id, $pages )
{
  $bcl = array();
  $pageid = $id;
  while( strlen( $pageid ) > 0 )
  {
    $bcl[] = $pageid;
    $pageid = $pages[ $pageid ]['parent'];
  }
  for( $i = count( $bcl ) - 1; $i >= 0; $i-- )
  {
    $page = $pages[$bcl[$i]];
    if ( $i > 0 )
    {
      echo( "<a href=\"" );
      echo( $page['url'] );
      echo( "\">" );
    }
    echo( $page['title'] );
    if ( $i > 0 )
    {
      echo( "</a> | " );
    }
  }
}
?>
<html>
<head>
<title>Page - <?php echo( $id ); ?></title>
</head>
<body>
Breadcrumbs: <?php breadcrumbs( $id, $pages ); ?><br/>
Page name: <?php echo( $id ); ?>
</body>
</html>
