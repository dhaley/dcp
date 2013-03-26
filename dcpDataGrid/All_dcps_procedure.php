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

class ALL_dcps_procedure extends dcpDataGrid
 {
   // Member variables
   var $datagrid1;
   var $null_label = 'n/a';
   
   function buildPage()
   {
     
     $this->printHeader('view_all_dcps_procedure');
      echo <<< END
<SCRIPT LANGUAGE="JavaScript">
var Labels = new Array()
var up = '&uArr;';
var down = '&dArr;';
var escape_up = escape(up);
var escape_down = escape(down); 
var tool_escape_up = ('tool' + escape_up);
var tool_escape_down = ('tool' + escape_down); 
 
Labels['Hostname'] = 'Hostname from Regtool';
Labels['DCP #'] = 'DCP ticket from Servicedesk';	      
Labels['Prod'] = 'Host prodcution in Regtool?';
Labels['Dup'] = 'Network interfaces full duplex?';      
Labels['Fault'] = 'Network interfaces any faults?';      
Labels['IPMP'] = 'IPMP configured?';
Labels['Mail'] = 'Sendmail verified?';       
Labels['Alias'] = 'Sendmail root alias?';       
Labels['Dump'] = 'Dumpadm validated?';       
Labels['Bkup'] = 'Backups started?';       
Labels['Explo'] = 'Explorer enabled?';       
Labels['Scic'] = 'SCIC enabled?';       
Labels['Mc'] = 'SunMC enabled?';       
Labels['Swat'] = 'SunSwat enabled?';       
Labels['Helio'] = 'Helios enabled?';       
Labels['Pass'] = 'Root password set?';
Labels['Pts'] = 'Pts applied?';       
Labels['Fss'] = 'Fss enabled?';       
Labels['Tool'] = 'Eds tools installed?';
Labels['Tool%26uArr%3B'] = 'Eds tools installed?';
Labels['Tool%26dArr%3B'] = 'Eds tools installed?';
Labels['Tool&uArr;'] = 'Eds tools installed?';
Labels['Tool&dArr;'] = 'Eds tools installed?';    
Labels['OBP'] = 'OBP firmware validated?';       
Labels['HBA'] = 'HBA firmware validated?';       
Labels['Alom'] = 'Alom firmware validated?';       
Labels['Disk'] = 'Disk firmware validated?';       
Labels['Hyp'] = 'Hypervisor firmware validated?';       
Labels['Lu'] = 'LU patches updated?';
//document.write(Labels['Tool%26dArr%3B']);
//document.write(up);
//document.write(escape_up);
//document.write(escape_down);  
//document.write(down);  
</SCRIPT>

END;

     // set error handling for PEAR classes
     PEAR::setErrorHandling(PEAR_ERROR_CALLBACK, array('All_dcps_procedure', 'errHandler'));
     $this->datagrid1 =& new Structures_DataGrid(20);

     //DB_DataObject::debugLevel(1);
     $sun_servers = new dcpDataObjects_Sun_server;
     //DB_DataObject::debugLevel(5);
     $all_dcps = new dcpDataObjects_Dcp_procedure_verification;

     //$all_dcps->joinAdd($sun_servers, "LEFT");
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

     //<a href="javascript:void(0);" onmouseover="return overlib('This is an ordinary  popup.');" onmouseout="return nd();">here</a>

     $this->datagrid1->addColumn(
     				 new Structures_DataGrid_Column(
								'Prod', 'regtool_prod_status', 'regtool_prod_status')
				 );
     
     $this->datagrid1->addColumn(
				 new Structures_DataGrid_Column('Dup', 'netwrk_inferfaces_full_duplex', 'netwrk_inferfaces_full_duplex')
				   );

          $this->datagrid1->addColumn(
				 new Structures_DataGrid_Column('Fault', 'netwrk_interfaces_any_faults', 'netwrk_interfaces_any_faults')
				   );


          $this->datagrid1->addColumn(
				 new Structures_DataGrid_Column('IPMP', 'ipmp_configured', 'ipmp_configured')
				   );

          $this->datagrid1->addColumn(
				 new Structures_DataGrid_Column('Mail', 'sendmail_verified', 'sendmail_verified')
				   );


	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Alias', 'sendmail_root_alias', 'sendmail_root_alias')
				      );


	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Dump', 'dumpadm_validated', 'dumpadm_validated')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Bkup', 'backups_started', 'backups_started')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Explo', 'explorer_enabled', 'explorer_enabled')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Scic', 'scic_enabled', 'scic_enabled')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Mc', 'sunmc_enabled', 'sunmc_enabled')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Swat', 'sunswat_enabled', 'sunswat_enabled')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Helio', 'helios_entry', 'helios_entry')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Pass', 'root_password_set', 'root_password_set')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Pts', 'pts_applied', 'pts_applied')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Fss', 'fss_enabled', 'fss_enabled')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Tool', 'eds_tools_installed', 'eds_tools_installed')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('OBP', 'frmware_obp_validation', 'frmware_obp_validation')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('HBA', 'frmware_hba_validation', 'frmware_hba_validation')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Alom', 'frmware_alom_validation', 'frmware_alom_validation')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Disk', 'frmware_disks_validation', 'frmware_disks_validation')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Hyp', 'frmware_hypervisor_validation', 'frmware_hypervisor_validation')
				      );

	  $this->datagrid1->addColumn(
				      new Structures_DataGrid_Column('Lu', 'lu_patch_update', 'lu_patch_update')
				      );

// | backups_sdt_num               | int(10)                | YES  |     | NULL    |       |
// | eis_radiance_case             | int(10)                | YES  |     | NULL    |       |
// | netcool_inventory_sdt         | int(10)                | YES  |     | NULL    |       |
	  
       // Define the Look and Feel
     $tableAttribs = array(
     			   'width' => '100%',
     			   'cellspacing' => '0',
     			   'cellpadding' => '4',
     			   'class' => 'datagrid'
     			   );

     $headerAttribs = array(
     			    'bgcolor' => '#CCCCCC',
			    //			    'onmouseover' => "return overlib('click here to sort by column')",
			    //       'onmouseover' => 'return overlib(this.cellIndex)',
			    'onmouseover' => 'return overlib(Labels[this.textContent])',
			    'onmouseout' => "return nd();"
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