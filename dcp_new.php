<?php

require_once "dcpWizard/dcpNewWizard.php";
require_once "DB.php";
require "db.inc";

// Connect to server
$connection = DB::connect($dsn);
if (DB::isError($connection))
  die($connection->getMessage());

session_start();
ob_start(); // hack to not screw up header information

$newWizard = new dcpNewWizard();
$newWizard->run();



?>