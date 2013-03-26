<?php 
function delay( $ie, $amount )
{
  for( $c = 0; $c < ( $amount / 100 ); $c++ )
    com_message_pump( 100 ); 
}

function test_page( $ie, $page, $first, $last )
{
  $ie->Navigate( $page ); 
  delay( $ie, 2000 );
  
  $fn = $ie->Document->getElementById( "first_name" );
  $fn->Value = $first;
  $ln = $ie->Document->getElementById( "last_name" );
  $ln->Value = $last;
  $inf = $ie->Document->getElementById( "inp_form" );
  $inf->submit();
  delay( $ie, 2000 );
  
  $rfn = $ie->Document->getElementById( "res_first" );
  $rfn = $rfn->innerHTML;
  $rln = $ie->Document->getElementById( "res_last" );
  $rln = $rln->innerHTML;

  if( strcmp( $rfn, $first ) == 0 &&
      strcmp( $rln, $last ) == 0 )
  {
    print "Test passed.\n";
    return 0;
  }
  else
  {
    print "Test failed.\n";
    return -1;
  }
}

$ie = new COM("InternetExplorer.Application"); 
$ie->Visible = true; 

$result = test_page( $ie,
  "http://localhost:1222/com/test.php",
  "Charles",
  "Herrington" );

$ie->Quit();

exit( $result ); 
?> 
