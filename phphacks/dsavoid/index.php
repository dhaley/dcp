<? require_once( "trans.php" ); ?>
<html>
<body>
<form action="handler.php" method="post">
<input type="hidden" name="transid" value="<?php echo( get_transid() ); ?>" />
Name: <input type="text" /><br/>
Amount: <input type="text" size="5" /><br/>
<input type="submit" />
</format>
