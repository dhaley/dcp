<?php

putenv ("SYBASE=/usr/dist/share/sybase/5.x");

$instance = "CST_SYB";     
$hostName = "SYBASE";
$databaseName = 'registration';
$username = "psc_view";
$password = "psc_view1";

$dsn = "sybase://{$username}:{$password}@{$instance}/{$databaseName}";

?>