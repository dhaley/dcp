<?php
require_once( "PHPReportMaker.php" );
$rep = new PHPReportMaker();
$rep->setUser( "root" );
$rep->setPassword( "" );
$rep->setDatabaseInterface( "mysql" );
$rep->setConnection( "localhost" );
$rep->setDatabase( "books" );
$rep->setSQL( "SELECT NAME,AUTHOR FROM BOOK ORDER BY NAME" );

$rep->setXML( "bookreport.xml" );

$rep->run();
?>
