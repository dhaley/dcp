<?php
require_once("tabs.php");
?>
<html>
<head>
<?php tabs_header(); ?>
</head>
<body>

<div style="width:600px;">
<?php tabs_start(); ?>
<?php tab( "Tab one" ); ?>
This is the first tab.
<?php tab( "Tab two" ); ?>
This is the second tab.
<?php tabs_end(); ?>
</div>
</body>
</html>
