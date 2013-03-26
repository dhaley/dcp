<?php
require_once( "menu.php" );

$page = "home";
if ( $_GET['page'] )
	$page = $_GET['page'];
?>
<html>
<head>
<title>Page - <?php echo($page); ?></title>
<?php echo menu_css(); ?>
</head>
<body>
<table cellspaceing="0" cellpadding="5">
<tr>
<td width="200" valign="top">
<?php page_menu( $page ); ?>
</td>
<td width="600" valign="top">
Page: <?php echo( $page ); ?>
</td>
</tr>
</table>
</body>
</html>
