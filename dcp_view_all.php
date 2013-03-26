<?php

require_once "dcpDataGrid/All_dcps.php";

session_start();

$config = parse_ini_file('dcpDataObjects/dcp.ini',TRUE);
foreach($config as $class=>$values) {
  $options = &PEAR::getStaticProperty($class,'options');
  $options = $values;
}


$page = new All_dcps;
$page->buildPage();

?>