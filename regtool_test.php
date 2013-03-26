<?php

  //require 'Structures/DataGrid.php';
require_once 'dcpDataGrid.php';
require_once 'PEAR.php';
define("DB_DATAOBJECT_NO_OVERLOAD",true); /* This is needed for some buggy versions of PHP4 */
require_once "HTML/Table.php";

//require_once "dcpDatabase/MysqlDataSource.php";
require_once "dcpDatabase/RegtoolDataSource.php";


// echo "<h1>we're testing</h1>";
// $datasource = new MysqlDataSource();
// $count = $datasource->count();
// echo "There are $count cats in the farm\n\n";

 echo "<hr>";
  $datasource = new RegtoolDataSource();
  $count = $datasource->count();
  echo "<p>There are $count Regtool cats in the farm\n\n";

error_reporting(E_ALL);
ini_set('display_errors', 1);
require_once 'PEAR.php';
PEAR::setErrorHandling(PEAR_ERROR_DIE); 

$datasource->dump(0,5);

//$datagrid =& new Structures_DataGrid(10);
$datagrid =& new Structures_DataGrid();

// Enable streaming and set buffer size to 1,000 records
$datagrid->enableStreaming(1000);

$test = $datagrid->bindDataSource($datasource);

if (PEAR::isError($test)) {
  echo $test->getMessage(); 
  die('An error occured while fetching the dcpDataObject information.');
 }


// $datagrid->addColumn(
// 			  new Structures_DataGrid_Column(
// 							 '#',
// 							 null,
// 							 null,
// 							 array('style' => 'text-align: right;'),
// 							 null,
// 							 array('All_dcps', 'formatRowNumber'),
// 							 $datagrid->getCurrentRecordNumberStart()
// 							 ));

// $datagrid->addColumn(
//      				 new Structures_DataGrid_Column('Hostname', 'primay_hostname', 'primay_hostname')
//      				 );

// $datagrid->addColumn(
//      				 new Structures_DataGrid_Column('Domain', 'primay_domain', 'primay_domain')
//      				 );

       // Define the Look and Feel
     $tableAttribs = array(
     			   'width' => '100%',
     			   'cellspacing' => '0',
     			   'cellpadding' => '4',
     			   'class' => 'datagrid'
     			   );
     $headerAttribs = array(
     			    'bgcolor' => '#CCCCCC'
       			    );
     $evenRowAttribs = array(
     			     'bgcolor' => '#FFFFFF'
       			     );
     $oddRowAttribs = array(
     			    'bgcolor' => '#EEEEEE'
       			    );
     $rendererOptions = array(
     			      'sortIconASC' => '&uArr;',
     			      'sortIconDESC' => '&dArr;'
     			      );
     // Create a HTML_Table
     $table = new HTML_Table($tableAttribs);
     $tableHeader =& $table->getHeader();
     $tableBody =& $table->getBody();
     
     // Ask the DataGrid to fill the HTML_Table with data, using rendering options
     $test = $datagrid->fill($table, $rendererOptions);

     if (PEAR::isError($test)) {
       echo $test->getMessage(); 
     }

     // Set attributes for the header row
     $tableHeader->setRowAttributes(0, $headerAttribs);
     
     // Set alternating row attributes
     $tableBody->altRowAttributes(0, $evenRowAttribs, $oddRowAttribs, true);
     
     // Output table and paging links
     echo $table->toHtml();
     
     // Display paging links
     $test = $datagrid->render(DATAGRID_RENDER_PAGER);

     if (PEAR::isError($test)) {
       echo $test->getMessage(); 
     }


//$datagrid->render();

?>