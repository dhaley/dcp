<?php
$xml = "";
while( !feof(STDIN) ) { $xml .= fgets( STDIN ); }

preg_match_all( "/\<book\s+.*?name=[\"|\'](.*?)[\"|\'].*?\/\>/is", $xml, $found );

foreach( $found[1] as $name ) { print( "$name\n" ); }
?>
