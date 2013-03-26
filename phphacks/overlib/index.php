<?php
function popup( $text, $popup )
{
?>
<a href="javascript:void(0);" onmouseover="return overlib('<?php echo($popup); ?>');" onmouseout="return nd();"><?php echo($text); ?></a>
<?php
}
?>
<html>
<head>
<script type="text/javascript" src="overlib.js"><!-- overLIB (c) Erik Bosrup --></script>
</head>
<body>
<div id="overDiv" style="position:absolute; visibility:hidden; z-index:1000;"></div>
So this is just a test of popups. Not something interesting about <?php popup( 'rabbits', 'Small furry woodland creatures.<br/>Rabbits also make good pets.' ); ?>. Because that would just be silly.
</body>
</html>
