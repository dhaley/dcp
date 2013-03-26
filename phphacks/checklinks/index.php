<?php
require_once( "checklinks.php" ); ?>
<html>
<body>
<?php checklinks_start() ?>
<div style="width: 800px" />
<a href="http://www.cnn.com">CNN</a><br/>
<a href="http://badlink">Bad link</a><br/>
<?php checklinks_end() ?>
</div>
</body>
</html>
