<?php
// This code was written by GenUnit.php
//
// Do not alter the code manually or your revisions
// will be lost the next time GenUnit.php is run.

require_once 'Add.php';
require_once 'PHPUnit2/Framework/TestCase.php';

class TestAdd extends PHPUnit2_Framework_TestCase
{
  function test1() { $this->assertTrue( add( 1, 2 ) == 3 ); }
  function test2() { $this->assertTrue( add( 1, -1 ) == 0 ); }
  function test3() { $this->assertTrue( add( 1, 1 ) != 3 ); }
  function test4() { $this->assertTrue( add( 1, -1 ) != 1 ); }
  function test5() { $this->assertTrue( minus( 1, 2 ) == -1 ); }
  function test6() { $this->assertTrue( minus( 1, -1 ) == 2 ); }
  function test7() { $this->assertTrue( minus( 1, 1 ) != 1 ); }
  function test8() { $this->assertTrue( minus( 1, -1 ) != 1 ); }
}
?>
