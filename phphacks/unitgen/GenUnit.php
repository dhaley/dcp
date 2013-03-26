<?php
if ( count( $argv ) < 2 )
{
  print "GenUnit.php usage:\n";
  print "   php GenUnit.php <PHP Script>\n";
  exit;
}

$infile = $argv[1];

define( 'STATE_NORMAL', 0 );
define( 'STATE_IN_UNIT_DEF', 1 );
define( 'STATE_WAITING_FOR_FUNC', 2 );

$state = STATE_NORMAL;

$fh = fopen( $infile, "r" );
$tests = array();
$funcs = array();
while( $str = fgets( $fh ) )
{
  if ( $state == STATE_NORMAL )
  {
    if ( preg_match( "|UNIT_TEST_START|", $str ) )
      $state = STATE_IN_UNIT_DEF;
  }
  else if ( $state == STATE_IN_UNIT_DEF )
  {
    if ( preg_match( "|UNIT_TEST_END|", $str ) )
      $state = STATE_WAITING_FOR_FUNC;
    else
    {
      $str = preg_replace( "|^//\s*|", "", $str );
      $str = preg_replace( "|\s*$|", "", $str );
      $tests []= $str;
    }
  }
  else if ( $state == STATE_WAITING_FOR_FUNC )
  {
    if ( preg_match( "|function\s+(.*?)\(|", $str, $out ) )
    {
      $funcs []= array(
        'function' => $out[1],
        'tests' => $tests
      );
      $state = STATE_NORMAL;
      $tests = array();
    }
  }
}

fclose( $fh );

ob_start();

$outfile = "Test".$infile;
$classname = preg_replace( "|[.]php$|i", "", $outfile );

echo( "<?php\n" );
?>
// This code was written by GenUnit.php
//
// Do not alter the code manually or your revisions
// will be lost the next time GenUnit.php is run.

require_once '<?php echo( $infile ); ?>';
require_once 'PHPUnit2/Framework/TestCase.php';

class <?php echo( $classname ); ?> extends PHPUnit2_Framework_TestCase
{
<?php
$id = 1;
foreach( $funcs as $func )
{
  foreach( $func['tests'] as $test ) {
?>
  function test<?php echo($id); ?>() { $this->assertTrue( <?php echo( $func['function'].$test ) ?> ); }
<?php
  $id+=1;
  }
}
?>
}
<?php
echo( "?>\n" );
$test_php = ob_get_clean();

print ($id-1)." tests created in $outfile\n";

$fh = fopen( $outfile, "w" );
fwrite( $fh, $test_php );
fclose( $fh );
?>
