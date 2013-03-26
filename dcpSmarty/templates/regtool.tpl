<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html><head>
</head>
<body>


<table align="center">
<tbody>
<tr>
<td align="center"><b>{$HEADER}</b>
<p></p>
</td>
</tr>
</tbody>
</table>

{section name=display loop=$view_dcp}
<center>
{$REGTOOL_ASSIGN_LINK}: {$view_dcp[display].hostname}
<br>
</center>
{/section}


<p>{section name=display loop=$view_regtool}</p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.serial_number}</b> </td>
<td align="center"><b>{$dcp_labels.hostid}</b> </td>
<td align="center"><b>{$dcp_labels.division}</b> </td>
<td align="center"><b>{$dcp_labels.status}</b> </td>
<td align="center"><b>{$dcp_labels.regtool_prod_status}</b> </td>
</tr>
<tr>
<td>{$view_regtool[display].serial_number} </td>
<td>{$view_regtool[display].hostid} </td>
<td>{$view_regtool[display].division} </td>
<td>{$view_regtool[display].status} </td>
<td>{$view_regtool[display].regtool_prod_status} </td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<p></p>
<table style="width: 500px; text-align: left; margin-left: auto; margin-right: auto;" border="1">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.model_name}</b> </td>  
<td align="center"><b>{$dcp_labels.location_name}</b> </td>
<td align="center"><b>{$dcp_labels.netwrk_isr_name}</b> </td>
<td align="center"<b>{$dcp_labels.slevel_name}</b> </td>
<td align="center"<b>{$dcp_labels.op_env_name}</b> </td>
</tr>
<tr>
<td>{$view_regtool[display].model_name}</td>
<td>{$view_regtool[display].location_name} </td>
<td>{$view_regtool[display].netwrk_isr_name} </td>
<td>{$view_regtool[display].slevel_name}</td>
<td>{$view_regtool[display].op_env_name}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.processor_type_name}</b> </td>
<td align="center"><b>{$dcp_labels.os_name}</b> </td>
<td align="center"><b>{$dcp_labels.os_version_name}</b> </td>
<td align="center"><b>{$dcp_labels.os_release_name}</b> </td>    
</tr>
<tr>
<td>{$view_regtool[display].processor_type_name} </td>
<td>{$view_regtool[display].os_name} </td>
<td>{$view_regtool[display].os_version_name} </td>
<td>{$view_regtool[display].os_release_name} </td>
</tr>
</tbody>
</table>
<p></p>

<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$dcp_labels.frmware_obp_name}</b> </td>
<td align="center"><b>{$dcp_labels.frmware_alom_name}</b> </td>
</tr>
<tr>
<td>{$view_regtool[display].frmware_obp_name} </td>
<td>{$view_regtool[display].frmware_alom_name} </td>
</tr>
</tbody>
</table>
<p>{/section}</p>

<p>{section name=display loop=$frmware_hypervisor}</p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$frmware_hypervisor_labels[display].frmware_hypervisor_name}</b> </td>
</tr>
<tr>
<td>{$frmware_hypervisor[display].frmware_hypervisor_name}
</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p></p>



<p>{section name=display loop=$frmware_disks}</p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$frmware_disks_labels[display].frmware_disks_name}</b> </td>
</tr>
<tr>
<td>{$frmware_disks[display].frmware_disks_name} </td>
</tr>
</tbody>
</table>
<p>{/section}</p>


{section name=display loop=$frmware_hba}
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$frmware_hba_labels[display].frmware_hba_name}</b> </td>
</tr>
<tr>
<td>{$frmware_hba[display].frmware_hba_name}
</td>
</tr>
</tbody>
</table>
<br>
{/section}
<p>{section name=display loop=$view_regtool}</p>
<table align="center">
<tbody>
<tr>
<td align="center"> <input name="vol" value="Edit" onclick="javascript:location.href='{$REGTOOL_LINK}';" type="button"> </td>
</tr>
</tbody>
</table>
{/section}

</body></html>
