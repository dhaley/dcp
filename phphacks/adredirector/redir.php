<?php
srand(time());
if ( mt_rand(0,10) < 7 )
{
  header( "Location: ".$_GET['url'] );
  exit;
}
?>
<html>
<head>
<script language="Javascript">
function redir()
{
  window.location='<?php echo( $_GET['url'] ); ?>';
}
function startTimer()
{
  window.setTimeout( "redir();", 2000 );
}
</script>
</head>
<body onload="startTimer()">
Here is my groovy ad. You can continue onto the article
<a href="<?php echo( $_GET['url'] ); ?>">here</a>. Or just
wait for a couple of seconds.
</body>
</html>
