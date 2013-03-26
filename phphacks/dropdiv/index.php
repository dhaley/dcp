<?php
$nextid = 1;
function start_link( $text )
{
  global $nextid;
  $idtext = "a"+$nextid;
?><a href="javascript: void drop( '<?php echo($idtext); ?>' );"><span id="a_<?php echo($idtext); ?>"><?php echo($text); ?></span></a><div id="<?php echo($idtext); ?>" class="drop" style="visibility:hidden;">
<table cellspacing="0" cellpadding="0" width="170"><tr>
<td valign="top" width="20">
<a href="javascript: void close(<?php echo($idtext); ?>)"><img src="close.gif" border="0"></a>
</td>
<td valign="top" width="150">
<?php
}

function end_link()
{
?>
</td>
</tr></table>
</div><?php
}

function link_header()
{
?>
<style type="text/css">
body { font-family: arial, verdana; }
.drop { 
  padding: 5px;
  font-size: small;
  background: #eee;
  border: 1px solid black;
  position: absolute;
}
</style>
<script language="Javascript">
function drop( sid )
{
  aobj = document.getElementById( "a_"+sid );
  divobj = document.getElementById( sid );
  divobj.style.top = aobj.offsetBottom+10;
  divobj.style.left = aobj.offsetLeft+10;
  divobj.style.visibility = "visible";
}
function close( sid )
{
  divobj = document.getElementById( sid );
  divobj.style.visibility = "hidden";
}
</script>
<?php
}
?>
<html>
<head>
<?php link_header(); ?>
</head>
<body>
Hey <?php start_link( "this is interesting" ); ?>
That really<br/>
Is interesting <?php end_link(); ?>. How about that.
<br/>
The popup will go over text and all that.<br/>
And it will stay up until it's dismissed with the close
button.
</body>
</html>
