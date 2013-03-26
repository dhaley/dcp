<?php

require_once 'dcpDataGrid.php';
require_once 'PEAR.php';
define("DB_DATAOBJECT_NO_OVERLOAD",true); /* This is needed for some buggy versions of PHP4 */
require_once "HTML/Table.php";
require_once "dcpDatabase/MysqlDataSource.php";


echo "<h1>we're testing</h1>";
$datasource = new MysqlDataSource();

$count = $datasource->count();
echo "There are $count cats in the farm\n\n";

 error_reporting(E_ALL);
 ini_set('display_errors', 1);
 PEAR::setErrorHandling(PEAR_ERROR_DIE); 


$datasource->sort('hostname');

echo "Here are the 5 lowest alpha ones: \n";

// dump() accepts the same $offset and $len argument as fetch()
$datasource->dump(0,5);





// //$datasource->dump(0,5);

// $datagrid =& new Structures_DataGrid(10);


// // // Enable streaming and set buffer size to 1,000 records
//  $datagrid->enableStreaming(1000);

//  $test = $datagrid->bindDataSource($datasource);

// if (PEAR::isError($test)) {
//   echo $test->getMessage(); 
//   die('An error occured while fetching the dcpDataObject information.');
//  }

//  $datagrid->render();

?>