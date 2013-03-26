<?php
require_once( "obscure.php" );
obscurejs_start() ?>
<html>
<head>
<script language="JavaScript">
function dowrite()
{
	document.write( "This is a test" );
}
</script>
</head>
<body>
<script language="JavaScript">dowrite();</script>
</body>
</html>
<?php obscurejs_end() ?>
