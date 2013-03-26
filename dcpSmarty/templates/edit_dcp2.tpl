<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title></title>
</head>
{if $form_data.frozen}
	{assign var="lbl" value="class=frozen"}
{else}
	{assign var="lbl" value="class=thawed"}
{/if}
<body>
<!-- Display the copyright -->
<!-- <td style="font-size: 11px; color: navy; text-align: center;" colspan="4"> ©2004 Tiger Computing Ltd </td> -->


<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<form {$form_data.attributes}>  
<tr>
<td style="white-space:nowrap;background:#CCCCCC;color:#ffc;" align="left"><b>
    {$form_data.header.hdrTesting}
    {if $form_data.frozen}
      <font color="red"> (frozen)</font>
    {/if}
</b>      
</td>
</tr>  
<tr>
<td>
{section name=display loop=$view_dcp}
<b>Hostname</b>:
{$view_dcp[display].hostname} <br>
<b>Description</b>: {$view_dcp[display].short_desc}
</td>
</tr>
</table>
<p></p>


<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center"><b>{$dcp_labels.submit_time}</b></td>
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
{/section}      
<p></p>
<p></p>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">  
<td align="center"        <b>{$dcp_labels.regtool_prod_status}</b> </td>

<td align="center" {$lbl}><b>{$form_data.regtool_prod_status_sdt.label}</b>
<td align="center" {$lbl}><b>{$form_data.gcn_num.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.os_load_date.label}</b>
</td>
</tr>
<tr>
{section name=display loop=$view_dcp}  
<td>{$view_dcp[display].regtool_prod_status}</td>
{/section}
<td>{$form_data.regtool_prod_status_sdt.html}</td>
<td>{$form_data.gcn_num.html} </td>
<td>{$form_data.os_load_date.html} </td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">    
<td align="center" {$lbl}><b>{$form_data.note.label}</b> </td>
</tr>
<tr>
<td>{$form_data.note.html}</td>
</tr>
</tbody>
</table>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">    
<td align="center" {$lbl}><b>{$form_data.netwrk_inferfaces_full_duplex.label}</b>
</td>
<td align="center" {$lbl}><b>{$form_data.netwrk_interfaces_any_faults.label}</b>
</td>
<td align="center" {$lbl}><b>{$form_data.ipmp_configured.label}</b>
</td>
<td align="center" {$lbl}><b>{$form_data.sendmail_verified.label}</b>
</td>
<td align="center" {$lbl}><b>{$form_data.sendmail_root_alias.label}</b></td>
</tr>
<tr>
<td>{$form_data.netwrk_inferfaces_full_duplex.html} </td>
<td>{$form_data.netwrk_interfaces_any_faults.html} </td>
<td>{$form_data.ipmp_configured.html} </td>
<td>{$form_data.sendmail_verified.html} </td>
<td>{$form_data.sendmail_root_alias.html}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">    
<td align="center" {$lbl}><b>{$form_data.dumpadm_validated.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.backups_started.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.backups_sdt_num.label}</b> </td>
<td align="center" {$lbl}><b>{$form_data.explorer_enabled.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.scic_enabled.label}</b></td>
</tr>
<tr>
<td>{$form_data.dumpadm_validated.html} </td>
<td>{$form_data.backups_started.html} </td>
<td>{$form_data.backups_sdt_num.html}  </td>
<td>{$form_data.explorer_enabled.html} </td>
<td>{$form_data.scic_enabled.html}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">      
<td align="center" {$lbl}><b>{$form_data.sunmc_enabled.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.sunswat_enabled.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.helios_entry.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.eis_radiance_case.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.netcool_inventory_sdt.label}</b></td>
</tr>
<tr>
<td>{$form_data.sunmc_enabled.html} </td>
<td>{$form_data.sunswat_enabled.html} </td>
<td>{$form_data.helios_entry.html} </td>
<td>{$form_data.eis_radiance_case.html} </td>
<td>{$form_data.netcool_inventory_sdt.html}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">        
<td align="center" {$lbl}><b>{$form_data.root_password_set.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.pts_applied.label}</b> </td>
<td align="center" {$lbl}><b>{$form_data.fss_enabled.label}</b> </td>
<td align="center" {$lbl}><b>{$form_data.eds_tools_installed.label}</b> </td>
<td align="center" {$lbl}><b>{$form_data.lu_patch_update.label}</b> </td>
</tr>
<tr>
<td>{$form_data.root_password_set.html} </td>
<td>{$form_data.pts_applied.html} </td>
<td>{$form_data.fss_enabled.html} </td>
<td>{$form_data.eds_tools_installed.html} </td>
<td>{$form_data.lu_patch_update.html}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.frmware_obp_validation.label}</b></td>
<td align="center"
    {$lbl}><b>{$form_data.frmware_hba_validation.label}</b></td>
<td align="center"
    {$lbl}><b>{$form_data.frmware_disks_validation.label}</b></td>
<td align="center"
    {$lbl}><b>{$form_data.frmware_alom_validation.label}</b></td>

