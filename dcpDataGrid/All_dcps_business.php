<?php

require_once 'dcpDataGrid.php';
require_once 'dcpDataObjects/All_dcps.php';
require_once 'dcpDataObjects/Dcp_procedure_verification.php';
require_once 'dcpDataObjects/Sun_server.php';
require_once 'dcpDataObjects/Os_version_release.php';
require_once 'dcpDataObjects/Os.php';
require_once 'dcpDataObjects/Os_version.php';
require_once 'dcpDataObjects/Processor_type.php';
require_once 'dcpDataObjects/Os_choices.php';

class ALL_dcps_business extends dcpDataGrid
 {
   // Member variables
   var $datagrid1;
   var $null_label = 'n/a';
   
   function buildPage()
   {
     
     $this->printHeader('view_all_dcps_business');

     // set error handling for PEAR classes
     PEAR::setErrorHandling(PEAR_ERROR_CALLBACK, array('All_dcps_business', 'errHandler'));
     $this->datagrid1 =& new Structures_DataGrid(15);

     //DB_DataObject::debugLevel(1);
     $sun_servers = new dcpDataObjects_Sun_server;
     $all_dcps = new dcpDataObjects_Dcp_procedure_verification;
     $all_dcps->joinAdd($sun_servers);

     $test = $this->datagrid1->bind($all_dcps);
   
     if (PEAR::isError($test)) {
       echo $test->getMessage(); 
       die('An error occured while fetching the dcpDataObject information.');
     }


     $this->datagrid1->addColumn(
			  new Structures_DataGrid_Column(
							 '#',
							 null,
							 null,
							 array('style' => 'text-align: right;'),
							 null,
							 array('All_dcps', 'formatRowNumber'),
							 $this->datagrid1->getCurrentRecordNumberStart()
							 ));


     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('Hostname', 'hostname', 'hostname')
     				 );
     
     
     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('DCP #', 'null', 'sdesk_num',
     							  null, $this->null_label, array('ALL_dcps', 'printEditLink') )
     				 );

     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('DCP submit time', 'submit_time', 'submit_time')
     				 );

     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('DCP description', 'short_desc', 'short_desc')
     				 );
     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('SDT owner', 'usr_nm', 'usr_nm')
     				 );
     
     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('SDT priority', 'priority', 'priority')
     				 );

     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('SDT request status', 'request_status', 'request_status')
     				 );

     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('SDT assigned to', 'login', 'login')
     				 );
     
     
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
     $test = $this->datagrid1->fill($table, $rendererOptions);

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
     $test = $this->datagrid1->render(DATAGRID_RENDER_PAGER);

     if (PEAR::isError($test)) {
       echo $test->getMessage(); 
     }
   }
 }
  
?>