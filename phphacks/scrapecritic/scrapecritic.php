<html>
<?
// Set up the CURL object
$ch = curl_init( "http://www.metacritic.com/video/" );

// Fake out the User Agent 
curl_setopt( $ch, CURLOPT_USERAGENT, "Internet Explorer" );

// Start the output buffering
ob_start(); 

// Get the HTML from MetaCritic
curl_exec( $ch );
curl_close( $ch );

// Get the contents of the output buffer
$str = ob_get_contents(); 
ob_end_clean(); 

// Get just the list sorted by name
preg_match( "/\<DIV ID=\"sortbyname1\"\>(.*?)\<\/DIV\>/is", $str, $byname );

// Get each of the movie entries
preg_match_all( "/\<SPAN.*?>(.*?)\<\/SPAN\>.*?\<A.*?\>(.*?)\<BR\>/is",
	$byname[0], $moviedata );

// Work through the raw movie data
$movies = array();
for( $i = 0; $i < count( $moviedata[1] ); $i++ )
{
	// The score is ok already
	$score = $moviedata[1][$i];

	// We need to remove tags from the title and decode
	// the HTML entities
	$title = $moviedata[2][$i];
	$title = preg_replace( "/<.*?>/", "", $title );
	$title = html_entity_decode( $title );

	// Then add the movie to the array
	$movies []= array( $score, $title );
}
?>
<body>
<table>
<tr>
<th>Name</th><th>Score</th>
</tr>
<? foreach( $movies as $movie ) { ?>
<tr>
<td><? echo( $movie[1] ) ?></td>
<td><? echo( $movie[0] ) ?></td>
</tr>
<? } ?>
</table>
</body>
</html>
