<?php
$dsn_host_Name = "unix(/tmp/mysql_coolstack.sock)";
$hostName = ":/tmp/mysql_coolstack.sock";
$databaseName = 'dcp';
$username = "dcp";
$password = "dcp";
$dsn = "mysql://{$username}:{$password}@{$dsn_host_Name}/{$databaseName}";

function showerror() {
  die("Error " . mysql_errno() . " : " . mysql_erro());
}





?>
