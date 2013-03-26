<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<?php
function start_section( $id, $title )
{
?>
<table cellspacing="0" cellpadding="0">
<tr>
<td width="30" valign="top">
<a href="javascript: void twist('<?php echo($id); ?>');">
<IMG src="up.gif" border="0" id="img_<?php echo($id); ?>"/>
</a>
</td>
<td width="90%">
<h1><?php echo( $title ); ?></h1>
</td>
</tr>
</table>
<div STYLE="height:0px;"
  id="<?php echo($id); ?>" class="spin-content">
<?php
}
function end_section()
{
?>
</div>
<?php
}
function spinner_header()
{
?>
 <!-- <STYLE type="text/css">
body { font-family: arial, verdana; }
h1 { font-size: medium; border-bottom: 1px solid black; }
.spin-content { font-size: small; overflow:hidden; }
 --> </STYLE>
<script language="Javascript">
function twist( sid )
{
  imgobj = document.getElementById( "img_"+sid );
  divobj = document.getElementById( sid );
  if ( imgobj.src.match( "up.gif" ) )
  {
    imgobj.src = "down.gif";
    divobj.style.height = "auto";
  }
  else
  {
    imgobj.src = "up.gif";
    divobj.style.height = "0px";
  }
}
</script>
<?php
}
?>
<html>
<head>
<?php spinner_header() ?>
</head>
<body>
<?php start_section( "one", "Report part one" ) ?>
This report will tell you a lot of stuff you didn't know before.
And that's good. Because that's what a report should do.<br/><br/>
But it will tell you so much that it needs to be rolled up into sections
so that you don't have to gasp as you see it all at one.
<?php end_section() ?>
<?php start_section( "two", "Report part two" ) ?>
This is a table of numbers and such:<br/>
<table>
<tr><th>State</th><th>Total</th></tr>
<tr><td>CA</td><td>$35M</td></tr>
<tr><td>PA</td><td>$22M</td></tr>
<tr><td>NC</td><td>$5M</td></tr>
<tr><td>FL</td><td>$15M</td></tr>
</table>
<?php end_section() ?>
</body>
</html>
