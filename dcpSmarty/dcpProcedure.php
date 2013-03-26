<?php

require_once 'dcpDataObjects/Model.php';
require_once 'dcpDataObjects/Location.php';
require_once 'dcpDataObjects/Netwrk_isr.php';
require_once 'dcpDataObjects/Slevel.php';
require_once 'dcpDataObjects/Op_env.php';
require_once 'dcpDataObjects/Server_console.php';
require_once 'dcpDataObjects/Frmware_alom.php';
require_once 'dcpDataObjects/Frmware_disks.php';
require_once 'dcpDataObjects/Server_frmware_disks.php';

require_once 'dcpDataObjects/Frmware_hba.php';

require_once 'dcpDataObjects/Server_frmware_hba.php';

require_once 'dcpDataObjects/Frmware_hypervisor.php';
require_once 'dcpDataObjects/Frmware_obp.php';
require_once 'dcpDataObjects/Sun_server.php';
require_once 'dcpDataObjects/Os_version_release.php';
require_once 'dcpDataObjects/Os.php';
require_once 'dcpDataObjects/Os_version.php';
require_once 'dcpDataObjects/Os_release.php';
require_once 'dcpDataObjects/Processor_type.php';
require_once 'dcpDataObjects/Os_choices.php';
require_once 'dcpDataObjects/Dcp_procedure_verification.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_san.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_svm.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_x86.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_zfs.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_assignee.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_clt.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_cluster.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_eeprom.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_offswan.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_onswan.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_vlan.php';
require_once 'dcpDataObjects/Dcp_procedure_verification_work_type.php';

require_once 'dcpSmarty.php';

class dcpProcedure extends dcpSmarty
{
  var $sdesk_num;
  function joinDCPTables ()
  {
    //    DB_DataObject::debug(1);
    //DB_DataObject::debugLevel(1);
    $model = new dcpDataObjects_Model;
    $location = new dcpDataObjects_Location;
    $network = new dcpDataObjects_Netwrk_isr;
    $slevel = new dcpDataObjects_Slevel;
    $op_env = new dcpDataObjects_Op_env;
    $alom = new dcpDataObjects_Frmware_alom;
    $hypervisor = new dcpDataObjects_Frmware_hypervisor;
    $obp = new dcpDataObjects_Frmware_obp;
    $console = new dcpDataObjects_Server_console;

    $dcp = new dcpDataObjects_Dcp_procedure_verification; // base of Join

    $os = new dcpDataObjects_Os;
    $os_choices = new dcpDataObjects_Os_choices;
    $os_version = new dcpDataObjects_Os_version;
    $os_release = new dcpDataObjects_Os_release;
    $processor_type = new dcpDataObjects_Processor_type;
    $os_version_release = new dcpDataObjects_Os_version_release;
    $os_version_release->joinAdd($os, "LEFT");
    $os_version_release->joinAdd($os_version, "LEFT");
    $os_version_release->joinAdd($os_release, "LEFT");
    $os_version_release->joinAdd($processor_type, "LEFT");
    $sun_servers = new dcpDataObjects_Sun_server;
    $sun_servers->joinAdd($os_version_release, "LEFT");
    $sun_servers->joinAdd($model, "LEFT");
    $sun_servers->joinAdd($location, "LEFT");
    $sun_servers->joinAdd($network, "LEFT");
    $sun_servers->joinAdd($slevel, "LEFT");
    $sun_servers->joinAdd($op_env, "LEFT");
    $sun_servers->joinAdd($console, "LEFT");
    $sun_servers->joinAdd($alom, "LEFT");
    $sun_servers->joinAdd($obp, "LEFT");
    $sun_servers->joinAdd($hypervisor, "LEFT");
    //DB_DataObject::debugLevel(1);    
    $dcp->joinAdd($sun_servers, "LEFT");

    return $dcp;
  }

  function joinOptionalTables ($sdesk_num)
  {
    $this->sdesk_num = $sdesk_num;
    $joined_tables = array();

    // svm
    $svm = new dcpDataObjects_Dcp_procedure_verification_svm;    
    if ( $svm->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $svm);
      }

