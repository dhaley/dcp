<?php
// UNIT_TEST_START
// ( 1, 2 ) == 3
// ( 1, -1 ) == 0
// ( 1, 1 ) != 3
// ( 1, -1 ) != 1
// UNIT_TEST_END
function add( $a, $b ) { return $a + $b; }

// UNIT_TEST_START
// ( 1, 2 ) == -1
// ( 1, -1 ) == 2
// ( 1, 1 ) != 1
// ( 1, -1 ) != 1
// UNIT_TEST_END
function minus( $a, $b ) { return $a - $b; }
?>
