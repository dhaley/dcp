<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Tmansitional//EN">
<html>
<head>
</head>
<body>

{section name=display loop=$view_dcp}

 <h2>
    {$form_data.header.hdrTesting}
  </h2>

<table align="center">
<tbody>

<!-- <form {$form_data.attributes> -->

<tr>
<td align="center">
<b>{$HEADER}</b>
    <!-- Display the fields -->
    <table>
      <tbody><tr>
        <th>{$form_data.txtFirstName.label}</th>
        <td>{$form_data.txtFirstName.html}</td>
        <th>{$form_data.txtLastName.label}</th>
        <td>{$form_data.txtLastName.html}</td>
      </tr>
      <tr>
        <th>{$form_data.txtAge.label}</th>
        <td>{$form_data.txtAge.html}</td>
        <th>{$form_data.txtTelephone.label}</th>
        <td>{$form_data.txtTelephone.html}</td>
      </tr>
      <!-- Display the buttons -->
      <tr>
        <td colspan="4" align="center">
<!--          {$form_data.btnClear.html}&nbsp;{$form_data.btnSubmit.html} -->
          {$form_data._qf_page7_back.html}&nbsp;{$form_data._qf_page7_back.html}
        </td>
      </tr>
      <!-- Display the copyright -->
      <tr>
        <td style="font-size: 11px; color: navy; text-align: center;" colspan="4">
          ©2004 Tiger Computing Ltd
        </td>
      </tr>
    </tbody></table>
<p></p>
</td>
</tr>
</tbody>
</table>
<!-- <table width="500" border="1" align="center">
<tbody>
<tr>
<td align="center"><b>{$data4}</b> </td>
</tr>
<tr>
<td>
-->
<center><b>Hostname</b>:
{$view_dcp[display].HOSTNAME} <br>
<b>Description</b>: {$view_dcp[display].DCP_SHORT_DESC}
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
<td align="center"><b>{$data0}</b> </td>
<td align="center"><b>{$data1}</b> </td>
<td align="center"><b>{$data2}</b> </td>
<td align="center"><b>{$data3}</b> </td>
<td align="center"><b>{$data54}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].SUBMIT_TIME} </td>
<td>{$view_dcp[display].DCP_PRIORITY} </td>
<td>{$view_dcp[display].DCP_REQUEST_STATUS} </td>
<td>{$view_dcp[display].CUSTOMER_NAME} </td>
<td>{$view_dcp[display].ASSIGNED_TO} </td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data6}</b> </td>
<td align="center"><b>{form_data.gcn_num.label}</b> </td>
<td align="center"><b>{$data8}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].REGTOOL_PROD_STATUS}
</td>
<td>{$form_data.gcn_num.html} </td>
<td>{$view_dcp[display].OS_LOAD_DATE} </td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data57}</b> </td>
</tr>
<tr>
<td>{$view_dcp[display].OS_LOAD_DATE} </td>
</tr>
</tbody>
</table>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data10}</b> </td>
<td align="center"><b>{$data11}</b> </td>
<td align="center"><b>{$data12}</b> </td>
<td align="center"><b>{$data13}</b> </td>
<td><strong>{$data14}</strong></td>
</tr>
<tr>
<td>{$view_dcp[display].NETWRK_INTERFACE_FULL_DUPLEX} </td>
<td>{$view_dcp[display].NETWRK_INTERFACE_ANY_FAULTS} </td>
<td>{$view_dcp[display].IPMP_CONFIG} </td>
<td>{$view_dcp[display].SENDMAIL_VERIFIED} </td>
<td>{$view_dcp[display].SENDMAIL_ROOT_ALIAS}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data15}</b> </td>
<td align="center"><b>{$data16}</b> </td>
<td align="center"><b>{$data17}</b> </td>
<td align="center"><b>{$data18}</b> </td>
<td align="center"><b>{$data19}</b></td>
</tr>
<tr>
<td>{$view_dcp[display].DUMPAD_VALID} </td>
<td>{$view_dcp[display].BKUPS_BEGIN} </td>
<td>{$view_dcp[display].BKUPS_SDT_NUM} </td>
<td>{$view_dcp[display].EXPLO_ENABLE} </td>
<td>{$view_dcp[display].SCIC_ENABLE}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data20}</b> </td>
<td align="center"><b>{$data21}</b> </td>
<td align="center"><b>{$data22}</b> </td>
<td align="center"><b>{$data23}</b> </td>
<td><strong>{$data24}</strong></td>
</tr>
<tr>
<td>{$view_dcp[display].SUNMC_ENABLE} </td>
<td>{$view_dcp[display].SUNSWAT_ENABLE} </td>
<td>{$view_dcp[display].HELIOS_ENTRY} </td>
<td>{$view_dcp[display].EIS_RADIANCE_CASE} </td>
<td>{$view_dcp[display].NETCOOL_INVENTORY_SDT}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data25}</b> </td>
<td align="center"><b>{$data26}</b> </td>
<td align="center"><b>{$data27}</b> </td>
<td align="center"><b>{$data28}</b> </td>
<td><strong>{$data29}</strong></td>
</tr>
<tr>
<td>{$view_dcp[display].ROOT_PASSWD_SET} </td>
<td>{$view_dcp[display].PTS_APPLIED} </td>
<td>{$view_dcp[display].FSS_ENABLED} </td>
<td>{$view_dcp[display].EDS_TOOLS_INSTALL} </td>
<td>{$view_dcp[display].LU_PATCH_UPDATE}</td>
</tr>
</tbody>
</table>
<p></p>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data31}</b> </td>
<td align="center"><b>{$data31}</b> </td>
<td align="center"><b>{$data32}</b> </td>
<td align="center"><b>{$data33}</b> </td>
<td><strong>{$data34}</strong></td>
</tr>
<tr>
<td>{$view_dcp[display].FRMWARE_OBP_VALIDATE} </td>
<td>{$view_dcp[display].FRMWARE_HBA_VALIDATE} </td>
<td>{$view_dcp[display].FRMWARE_DISKS_VALIDATE} </td>
<td>{$view_dcp[display].FRMWARE_ALOM_VALIDATE} </td>
<td>{$view_dcp[display].FRMWARE_HYPERVISOR_VALIDATE}</td>
</tr>
</tbody>
</table>
<p>{/section}</p>
<p>
{section name=display loop=$view_onswan}
</p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_onswan[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data73}</b> </td>
<td align="center"><b>{$data74}</b> </td>
</tr>
<tr>
<td>{$view_onswan[display].ONSWAN_AUTOFS_ENABLED}</td>
<td>{$view_onswan[display].ONSWAN_THROUGHPUT_RATE}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
{section name=display loop=$view_offswan}
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_offswan[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data75}</b> </td>
<td align="center"><b>{$data76}</b> </td>
</tr>
<tr>
<td>{$view_offswan[display].OFFSWAN_MOVED}</td>
<td>{$view_offswan[display].OFFSWAN_AUTOFS_DISABLED}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p></p>
<p>{section name=display loop=$view_svm}</p>
<p></p>
<center style="font-weight: bold;">{$view_svm[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data58}</b> </td>
<td align="center"><b>{$data59}</b> </td>
<td align="center"><b>{$data60}</b> </td>
</tr>
<tr>
<td>{$view_svm[display].SVM_METADB_TWO_DISKS}</td>
<td>{$view_svm[display].SVM_BOOT_MIRROR}</td>
<td>{$view_svm[display].SVM_MD_TAB}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
{section name=display loop=$view_zfs}
<p></p>
<center>
<p style="font-weight: bold;">{$view_zfs[display].HEADER}</p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data61}</b> </td>
</tr>
<tr>
<td>{$view_zfs[display].ZFS_BOOT_ZPOOL}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_clt}</p>
<p></p>
<center style="font-weight: bold;">{$view_clt[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data62}</b> </td>
<td align="center"><b>{$data63}</b> </td>
</tr>
<tr>
<td>{$view_clt[display].CAM_SHEET_SENT}</td>
<td>{$view_clt[display].CAM_SHEET_SENT_DATE}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_san}</p>
<p></p>
<center style="font-weight: bold;">{$view_san[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data64}</b> </td>
<td align="center"><b>{$data65}</b> </td>
<td align="center"><b>{$data66}</b> </td>
</tr>
<tr>
<td>{$view_san[display].SAN_CR_NUM}</td>
<td>{$view_san[display].SAN_REQUEST_DATE}</td>
<td>{$view_san[display].SAN_CONNECTED_DATE}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_eeprom}</p>
<p></p>
<center style="font-weight: bold;">{$view_eeprom[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data67}</b> </td>
<td align="center"><b>{$data68}</b> </td>
<td align="center"><b>{$data69}</b> </td>
</tr>
<tr>
<td>{$view_eeprom[display].MIRROR_BOOT_DEFINED}</td>
<td>{$view_eeprom[display].AUTO_BOOT_ON_ERROR}</td>
<td>{$view_eeprom[display].AUTO_BOOT}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_cluster}
</p>
<p></p>
<p style="font-weight: bold;">{$view_cluster[display].HEADER}</p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data70}</b> </td>
</tr>
<tr>
<td>{$view_cluster[display].CLUSTER_EIS_CERTIFIED}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_x86}
</p>
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_x86[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data71}</b> </td>
</tr>
<tr>
<td>{$view_x86[display].X86_LABEL}</td>
</tr>
</tbody>
</table>
<p>
{/section}</p>
<p>{section name=display loop=$view_vlan}
</p>
<p></p>
<p style="font-weight: bold;"></p>
<center style="font-weight: bold;">{$view_vlan[display].HEADER}</center>
<p></p>
<table align="center" border="1" width="500">
<tbody>
<tr>
<td align="center"><b>{$data72}</b> </td>
</tr>
<tr>
<td>{$view_vlan[display].VLAN_TAGGING}</td>
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
<!-- </form> -->
</tbody>
</table>
</body></html>