    // zfs
    $zfs = new dcpDataObjects_Dcp_procedure_verification_zfs;
    if ( $zfs->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $zfs);
      }

    // clt
    $clt = new dcpDataObjects_Dcp_procedure_verification_clt;
    if ( $clt->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $clt);
      }

    // san
    $san = new dcpDataObjects_Dcp_procedure_verification_san;
    if ( $san->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $san);
      }

    // eeprom
    $eeprom = new dcpDataObjects_Dcp_procedure_verification_eeprom;
    if ( $eeprom->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $eeprom);
      }

    // cluster
    $cluster = new dcpDataObjects_Dcp_procedure_verification_cluster;
    if ( $cluster->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $cluster);
      }

    // x86
    $x86 = new dcpDataObjects_Dcp_procedure_verification_x86;
    if ( $x86->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $x86);
      }

    // vlan
    $vlan = new dcpDataObjects_Dcp_procedure_verification_vlan;
    if ( $vlan->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $vlan);
      }

    // onswan
    $onswan = new dcpDataObjects_Dcp_procedure_verification_onswan;
    if ( $onswan->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $onswan);
      }

    // offswan
    $offswan = new dcpDataObjects_Dcp_procedure_verification_offswan;
    if ( $offswan->get("$this->sdesk_num") )
      {
	array_push($joined_tables, $offswan);
      }
    return $joined_tables;
  }

  function loadSmarty ($sdesk_num)
  {
    $this->sdesk_num = $sdesk_num;
    $dcp = $this->joinDCPTables();
    //DB_DataObject::debugLevel(5);
    $dcp->get(sdesk_num,"$this->sdesk_num");
    $sun_server = $dcp->getLink('sysid');

    $this->assignLabels();
    $this->smarty->append('view_dcp', array(
					    'sdesk_num'        => $dcp->sdesk_num,
					    'login' => $dcp->login,     
					    'submit_time'  => $dcp->submit_time,     
					    'close_time'     => $dcp->close_time,     
					    'user_sunid' => $dcp->usr_sunid,
					    'usr_nm' => $dcp->usr_nm,
					    'usr_dept' => $dcp->usr_dept,
					    'priority' =>  $dcp->priority,
					    'new_priority' => $dcp->new_priority,
					    'request_status' => $dcp->request_status,
					    'status' => $dcp->status,
					    'short_desc' => $dcp->short_desc,
					    'hostname' => $dcp->hostname,
					    'note' => $dcp->note,
					    'regtool_prod_status_sdt' => $dcp->regtool_prod_status_sdt || '',
					    'gcn_num' => $dcp->gcn_num || '',
					    'os_load_date' => $dcp->os_load_date,
					    'netwrk_inferfaces_full_duplex' => $dcp ->netwrk_inferfaces_full_duplex,
					    'netwrk_interfaces_any_faults' => $dcp->netwrk_interfaces_any_faults,
					    'ipmp_configured' => $dcp->ipmp_configured,
					    'sendmail_verified' => $dcp->sendmail_verified,
					    'sendmail_root_alias' => $dcp->sendmail_root_alias,         
					    'dumpadm_validated' => $dcp->dumpadm_validated,
					    'backups_started' => $dcp->backups_started,
					    'backups_sdt_num' => $dcp->backups_sdt_num || '',
					    'explorer_enabled' => $dcp->explorer_enabled,
					    'scic_enabled' => $dcp->scic_enabled,
					    'sunmc_enabled' => $dcp->sunmc_enabled,
					    'sunswat_enabled' => $dcp->sunswat_enabled,
					    'helios_entry' => $dcp->helios_entry,
					    'eis_radiance_case' => $dcp->eis_radiance_case || '',
					    'netcool_inventory_sdt' => $dcp->netcool_inventory_sdt || '',
					    'root_password_set' => $dcp->root_password_set,
					    'pts_applied' => $dcp->pts_applied,
					    'fss_enabled' => $dcp->fss_enabled,
					    'eds_tools_installed' => $dcp->eds_tools_installed,
					    'frmware_obp_validation' => $dcp->frmware_obp_validation,
					    'frmware_hba_validation' => $dcp->frmware_hba_validation,
					    'frmware_disks_validation' => $dcp->frmware_disks_validation,
					    'frmware_alom_validation' => $dcp->frmware_alom_validation,
					    'frmware_hypervisor_validation' => $dcp->frmware_hypervisor_validation,
					    'lu_patch_update' => $dcp->lu_patch_update,
					    'serial_number' => $dcp->serial_number,
					    'hostid' => $dcp->hostid,
					    'division' => $dcp->division,
					    'model_name' => $dcp->model_name,
					    'location_name' => $dcp->location_name,
					    'netwrk_isr_name' => $dcp->netwrk_isr_name,
					    'slevel_name' => $dcp->slevel_name,
					    'op_env_name' => $dcp->op_env_name,
					    'frmware_obp_name' => $dcp->frmware_obp_name,
					    'frmware_alom_name' => $dcp->frmware_alom_name,
					    'frmware_hypervisor_name' => $dcp->frmware_hypervisor_name,
					    'os_name' => $dcp->os_name,
					    'os_version_name' => $dcp->os_version_name,
					    'os_release_name' => $dcp->os_release_name,
					    'processor_type_name' => $dcp->processor_type_name,
					    'regtool_prod_status' => $dcp->regtool_prod_status,
					    'console_hostname' => $dcp->console_hostname,
					    'console_port' => $dcp->console_port,
					    ));




    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// IF a HOST OBJECT HAS BEEN ASSIGNED

    $sysid = $sun_server->sysid;

    error_log("sysis is $sysid");
    if (isset ($sysid) )
      {
	error_log("made it to herrrrreeeee");
	    $this->smarty->append('view_regtool', array(
					    'serial_number' => $dcp->serial_number,
					    'hostid' => $dcp->hostid,
					    'division' => $dcp->division,
					    'model_name' => $dcp->model_name,
					    'location_name' => $dcp->location_name,
					    'netwrk_isr_name' => $dcp->netwrk_isr_name,
					    'slevel_name' => $dcp->slevel_name,
					    'op_env_name' => $dcp->op_env_name,
					    'frmware_obp_name' => $dcp->frmware_obp_name,
					    'frmware_alom_name' => $dcp->frmware_alom_name,
					    'frmware_hypervisor_name' => $dcp->frmware_hypervisor_name,
					    'os_name' => $dcp->os_name,
					    'os_version_name' => $dcp->os_version_name,
					    'os_release_name' => $dcp->os_release_name,
					    'processor_type_name' => $dcp->processor_type_name,
					    'regtool_prod_status' => $dcp->regtool_prod_status,
					    'console_hostname' => $dcp->console_hostname,
					    'console_port' => $dcp->console_port,
					    'status' => $dcp->status
					    ));

	$disks = new dcpDataObjects_Frmware_disks;
	$server_disks = new dcpDataObjects_Server_frmware_disks;    
	$server_disks->joinAdd($disks);
	$server_disks->sysid = $sysid;

	$server_disks->find();
	while ( $server_disks->fetch() ) {
	  $this->smarty->append('frmware_disks', array(
						       "frmware_disks_name" => $server_disks->frmware_disks_name
						       ));
	  $this->smarty->append('frmware_disks_labels', array(
							      "frmware_disks_name" => 'Disk firmware level'
							      ));
	}

	//    $hba
	$hba = new dcpDataObjects_Frmware_hba;
	$server_hba = new dcpDataObjects_Server_frmware_hba;    // dcpDataObjects_Server_frmware_hba
	$server_hba->joinAdd($hba);
	$server_hba->sysid = $sysid;
	$server_hba->find();


	while ( $server_hba->fetch() )
	  {
	    $this->smarty->append('frmware_hba', array(
						       'frmware_hba_name' => $server_hba->frmware_hba_name,
						       ));
	    $this->smarty->append('frmware_hba_labels', array(
							      'frmware_hba_name' => 'HBA firmware level',
							      ));
	  }
      }

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ($dcp->frmware_hypervisor_name )
	  {
	    $this->smarty->append('frmware_hypervisor', array(
							      'frmware_hypervisor_name' => $dcp->frmware_hypervisor_name,
							      ));
	    $this->smarty->append('frmware_hypervisor_labels', array(
								     'frmware_hypervisor_name' => 'Hypervisor level',
								     ));
	  }

    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // svm
    $svm = new dcpDataObjects_Dcp_procedure_verification_svm;    
    if ( $svm->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_svm_header','SVM status');	
    	$this->smarty->append('view_svm', array(
    						'metadb_defined_on_two_disks' => $svm->metadb_defined_on_two_disks,
						'boot_from_mirror_enabled' => $svm->boot_from_mirror_enabled,
						'lvm_md_tab_updated' => $svm->lvm_md_tab_updated,
    						));
    	$this->smarty->append('view_svm_labels', array(
    						'metadb_defined_on_two_disks' => 'Metadb defined on two disks',
						'boot_from_mirror_enabled' => 'Boot from mirror enabled',
						'lvm_md_tab_updated' => 'Lvm md tab updated',
    						));
      }

    // zfs
    $zfs = new dcpDataObjects_Dcp_procedure_verification_zfs;
    if ( $zfs->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_zfs_header','ZFS status');	
    	$this->smarty->append('view_zfs', array(
    						'boot_zpool' => $zfs->boot_zpool,
    						));
    	$this->smarty->append('view_zfs_labels', array(
    						'boot_zpool' => 'Boot zpool',
    						));

      }

    // clt
    $clt = new dcpDataObjects_Dcp_procedure_verification_clt;
    if ( $clt->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_clt_header','Charlotte data center status');	
    	$this->smarty->append('view_clt', array(
    						'cam_sheet_sent' => $clt->cam_sheet_sent,
						'cam_sheet_sent_date' => $clt->cam_sheet_sent_date,
    						));
    	$this->smarty->append('view_clt_labels', array(
    						'cam_sheet_sent' => 'Cam sheet sent',
						'cam_sheet_sent_date' => 'Cam sheet sent date',
    						));

      }

    // san
    $san = new dcpDataObjects_Dcp_procedure_verification_san;
    if ( $san->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_san_header','SAN status');
    	$this->smarty->append('view_san', array(
    						'san_cr_num' => $san->san_cr_num,
						'san_switch_port_requested_date' => $san->san_switch_port_requested_date,
						'san_connected_date' => $san->san_connected_date,
    						));
    	$this->smarty->append('view_san_labels', array(
    						'san_cr_num' => 'SAN change control number',
						'san_switch_port_requested_date' => 'SAN request date',
						'san_connected_date' => 'SAN connected date',
    						));
	
      }

    // eeprom
    $eeprom = new dcpDataObjects_Dcp_procedure_verification_eeprom;
    if ( $eeprom->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_eeprom_header','Eeprom status');
    	$this->smarty->append('view_eeprom', array(
    						'mirror_boot_disk_defined' => $eeprom->mirror_boot_disk_defined,
						'auto_boot_on_error' => $eeprom->auto_boot_on_error,
						'auto_boot' => $eeprom->auto_boot,
    						));
    	$this->smarty->append('view_eeprom_labels', array(
    						'mirror_boot_disk_defined' => 'Mirror boot disk defined',
						'auto_boot_on_error' => 'Auto boot on error',
						'auto_boot' => 'Auto boot',
    						));
	
      }

    // cluster
    $cluster = new dcpDataObjects_Dcp_procedure_verification_cluster;
    if ( $cluster->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_cluster_header','Cluster status');
    	$this->smarty->append('view_cluster', array(
    						'cluster_eis_certified' => $cluster->cluster_eis_certified,
    						));
    	$this->smarty->append('view_cluster_labels', array(
    						'cluster_eis_certified' => 'EIS certified',
    						));
	
      }

    // x86
    $x86 = new dcpDataObjects_Dcp_procedure_verification_x86;
    if ( $x86->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_x86_header','X86 status');
    	$this->smarty->append('view_x86', array(
    						'fdisk_label_x86' => $x86->fdisk_label_x86,
    						));
    	$this->smarty->append('view_x86_labels', array(
    						'fdisk_label_x86' => 'Fdisk label',
    						));
	
      }

    // vlan
    $vlan = new dcpDataObjects_Dcp_procedure_verification_vlan;
    if ( $vlan->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_vlan_header','Vlan status');
    	$this->smarty->append('view_vlan', array(
    						'vlan_tagging' => $vlan->vlan_tagging,
    						));
	$this->smarty->append('view_vlan_labels', array(
						 'vlan_tagging' => 'Vlan tagging',
						 ));
      }

    // onswan
    $onswan = new dcpDataObjects_Dcp_procedure_verification_onswan;
    if ( $onswan->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_onswan_header','Onswan status');
    	$this->smarty->append('view_onswan', array(
    						'autofs_enabled' => $onswan->autofs_enabled,
    						'throughput_rate_verified' => $onswan->throughput_rate_verified,
    						));

    	$this->smarty->append('view_onswan_labels', array(						  
    						'autofs_enabled' => 'Autofs enabled',
    						'throughput_rate_verified' => 'Troughput rate verified',
    						));
      }

    // offswan
    $offswan = new dcpDataObjects_Dcp_procedure_verification_offswan;
    if ( $offswan->get("$this->sdesk_num") )
      {
	$this->smarty->assign('view_offswan_header','Offswan status');	
    	$this->smarty->append('view_offswan', array(
    						'moved_off_swan' => $offswan->moved_off_swan,
    						'autofs_disabled' => $offswan->autofs_disabled,
    						));
    	$this->smarty->append('view_offswan_labels', array(
    						'moved_off_swan' => 'Moved off Swan',
    						'autofs_disabled' => 'Autofs disabled',
    						));
	
      }
    
    $this->smarty->assign('TITLE','List DCPs');
    $this->smarty->assign('HEADER',"DCP #$dcp->sdesk_num");
    $this->smarty->assign('LINK',"/dcp/index.php?dcp_action=edit_dcp&sdesk_num=$dcp->sdesk_num");
    $this->smarty->assign('REGTOOL_LINK',"/dcp/index.php?dcp_action=edit_regtool&sdesk_num=$dcp->sdesk_num");
    $this->smarty->assign('REGTOOL_ASSIGN_LINK',"<b>Hostname (<a href='/dcp/index.php?dcp_action=assign_regtool&sdesk_num=$dcp->sdesk_num'>assign</a>)</b>");
  }

  function assignLabels()
  {
    $this->smarty->assign( 'dcp_labels', array(
					       'submit_time' => 'Submitted',
					       'sdesk_num'        => 'DCP',
					       'login' => 'Assigned to',     
					       'close_time'     => 'Closed',     
					       'user_sunid' => 'Customer SunId',
					       'usr_nm' => 'Customer',
					       'usr_dept' => 'Customer deptartment',
					       'priority' =>  'SDT priority',
					       'new_priority' => 'New Priority',
					       'request_status' => 'SDT request status',
					       'status' => 'Status',
					       'short_desc' => "DCP Short Description",
					       'hostname' => 'Hostname',
					       'note' => 'DCP process notes',
					       'regtool_prod_status_sdt' => 'Regtool status SDT#',
					       'gcn_num' => 'GCN number',
					       'os_load_date' => 'OS load date',
					       'netwrk_inferfaces_full_duplex' => 'Interface full duplex',
					       'netwrk_interfaces_any_faults' => 'Network interface faults',
					       'ipmp_configured' => 'IPMP configured',
					       'sendmail_verified' => 'Sendmail verified',
					       'sendmail_root_alias' => 'Sendmail root alias',         
					       'dumpadm_validated' => 'DUMPADM valid',
					       'backups_started' => 'Backups initiated',
					       'backups_sdt_num' => 'Backups SDT num',
					       'explorer_enabled' => 'Explorer enabled',
					       'scic_enabled' => 'SCIC enabled',
					       'sunmc_enabled' => 'SUNMC enabled',
					       'sunswat_enabled' => 'SUNSWAT enabled',
					       'helios_entry' => 'HELIOS entry',
					       'eis_radiance_case' => 'EIS Radiance case #',
					       'netcool_inventory_sdt' => 'Netcool inventiory SDT#',
					       'root_password_set' => 'Root password set',
					       'pts_applied' => 'PTS applied',
					       'fss_enabled' => 'FSS enabled',
					       'eds_tools_installed' => 'EDS tools installed',
					       'frmware_obp_validation' => 'Frmware OBP validation',
					       'frmware_hba_validation' => 'Frmware HBA validation',
					       'frmware_disks_validation' => 'Frmware Discs validation',
					       'frmware_alom_validation' => 'Frmware Alom validation',
					       'frmware_hypervisor_validation' => 'Frmware Hypervisor validation',
					       'lu_patch_update' => 'LU patch update',
					       'serial_number' => 'Serial number',
					       'hostid' => 'Hostid',
					       'division' => 'Division',
					       'model_name' => 'Model name',
					       'location_name' => 'Location name',
					       'netwrk_isr_name' => 'Network name',
					       'slevel_name' => 'Service level',
					       'op_env_name' => 'Operating environment',
					       'frmware_obp_name' => 'OBP level',
					       'frmware_alom_name' => 'Alom level',
					       'frmware_hypervisor_name' => 'Hypervisor level',
					       'os_name' => 'OS',
					       'os_version_name' => 'OS version',
					       'os_release_name' => 'OS release',
					       'processor_type_name' => 'Processor',
					       'regtool_prod_status' => 'Regtool prod status',
					       'console_hostname' => 'Console name',
					       'console_port' => 'Console port',
					       ));

  }
}


?>