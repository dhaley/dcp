<html>
<?
$data = array(
	array( "movies", 20, "red" ),
	array( "food", 30, "green" ),
	array( "workout", 10, "blue" ),
	array( "work", 40, "black" )
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
<table width="<? echo($percent) ?>%" bgcolor="<? echo($d[2]) ?>">
	<tr><td>&nbsp;</td></tr>
</table>
</td>
</tr>
<? } ?>
</table>
</body>
</html>
