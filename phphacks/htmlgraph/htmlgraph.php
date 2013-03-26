<html>
<?
$data = array(
	array( "movies", 20 ),
	array( "food", 30 ),
	array( "workout", 10 ),
	array( "work", 40 )
);
$max = 0;
foreach ( $data as $d ) { $max += $d[1]; }
?>
<body>
<table width="400" cellspacing="0" cellpadding="2">
<? foreach( $data as $d ) {
$percent = ( $d[1] / $max ) * 100;
?>
<tr>
<td width="20%"><? echo( $d[0] ) ?></td>
<td width="10%"><? echo( $d[1] ) ?>%</td>
<td>
<table width="<? echo($percent) ?>%" bgcolor="#aaa">
	<tr><td>&nbsp;</td></tr>
</table>
</td>
</tr>
<? } ?>
</table>
</body>
</html>
