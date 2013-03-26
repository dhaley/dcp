<?php
$text = "";
while( !feof( STDIN ) ) { $text .= fgets( STDIN ); }

preg_match_all( "/\<person\>(.*?)\<\/person\>/si", $text, $people );

$list = array();

foreach( $people[1] as $person )
{
	preg_match( "/\<first\>(.*?)\<\/first\>/is", $person, $res );
	$first = $res[1];
	preg_match( "/\<last\>(.*?)\<\/last\>/is", $person, $res );
	$last = $res[1];
	$list []= array(
		'first' => $first,
		'last' => $last
	);
}
print_r( $list );
?>