<td align="center" {$lbl}><b>{$form_data.frmware_hypervisor_validation.label}</b></td>
</tr>
<tr>
<td>{$form_data.frmware_obp_validation.html} </td>
<td>{$form_data.frmware_hba_validation.html} </td>
<td>{$form_data.frmware_disks_validation.html} </td>
<td>{$form_data.frmware_alom_validation.html} </td>
<td>{$form_data.frmware_hypervisor_validation.html}</td>
</tr>
</tbody>
</table>



<p></p>
<p>

{section name=display loop=$view_onswan}
</p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_onswan_header}</center>
<p></p>

<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.autofs_enabled.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.throughput_rate_verified.label}</b></td>  
</tr>
<tr>
<td>{$form_data.autofs_enabled.html}</td>
<td>{$form_data.throughput_rate_verified.html}</td>
</tr>
</tbody>
</table>
<p>
{/section}  
{section name=display loop=$view_offswan}

</p> 
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_offswan_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.moved_off_swan.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.autofs_disabled.label}</b></td>
</tr>
<tr>
<td>{$form_data.moved_off_swan.html}</td>
<td>{$form_data.autofs_disabled.html}</td>
</tr>
</tbody>
</table>
<p>
</p>
<p></p>
{/section}
{section name=display loop=$view_svm}
<p>
</p>
<p></p>
<center style="font-weight: bold;">{$view_svm_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.metadb_defined_on_two_disks.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.boot_from_mirror_enabled.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.lvm_md_tab_updated.label}</b></td>
</tr>
<tr>
<td>{$form_data.metadb_defined_on_two_disks.html}</td>
<td>{$form_data.boot_from_mirror_enabled.html}</td>
<td>{$form_data.lvm_md_tab_updated.html}</td>
</tr>
</tbody>
</table>
<p>
{/section}  
{section name=display loop=$view_zfs}
</p>
<p></p>
<center>
<p style="font-weight: bold;">{$view_zfs_header}</p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.boot_zpool.label}</b></td>  
</tr>
<tr>
<td>{$form_data.boot_zpool.html}</td>
</tr>
</tbody>
</table>
<p>
{/section}  
{section name=display loop=$view_clt}
</p>
<p>
</p>
<p></p>
<center style="font-weight: bold;">{$view_clt_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.cam_sheet_sent.label}</b></td>    
<td align="center" {$lbl}><b>{$form_data.cam_sheet_sent_date.label}</b></td>    
</tr>
<tr>
<td>{$form_data.cam_sheet_sent.html}</td>
<td>{$form_data.cam_sheet_sent_date.html}</td>
</tr>
</tbody>
</table>
<p>
</p>
{/section}
{section name=display loop=$view_san}
<p>
</p>
<p></p>
<center style="font-weight: bold;">{$view_san_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.san_cr_num.label}</b></td>
<td align="center"
    {$lbl}><b>{$form_data.san_switch_port_requested_date.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.san_connected_date.label}</b></td>    
</tr>
<tr>
<td>{$form_data.san_cr_num.html}</td>
<td>{$form_data.san_switch_port_requested_date.html}</td>
<td>{$form_data.san_connected_date.html}</td>
</tr>
</tbody>
</table>
<p>
</p>
{/section}
{section name=display loop=$view_eeprom}
<p>
</p>
<p></p>
<center style="font-weight: bold;">{$view_eeprom_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.mirror_boot_disk_defined.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.auto_boot_on_error.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.auto_boot.label}</b></td>
</tr>
<tr>
<td>{$form_data.mirror_boot_disk_defined.html}</td>
<td>{$form_data.auto_boot_on_error.html}</td>
<td>{$form_data.auto_boot.html}</td>
</tr>
</tbody>
</table>
<p>
</p>
{/section}
{section name=display loop=$view_cluster}
<p></p>
<p></p>
<center style="font-weight: bold;">{$view_cluster_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.cluster_eis_certified.label}</b></td>  
</tr>
<tr>
<td>{$form_data.cluster_eis_certified.html}</td>
</tr>
</tbody>
</table>
<p>
</p>
{/section}
{section name=display loop=$view_x86}
<p>
</p>
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_x86_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.fdisk_label_x86.label}</b></td>    
</tr>
<tr>
<td>{$form_data.fdisk_label_x86.html}</td>
</tr>
</tbody>
</table>
<p>
</p>
{/section}
{section name=display loop=$view_vlan}
<p>
</p>
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_vlan_header}</center>
<p></p>
<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.vlan_tagging.label}</b></td>      
</tr>
<tr>
<td>{$form_data.vlan_tagging.html}</td>
</tr>
</tbody>
</table>
<p>
</p>
<p></p>
{/section}
<p></p>
<p></p>
<p></p>
</center>
<p></p>
<table align="center" width="600" border="0" cellpadding="3"
       cellspacing="2">  
<tbody>
<!--<tr style="white-space;background:#CCCCCC;color:#ffc;">-->
<tr>
 <td align="center" colspan="4">
   <br>
          {$form_data.prevnext.html}
   <br>
        </td>
</tr>
{if $form_data.requirednote and not $form_data.frozen}
    <tr>
      <td>&nbsp;</td>
      <td valign="top">{$form_data.requirednote}</td>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
{/if}
</tbody>
</table>

</form>
</body></html>
