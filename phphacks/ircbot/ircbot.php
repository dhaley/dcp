<?php
include_once('Net/SmartIRC.php');
require_once('DB.php');

$dsn = 'mysql://root:password@localhost/books';
$db =& DB::Connect( $dsn, array() );
if (PEAR::isError($db)) { die($db->getMessage()); }

class dbbot
{
    function listdata(&$irc, &$data)
    {
		global $db;

        $irc->message(SMARTIRC_TYPE_CHANNEL, $data->channel, 'Books: ');

        $res = $db->query( "SELECT name FROM book", array( ) );
        while( $res->fetchInto( $row, DB_FETCHMODE_ASSOC ) )
		{
        	$irc->message(SMARTIRC_TYPE_CHANNEL, $data->channel, '  '.$row['name'] );
		}
    }
}

$host = "localhost";
$port = 6667;
$nick = "DBBot";
$chan = "#db";

$bot = &new dbbot( );
$irc = &new Net_SmartIRC( );
$irc->setUseSockets( TRUE );
$irc->registerActionhandler( SMARTIRC_TYPE_CHANNEL, '^list', $bot, 'listdata' );
$irc->connect( $host, $port );
$irc->login( $nick, 'Database bot', 0, $nick );
$irc->join( array( $chan ) );
$irc->listen( );
$irc->disconnect( );
?>
