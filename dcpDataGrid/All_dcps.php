<?php

require_once 'dcpDataGrid.php';
//require_once 'dcpDataObjects/All_dcps.php';
require_once 'dcpDataObjects/Dcp_procedure_verification.php';
require_once 'dcpDataObjects/Sun_server.php';
require_once 'dcpDataObjects/Os_version_release.php';
require_once 'dcpDataObjects/Os.php';
require_once 'dcpDataObjects/Os_version.php';
require_once 'dcpDataObjects/Processor_type.php';
require_once 'dcpDataObjects/Os_choices.php';

require_once 'dcpDataObjects/Model.php';
require_once 'dcpDataObjects/Location.php';
require_once 'dcpDataObjects/Netwrk_isr.php';
require_once 'dcpDataObjects/Slevel.php';
require_once 'dcpDataObjects/Op_env.php';
require_once 'dcpDataObjects/Server_console.php';
require_once 'dcpDataObjects/Frmware_alom.php';

require_once 'dcpDataObjects/Server_frmware_disks.php';

require_once 'dcpDataObjects/Frmware_disks.php';
require_once 'dcpDataObjects/Frmware_hba.php';
require_once 'dcpDataObjects/Frmware_hypervisor.php';
require_once 'dcpDataObjects/Frmware_obp.php';



class ALL_dcps extends dcpDataGrid
 {
   // Member variables
   var $datagrid1;
   //   var $edit_url = 'http://psc.central.sun.com:9000/dcp/dcp_edit.php';
   var $null_label = 'n/a';
   
   function buildPage()
   {
     
     $this->printHeader('view_all_dcps');

     // set error handling for PEAR classes
     PEAR::setErrorHandling(PEAR_ERROR_CALLBACK, array('All_dcps', 'errHandler'));
     $this->datagrid1 =& new Structures_DataGrid(15);

     // Enable streaming and set buffer size to 1,000 records
     //$this->datagrid1->enableStreaming(1000);

     //DB_DataObject::debugLevel(1);
     $os = new dcpDataObjects_Os;
     $os_choices = new dcpDataObjects_Os_choices;
     $os_version = new dcpDataObjects_Os_version;
     $processor_type = new dcpDataObjects_Processor_type;
     $os_version_release = new dcpDataObjects_Os_version_release;
     $os_version_release->joinAdd($os);
     $os_version_release->joinAdd($os_version);
     $os_version_release->joinAdd($processor_type);

     $model = new dcpDataObjects_Model;
     $location = new dcpDataObjects_Location;
     $network = new dcpDataObjects_Netwrk_isr;
     $slevel = new dcpDataObjects_Slevel;
     $op_env = new dcpDataObjects_Op_env;

     $alom = new dcpDataObjects_Frmware_alom;
     $hba = new dcpDataObjects_Frmware_hba;
     $hypervisor = new dcpDataObjects_Frmware_hypervisor;
     $obp = new dcpDataObjects_Frmware_obp;

     $console = new dcpDataObjects_Server_console;

     $server_disks = new dcpDataObjects_Server_frmware_disks;
     $disks = new dcpDataObjects_Frmware_disks;


     $server_disks->joinAdd($disks,"LEFT");
     
     $sun_servers = new dcpDataObjects_Sun_server;

     $sun_servers->joinAdd($os_version_release);
    $sun_servers->joinAdd($model);
    $sun_servers->joinAdd($location);
    $sun_servers->joinAdd($network);
    $sun_servers->joinAdd($slevel);
    $sun_servers->joinAdd($op_env);
    $sun_servers->joinAdd($console, "LEFT");
    $sun_servers->joinAdd($alom);
    $sun_servers->joinAdd($obp);
    $sun_servers->joinAdd($hypervisor, "LEFT");

    $sun_servers->joinAdd($server_disks, "LEFT");    


     $all_dcps = new dcpDataObjects_Dcp_procedure_verification;
     $all_dcps->joinAdd($sun_servers);
     //     print_r($all_dcps);

     $test = $this->datagrid1->bind($all_dcps);
   
     if (PEAR::isError($test)) {
       echo $test->getMessage(); 
       die('An error occured while fetching the dcpDataObject information.');
     }


     //				 new Structures_DataGrid_Column('OS Version', 'null', 'os_name', array('width' => '40%'), null, 'printFullOS()')
     //array('width' => '40%')


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
     				 new Structures_DataGrid_Column('SD Num', 'null', 'sdesk_num',
     							  null, $this->null_label, array('ALL_dcps', 'printEditLink') )
     				 );

     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column('OS', 'null', 'os_name',
     								null, $this->null_label, array('All_dcps', 'printFullOS') )				 				 );
     $this->datagrid1->addColumn(
     			   new Structures_DataGrid_Column('Proc', 'processor_type_name', 'processor_type_name')
     			   );


     $this->datagrid1->addColumn(
     			   new Structures_DataGrid_Column('Location', 'location_name', 'location_name')
     			   );


     $this->datagrid1->addColumn(
     			   new Structures_DataGrid_Column('Model', 'model_name', 'model_name')
     			   );

     $this->datagrid1->addColumn(
     			   new Structures_DataGrid_Column('Network', 'netwrk_isr_name', 'netwrk_isr_name')
     			   );

     $this->datagrid1->addColumn(
     			   new Structures_DataGrid_Column('Env', 'op_env_name', 'op_env_name')
     			   );

     $this->datagrid1->addColumn(
				 new Structures_DataGrid_Column('Obp', 'frmware_obp_name', 'frmware_obp_name')
				 );

     $this->datagrid1->addColumn(
				 new Structures_DataGrid_Column('Alom', 'frmware_alom_name', 'frmware_alom_name')
				 );

     $this->datagrid1->addColumn(
				 new Structures_DataGrid_Column('Disk', 'frmware_disks_name', 'frmware_disks_name')
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