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

<table align="center" width="600" border="1" cellpadding="3"
       cellspacing="2" bgcolor="#EEEEEE">
<form {$form_data.attributes}>    
<tr>
<td style="white-space:nowrap;background:#CCCCCC;color:#ffc;"
    align="left">
<b>
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
{$view_dcp[display].hostname} <b><br>
</b>
</td>
</tr>
</table>
<p></p>

<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">  
<td align="center"><b>{$dcp_labels.serial_number}</b> </td>
<td align="center"><b>{$dcp_labels.hostid}</b> </td>
<td align="center"><b>{$dcp_labels.division}</b> </td>
<td align="center"><b>{$dcp_labels.status}</b> </td>
<td align="center"><b>{$dcp_labels.regtool_prod_status}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].serial_number} </td>
<td>{$view_dcp[display].hostid} </td>
<td>{$view_dcp[display].division} </td>
<td>{$view_dcp[display].status} </td>
<td>{$view_dcp[display].regtool_prod_status} </td>
</tr>
</tbody>
</table>
<p></p>

<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">  
<td align="center"><b>{$dcp_labels.model_name}</b> </td>  
<td align="center"><b>{$dcp_labels.location_name}</b> </td>
<td align="center"><b>{$dcp_labels.netwrk_isr_name}</b> </td>
<td align="center"<b>{$dcp_labels.slevel_name}</b> </td>
<td align="center"<b>{$dcp_labels.op_env_name}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].model_name}</td>
<td>{$view_dcp[display].location_name} </td>
<td>{$view_dcp[display].netwrk_isr_name} </td>
<td>{$view_dcp[display].slevel_name}</td>
<td>{$view_dcp[display].op_env_name}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center" {$lbl}><b>{$form_data.processor_type_id.label}</b></td>  
<!-- {section name=display loop=$view_dcp} -->  
<td align="center"><b>{$dcp_labels.os_name}</b> </td>
<td align="center"><b>{$dcp_labels.os_version_name}</b> </td>
<!-- {/section} -->
<td align="center" {$lbl}><b>{$form_data.os_release_id.label}</b></td>
</tr>
<tr>
<td>{$form_data.processor_type_id.html} </td>  
<!-- {section name=display loop=$view_dcp} -->    
<td>{$view_dcp[display].os_name} </td>
<td>{$view_dcp[display].os_version_name} </td>

<td>{$form_data.os_release_id.html} </td>
</tr>
</tbody>
</table>
<p></p>
<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center"{$lbl}><b>{$form_data.frmware_obp_id.label}</b></td>
<td align="center" {$lbl}><b>{$form_data.frmware_alom_id.label}</b></td>  
</tr>
<tr>
<td>{$form_data.frmware_obp_id.html} </td>
<td>{$form_data.frmware_alom_id.html} </td>  
</tr>
</tbody>
</table>

<p>
  {section name=display loop=$frmware_hypervisor}
</p>

<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center"{$lbl}><b>{$form_data.frmware_hypervisor_id.label}</b></td>    
</tr>
<tr>
<td>{$form_data.frmware_hypervisor_id.html} </td>  
</td>
</tr>
</tbody>
</table>


<p>
    {/section}
<!-- {/section} -->
<p>{section name=display loop=$frmware_disks max=1}</p>

<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center"{$lbl}><b>{$form_data.frmware_disks_id.label}</b></td>
</tr>
<tr>
<td>{$form_data.frmware_disks_id.html} </td>  
</tr>
</tbody>
</table>
<p>{/section}</p>


{section name=display loop=$frmware_hba max=1}
<table align="center" width="600" border="1" cellpadding="3" cellspacing="2" bgcolor="#EEEEEE">
<tbody>
<tr style="white-space;background:#CCCCCC;color:#ffc;">
<td align="center"{$lbl}><b>{$form_data.frmware_hba_id.label}</b></td>      
</tr>
<tr>
<td>{$form_data.frmware_hba_id.html} </td>    
</td>
</tr>
</tbody>
</table>
{/section}
<!-- {/section} -->
<p></p>
<p></p>
<p></p>
</center>
<p></p>
<table align="center" width="600" border="0" cellpadding="3"
       cellspacing="2">  
<tbody>
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


</body></html>
