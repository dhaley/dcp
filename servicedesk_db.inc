<?php

putenv ("SYBASE=/usr/dist/share/sybase/5.x");

$instance = "SDESKRPT";     
$hostName = "SYBASE";
$databaseName = 'sdesk';
$username = "dh196264";
$password = "dh196264";

$dsn = "sybase://{$username}:{$password}@{$instance}/{$databaseName}";


?>