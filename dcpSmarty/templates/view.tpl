<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html><head>
</head>
<body>
{section name=display loop=$view_dcp}
<table align="center">
<tbody>
<tr>
<td align="center"><b>{$HEADER}</b>
<p></p>
</td>
</tr>
</tbody>
</table>
<center>
{$REGTOOL_ASSIGN_LINK}: {$view_dcp[display].hostname}
<br>  
<b>Description</b>: {$view_dcp[display].short_desc}
</center>
<!--
</td>
</tr>
</tbody>
</table>
-->
<br>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.submit_time}</b> </td>
<td align="center"><b>{$dcp_labels.priority}</b> </td>
<td align="center"><b>{$dcp_labels.request_status}</b> </td>
<td align="center"><b>{$dcp_labels.usr_nm}</b> </td>
<td align="center"><b>{$dcp_labels.login}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].submit_time} </td>
<td>{$view_dcp[display].priority} </td>
<td>{$view_dcp[display].request_status} </td>
<td>{$view_dcp[display].usr_nm} </td>
<td>{$view_dcp[display].login} </td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.regtool_prod_status}</b> </td>
<td align="center"><b>{$dcp_labels.regtool_prod_status_sdt}</b> </td>  
<td align="center"><b>{$dcp_labels.gcn_num}</b> </td>
<td align="center"><b>{$dcp_labels.os_load_date}</b> </td>  
</tr>
<tr>
<td>{$view_dcp[display].regtool_prod_status}</td>
<td>{$view_dcp[display].regtool_prod_status_sdt}</td>
<td>{$view_dcp[display].gcn_num} </td>
<td>{$view_dcp[display].os_load_date} </td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.note}</b> </td>    
</tr>
<tr>
<td>{$view_dcp[display].note} </td>
</tr>
</tbody>
</table>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.netwrk_inferfaces_full_duplex}</b> </td>
<td align="center"><b>{$dcp_labels.netwrk_interfaces_any_faults}</b> </td>
<td align="center"><b>{$dcp_labels.ipmp_configured}</b> </td>
<td align="center"><b>{$dcp_labels.sendmail_verified}</b> </td>
<td align="center"><b>{$dcp_labels.sendmail_root_alias}</b> </td>    
</tr>
<tr>
<td>{$view_dcp[display].netwrk_inferfaces_full_duplex} </td>
<td>{$view_dcp[display].netwrk_interfaces_any_faults} </td>
<td>{$view_dcp[display].ipmp_configured} </td>
<td>{$view_dcp[display].sendmail_verified} </td>
<td>{$view_dcp[display].sendmail_root_alias}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.dumpadm_validated}</b> </td>
<td align="center"><b>{$dcp_labels.backups_started}</b> </td>
<td align="center"><b>{$dcp_labels.backups_sdt_num}</b> </td>
<td align="center"><b>{$dcp_labels.explorer_enabled}</b> </td>
<td align="center"><b>{$dcp_labels.scic_enabled}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].dumpadm_validated} </td>
<td>{$view_dcp[display].backups_started} </td>
<td>{$view_dcp[display].backups_sdt_num} </td>
<td>{$view_dcp[display].explorer_enabled} </td>
<td>{$view_dcp[display].scic_enabled}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.sunmc_enabled}</b> </td>
<td align="center"><b>{$dcp_labels.sunswat_enabled}</b> </td>
<td align="center"><b>{$dcp_labels.helios_entry}</b> </td>
<td align="center"><b>{$dcp_labels.eis_radiance_case}</b> </td>
<td align="center"><b>{$dcp_labels.netcool_inventory_sdt}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].sunmc_enabled} </td>
<td>{$view_dcp[display].sunswat_enabled} </td>
<td>{$view_dcp[display].helios_entry} </td>
<td>{$view_dcp[display].eis_radiance_case} </td>
<td>{$view_dcp[display].netcool_inventory_sdt}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.root_password_set}</b> </td>
<td align="center"><b>{$dcp_labels.pts_applied}</b> </td>
<td align="center"><b>{$dcp_labels.fss_enabled}</b> </td>
<td align="center"><b>{$dcp_labels.eds_tools_installed}</b> </td>
<td align="center"><b>{$dcp_labels.lu_patch_update}</b> </td>  
</tr>
<tr>
<td>{$view_dcp[display].root_password_set} </td>
<td>{$view_dcp[display].pts_applied} </td>
<td>{$view_dcp[display].fss_enabled} </td>
<td>{$view_dcp[display].eds_tools_installed} </td>
<td>{$view_dcp[display].lu_patch_update}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.frmware_obp_validation}</b> </td>
<td align="center"><b>{$dcp_labels.frmware_hba_validation}</b> </td>
<td align="center"><b>{$dcp_labels.frmware_disks_validation}</b> </td>
<td align="center"><b>{$dcp_labels.frmware_alom_validation}</b> </td>
<td align="center"><b>{$dcp_labels.frmware_hypervisor_validation}</b> </td>  
</tr>
<tr>
<td>{$view_dcp[display].frmware_obp_validation} </td>
<td>{$view_dcp[display].frmware_hba_validation} </td>
<td>{$view_dcp[display].frmware_disks_validation} </td>
<td>{$view_dcp[display].frmware_alom_validation} </td>
<td>{$view_dcp[display].frmware_hypervisor_validation}</td>
</tr>
</tbody>
</table>
<p>{/section}</p>
<p>
{section name=display loop=$view_onswan}
</p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_onswan_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_onswan_labels[display].autofs_enabled}</b> </td>
<td align="center"><b>{$view_onswan_labels[display].throughput_rate_verified}</b> </td>
</tr>
<tr>
<td>{$view_onswan[display].autofs_enabled}</td>
<td>{$view_onswan[display].throughput_rate_verified}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
{section name=display loop=$view_offswan}
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_offswan_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_offswan_labels[display].moved_off_swan}</b> </td>
<td align="center"><b>{$view_offswan_labels[display].autofs_disabled}</b> </td>
</tr>
<tr>
<td>{$view_offswan[display].moved_off_swan}</td>
<td>{$view_offswan[display].autofs_disabled}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p></p>
<p>{section name=display loop=$view_svm}</p>
<p></p>
<center style="font-weight: bold;">{$view_svm_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_svm_labels[display].metadb_defined_on_two_disks}</b> </td>
<td align="center"><b>{$view_svm_labels[display].boot_from_mirror_enabled}</b> </td>
<td align="center"><b>{$view_svm_labels[display].lvm_md_tab_updated}</b> </td>
</tr>
<tr>
<td>{$view_svm[display].metadb_defined_on_two_disks}</td>
<td>{$view_svm[display].boot_from_mirror_enabled}</td>
<td>{$view_svm[display].lvm_md_tab_updated}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
{section name=display loop=$view_zfs}
<p></p>
<center>
<p style="font-weight: bold;">{$view_zfs_header}</p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_zfs_labels[display].boot_zpool}</b> </td>
</tr>
<tr>
<td>{$view_zfs[display].boot_zpool}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_clt}</p>
<p></p>
<center style="font-weight: bold;">{$view_clt_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_clt_labels[display].cam_sheet_sent}</b> </td>
<td align="center"><b>{$view_clt_labels[display].cam_sheet_sent_date}</b> </td>
</tr>
<tr>
<td>{$view_clt[display].cam_sheet_sent}</td>
<td>{$view_clt[display].cam_sheet_sent_date}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_san}</p>
<p></p>
<center style="font-weight: bold;">{$view_san_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_san_labels[display].san_cr_num}</b> </td>
<td align="center"><b>{$view_san_labels[display].san_switch_port_requested_date}</b> </td>
<td align="center"><b>{$view_san_labels[display].san_connected_date}</b> </td>
</tr>
<tr>
<td>{$view_san[display].san_cr_num}</td>
<td>{$view_san[display].san_switch_port_requested_date}</td>
<td>{$view_san[display].san_connected_date}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_eeprom}</p>
<p></p>
<center style="font-weight: bold;">{$view_eeprom_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_eeprom_labels[display].mirror_boot_disk_defined}</b> </td>
<td align="center"><b>{$view_eeprom_labels[display].auto_boot_on_error}</b> </td>
<td align="center"><b>{$view_eeprom_labels[display].auto_boot}</b> </td>
</tr>
<tr>
<td>{$view_eeprom[display].mirror_boot_disk_defined}</td>
<td>{$view_eeprom[display].auto_boot_on_error}</td>
<td>{$view_eeprom[display].auto_boot}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_cluster}
</p>
<p>
<center style="font-weight: bold;">{$view_cluster_header}</center>
<p></p>
</p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_cluster_labels[display].cluster_eis_certified}</b> </td>
</tr>
<tr>
<td>{$view_cluster[display].cluster_eis_certified}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_x86}
</p>
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_x86_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_x86_labels[display].fdisk_label_x86}</b> </td>
</tr>
<tr>
<td>{$view_x86[display].fdisk_label_x86}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_vlan}
</p>
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_vlan_header}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$view_vlan_labels[display].vlan_tagging}</b> </td>
</tr>
<tr>
<td>{$view_vlan[display].vlan_tagging}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p></p>
<p></p>
<p></p>
<p></p>
</center>
<p></p>
<table align="center">
<tbody>
<tr>
<td align="center"> <input name="vol" value="Edit" onclick="javascript:location.href='{$LINK}';" type="button"> </td>
</tr>
</tbody>
</table>
</body></html>
