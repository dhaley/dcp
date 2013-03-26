<?php

require_once "HTML/QuickForm/Page.php";
require_once 'HTML/QuickForm/advmultiselect.php';  // <-- DO NOT forget it
require('/opt/coolstack/php5/lib/php/Smarty/Smarty.class.php');
require_once "dcpSmarty/dcpProcedure.php";
require_once 'dcpDatabase/dcpSun_ServerOsSelections.php';
require_once 'dcpDatabase/dcpSun_ServerSelections.php';

// Class representing a form
class dcpPage extends HTML_QuickForm_Page
{
  var $tabs;
  var $smarty;
  var $dcp_smarty;
  var $_smarty_template = FALSE;
  
  
    // function buildForm()
    // {
    //     $this->_formBuilt = true;

    //     // Add some elements to the form
    //     $this->addElement('header', null, 'dcpPage base class');
    // }

    function buildPageHeading($dcp_action = 'new') 
    {
      echo <<< HTML_HEADER
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-15">
<title>DCP PSC Tracker</title>
<script type="text/javascript" src="http://psc.central.sun.com:9000/dcp/overlib/overlib.js"><!-- overLIB (c) Erik Bosrup -->
</script>
</head>
<body>
<div id="overDiv" style="position:absolute; visibility:hidden; z-index:1000;"></div>

HTML_HEADER;
      $this->add_css();
      echo "<div style='width:1000px;'\n";      
      echo $this->start_box('PSC DCP Tracker');
      $this->page_menu($dcp_action);
      echo $this->end_box();
      echo "</div>\n";
      echo "<br>\n";
      //      $this->addElement('html', "$HTML");
    }

    function buildPageFooter()
    {
      $HTML .= end_box();
      $HTML .= "</div>\n";
      $this->addElement('html', "$HTML");
    }

    function add_css ()
    {
      echo <<< END
<style type="text/css">
body {
  background-color: #FFF;
  font-family: Verdana, Arial, helvetica;
  font-size: 10pt;
}

.menu-inactive, .menu-active {
	padding: 2px;
	padding-left: 20px;
	font-family: arial, verdana;
}
.menu-inactive { background: #ddd; }
.menu-active { background: #000; font-weight: bold; }
.menu-inactive a { text-decoration: none; }
.menu-active a { color: white; text-decoration: none; }

.box {
   font-family: arial, verdana, sans-serif;
}
.box-title {
   font-size: small;
   font-weight: bold;
   color: white;
   background: #000063;
   text-align: center;
}
.box-content-container {
   background: #000063;
}
.box-content {
   background: white;
   font-size: x-small;
   padding: 5px;
}

.tab {
    border-bottom: 1px solid black;
    text-align: center;
    font-family: arial, verdana;
  }
.tab-active {
    border-left: 1px solid black;
    border-top: 1px solid black;
    border-right: 1px solid black;
    text-align: center;
    font-family: arial, verdana;
    font-weight: bold;
  }
.tab-content {
    padding: 5px;
    border-left: 1px solid black;
    border-right: 1px solid black;
    border-bottom: 1px solid black;
  }

th {
  text-align: right;
}
.frozen {
 color: red;
}
.thawed {
 color: green;
}


table.pool {
  border: 0;
  background-color: lightyellow;
}
table.pool th {
  font-size: 80%;
  font-style: italic;
  text-align: center;
}
table.pool select {
  background-color: lightblue;
}
 
.inputCommand {
    background-color: #d0d0d0;
    border: 1px solid #7B7B88;
    width: 7em;
    margin-bottom: 2px;
}


</style>

END;
  }

  function page_menu($dcp_action) {
    echo "<table cellspaceing='0' cellpadding='5'>\n";
    echo "<tr>\n";
    //  echo "<td width='150' valign='top'>\n";
    echo "<td width='1000' valign='top'>\n";  
    echo "<table width='100%'>\n";
    echo "<tr>\n";
    //    $this->menu_item('Main Menu', 'http://psc.central.sun.com:9000/dcp', 'on');  
    // $this->menu_item('New Dcp', 'http://psc.central.sun.com:9000/dcp', "$dcp_action");
    // $this->menu_item('View Single DCP', 'http://psc.central.sun.com:9000/dcp/dcp_edit.php', "$dcp_action");
    // $this->menu_item('View All DCPS', 'http://psc.central.sun.com:9000/dcp/dcp_view_all.php', "$dcp_action");
    // $this->menu_item('Edit DCP', 'http://psc.central.sun.com:9000/dcp/dcp_edit2.php', "$dcp_action");
    // $this->menu_item('Delete DCP', 'http://psc.central.sun.com:9000/dcp/dcp_edit2.php', "$dcp_action");
    $this->menu_item('Search for DCP/<br>Create or Update DCP', 'new', "$dcp_action");    
    //    $this->menu_item('Search for DCP', 'search', "$dcp_action");
    //    $this->menu_item('View Single DCP', 'view_single_dcp', "$dcp_action");
    $this->menu_item('View All DCPS (productionalization)', 'view_all_dcps_procedure', "$dcp_action");
    $this->menu_item('View All DCPS (infrastructure)', 'view_all_dcps', "$dcp_action");
    $this->menu_item('View All DCPS (resources)', 'view_all_dcps_business', "$dcp_action");
    //    $this->menu_item('Edit DCP', 'edit_dcp', "$dcp_action");
    //    $this->menu_item('Delete DCP', 'delete_dcp', "$dcp_action");
    echo "</tr>\n";
    echo "</table>\n";
    //  echo "</td>\n";
    //  echo "<td width='600' valign='top'>\n";
    //  echo "</td>\n";
    echo "</tr>\n";
    echo "</table>";
  }


  function menu_item($title, $action, $dcp_action ) {
    $class = "menu-inactive";
    if ( $action == $dcp_action )
      $class = "menu-active";
    //  echo "<tr><td class='$class'>";
    echo "<td class='$class'>";  
    //    echo "<a href=$url>$title</a>";
    echo "<a href='http://psc.central.sun.com:9000/dcp/index.php?dcp_action=$action'>$title</a>";    
    echo "</td>";
  }

function start_box( $name ) {
  echo <<< END
<table cellspacing="0" cellpadding="0" class="box">
<tr><td>

<table cellspacing="0" cellpadding="0" width="100%" class="box-title">
<tr><td width="20" height="20"><img src="/dcp/blue_ul.png" /></td>
<td>$name</td>
<td width="20" height="20"><img src="/dcp/blue_ur.png"></td></tr></table>
</td></tr>

<tr><td>
<table width="100%" cellspacing="2" cellpadding="0"
  class="box-content-container">
<tr><td class="box-content">
END;
  
}

 function end_box() {

  echo <<< END
</td></tr></table>
<tr><td>

<table cellspacing="0" cellpadding="0" width="100%" class="box-title">
<tr><td width="20" height="20"><img src="/dcp/blue_ll.png" /></td>
<td>&nbsp;</td>
<td width="20" height="20"><img src="/dcp/blue_lr.png"></td></tr></table>

</td></tr></table>
END;
 }

function endtab()
{
  $this->tabs[ count( $this->tabs ) - 1 ][ 'text' ] = $text;
}

 function tab( $title, $smarty, $tpl )
{
  if ( count( $this->tabs ) > 0 ) // has a count of 1
    $this->endtab();

  $this->tabs []= array(
    title => $title,
    text => "",
    smarty => $smarty,
    tpl => $tpl
  );
}

 function tabs_end($sdesk_num)
{
  $this->endtab();

  $index = 0;
  if ( $_GET['tabindex'] )
    $index = $_GET['tabindex'];

  echo "<table width='100%' cellspacing='0' cellpadding='0'> <tr>\n";
  $baseuri = $_SERVER['REQUEST_URI'];
  $baseuri = preg_replace( "/\?.*$/", "", $baseuri );
  $curindex = 0;
  foreach( $this->tabs as $tab )
  {
    $class = "tab";
    if ( $index == $curindex )
      $class ="tab-active";
    echo "<td class=$class>\n";
    echo "<a href=$baseuri?dcp_action=view_dcp&sdesk_num=$sdesk_num&tabindex=$curindex>\n";
    echo( $tab['title'] );
    echo "</a>\n";
    echo "</td>\n";
    $curindex += 1;
  }
  echo "</tr>\n";
  echo "<tr><td class='tab-content' colspan='";
  echo( count( $this->tabs ) + 1 );
  echo "'>\n";
  echo( $this->tabs[$index ]['text'] );
  $smarty = $this->tabs[$index ]['smarty'];
  $tpl = $this->tabs[$index ]['tpl'];
  $smarty->display("$tpl");
  echo "</td></tr>\n";
  echo "</table>\n";
}

 function displayErrorPage($message,$template='error.tpl') {
   $smarty = $this->createSmarty;
   $smarty->assign('message',$message);
   $smarty->display($template);
 }

function createSmarty ()
{
  // Smarty
  $smarty = new Smarty;
  $smarty->template_dir = '/opt/coolstack/apache2/htdocs/smarty/templates';
  $smarty->compile_dir = '/opt/coolstack/apache2/htdocs/smarty/templates_c';
  $smarty->cache_dir = '/opt/coolstack/apache2/htdocs/smarty/cache';
  $smarty->config_dir = '/opt/coolstack/apache2/htdocssmarty/configs';
  return $smarty;
}

function action($action,$actionName)
{
  $values = $this->controller->exportValues();
  echo '<pre>';
  var_dump($values);
  echo '</pre>';
}

function dcpVal($var)
{
  $data="";
  foreach(explode('.',$var) as $v)
    {
      if (empty($data))
	{
	  $data = $this->smarty->get_template_vars($v);
	}
      else 
	{
	  $data = $data[$v];
	}
    }
  return $data;

}

  function buildEditForm ($sdesk_num)
  {
    $this->sdesk_num = $sdesk_num;
    $this->smarty = $this->createSmarty();

    $dcpProcedure_Smarty = new dcpProcedure($this->smarty);
    $dcpProcedure_Smarty->loadSmarty($this->sdesk_num);
    $this->dcp_smarty = $dcpProcedure_Smarty->getSmarty(); // fully loaded Smarty	
    $dcp_labels = $this->dcpVal('dcp_labels');
    $dcp_array = $this->dcpVal('view_dcp.0');
    
    $this->addElement('header', 'hdrTesting', "Please update the status of DCP #$sdesk_num");
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    $this->addElement('text', 'regtool_prod_status_sdt', $dcp_labels['regtool_prod_status_sdt'],  array('size' => 7, 'maxlength' => 7)); 
    $this->addRule('regtool_prod_status_sdt', 'ERROR: Incorrect data type', 'numeric');
    $this->addRule('regtool_prod_status_sdt', 'SDESK number must be 7 digits:', 'rangelength', array(7,7) );
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    $this->addElement('text', 'gcn_num', $dcp_labels['gcn_num'], array('size' => 6, 'maxlength' => 6));		
    $this->addRule('gcn_num', 'ERROR: Incorrect data type', 'numeric');
    $this->addRule('gcn_num', 'GCN number must be 6 digits:', 'rangelength', array(6,6) );
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    $this->addElement('date', 'os_load_date', $dcp_labels['os_load_date'], array('format' => 'd-M-Y', 'minYear' => 2008, 'maxYear' => date('Y')));
    $this->addElement('textarea', 'note', $dcp_labels['note'], array('cols'=>80, 'rows'=>4, 'size' => 144, 'maxlength' => 144)); // size 144
    //	$this->addRule('note', 'Note can only be 144 characters long', 'rangelength', array(144,144) );
    
    $this->addElement('text', 'backups_sdt_num', $dcp_labels['backups_sdt_num'], array('size' => 10, 'maxlength' => 10));
    $this->addRule('backups_std_num', 'ERROR: Incorrect data type', 'numeric');
    $this->addRule('backups_std_num', 'Backups SDESK number must be 7 digits:', 'rangelength', array(7,7) );
    
    $this->addElement('text', 'eis_radiance_case', $dcp_labels['eis_radiance_case'], array('size' => 10, 'maxlength' => 10));
    $this->addRule('eis_radiance_case', 'ERROR: Incorrect data type', 'numeric');
    $this->addRule('eis_radiance_case', 'EIS radiance case number must be 8 digits:', 'rangelength', array(8,8) );
    
    $this->addElement('text', 'netcool_inventory_sdt', $dcp_labels['netcool_inventory_sdt'], array('size' => 10, 'maxlength' => 10));
    $this->addRule('netcool_inventory_sdt', 'ERROR: Incorrect data type', 'numeric');
    $this->addRule('netcool_inventory_sdt', 'Netcool inventory SDESK number must be 7 digits:', 'rangelength', array(7,7) );

    $defaults_array = array('note', 'netcool_inventory_sdt', 'eis_radiance_case', 'backups_sdt_num', 'os_load_date', 'gcn_num', 'regtool_prod_status_sdt' );

    foreach ($defaults_array as $col)
      {
	if ( $dcp_array["$col"] != 0 )
	  {
	    $this->setDefaults(array(
				     "$col" => $dcp_array["$col"],
				 ));
	  }
      }

    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    $choice_tables = array('netwrk_interfaces_any_faults' => 'Any network interface faults', 'netwrk_inferfaces_full_duplex' => 'Are network interfaces full duplex', 'ipmp_configured' => 'IPMP configured', 'sendmail_verified' => 'Sendmail verified', 'sendmail_root_alias' => 'Root mail alias created', 'dumpadm_validated' => 'Dumpadm validated', 'backups_started' => 'Backups started', 'explorer_enabled' => 'Explorer enabled', 'scic_enabled' => 'SCIC enabled', 'sunmc_enabled' => 'SunMC enabled', 'sunswat_enabled' => 'Sunswat enabled', 'helios_entry' => 'Helios entry created', 'root_password_set' => 'root password set', 'eds_tools_installed' => 'EDS tools installed', 'lu_patch_update' => 'Live Upgrade patches applied', 'fss_enabled' => 'fss enabled', 'pts_applied' => 'pts applied',
			       'frmware_obp_validation' => 'Firmware OBP validation', 'frmware_hba_validation' => 'Firmware HBA validation', 'frmware_alom_validation' => 'Firmware Alom validation', 'frmware_hypervisor_validation' => 'Firmware Hypervisor validation', 'lu_patch_update' => 'Lu patch update', 'frmware_disks_validation' => 'Firmware disks validation'
			       );

    //	foreach ($dcp_array as $column => $value)
    foreach ($choice_tables as $column => $value)
      {
	${$column}[] = &$this->createElement('radio', null, null, 'Yes', 'yes');
	${$column}[] = &$this->createElement('radio', null, null, 'No', 'no');
	$this->addGroup($$column, $column, $dcp_labels[$column]);
	$this->addRule("$$column", 'Check Yes or No', 'required');
	$this->setDefaults(array(
				 $column => $dcp_array[$column],
				 ));
      }
    
    
    // THIS OPTIONAL TABLES STUFF SHOULD BE HANDLED BY SMARTY
    $sometables = array('svm', 'offswan', 'onswan', 'vlan', 'eeprom', 'san', 'zfs', 'x86', 'cluster', 'clt');
    foreach ($sometables as $o_table)
      {
	if ( $array = $this->dcpVal("view_$o_table.0") )
	  {
	    $col_array = "view_" . $o_table . "_labels";
	    $col_labels = $this->dcpVal($col_array);
	    foreach ($array as $column => $value)
	      {
		$col_label = $col_labels[0]["$column"];
		if ( ($column == 'cam_sheet_sent_date' ) || ($column == 'san_switch_port_requested_date' ) || ($column == 'san_connected_date' ) )
		  {
		    $this->addElement('date', "$column", "$col_label", array('format' => 'd-M-Y', 'minYear' => 2008, 'maxYear' => date('Y')));			
		  }
		elseif ($column == 'san_cr_num')
		  $this->addElement('text', $column, $col_label, array('size' => 10, 'maxlength' => 10));
		else 
		  {
		    ${$column}[] = &$this->createElement('radio', null, null, 'Yes', 'yes');
		    ${$column}[] = &$this->createElement('radio', null, null, 'No', 'no');
		    $this->addGroup($$column, "$column", $col_label);	      
		    $this->addRule("$$column", 'Check Yes or No', 'required');
		  }
		$this->setDefaults(array(
					 $column => $value,
					 ));
	      }
	  }
      }
  }

  function buildRegToolEditForm ($sdesk_num)
  {
    $this->sdesk_num = $sdesk_num;
    $this->smarty = $this->createSmarty();
    $dcpProcedure_Smarty = new dcpProcedure($this->smarty);
    $dcpProcedure_Smarty->loadSmarty($this->sdesk_num);
    $this->dcp_smarty = $dcpProcedure_Smarty->getSmarty(); // fully loaded Smarty
    $dcp_labels = $this->dcpVal('dcp_labels');
    $dcp_array = $this->dcpVal('view_dcp.0'); // array of values loaded from smarty
    global $connection;
    $this->addElement('header', 'hdrTesting', "Please update the Regtool status of DCP #$sdesk_num");
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    $selection = new dcpSun_ServerSelections($connection, 'os_release');
    $Rows = $selection->getContents();
    $this->addElement('select', 'os_release_id', $dcp_labels['os_release_name'], $Rows);
    $this->setDefaults(array(
			     'os_release_id' => array_search($dcp_array['os_release_name'], $Rows),
			     ));
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    $proc_type_selection = new dcpSun_ServerSelections($connection, 'processor_type');
    $proc_type_Rows = $proc_type_selection->getContents();
    $this->addElement('select', 'processor_type_id', $dcp_labels['processor_type_name'], $proc_type_Rows);
    $this->setDefaults(array(
			     'processor_type_id' => array_search($dcp_array['processor_type_name'], $proc_type_Rows),
			     ));
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    $contents = array('frmware_obp','frmware_alom','frmware_hypervisor','frmware_hba','frmware_disks');
    foreach ($contents as $table)
      {
	$selection = new dcpSun_ServerSelections($connection, "$table");
	$Rows = $selection->getContents();
	$column_name = "$table" . "_name";
	$column_id = "$table" . "_id";

	if (! preg_match ('/^frmware_(obp|alom|hypervisor)/', $table) )
	  {
	    $mult_array = $this->dcpVal("$table");
	    $array_count = count($mult_array);
	    $array_count--;
	    $count = 0;

	    $labels = "$table" . "_labels";	    
	    $dcp_labels = $this->dcpVal("$labels.$count");

	    $ams =& $this->addElement('advmultiselect', $column_id, $dcp_labels[$column_name], $Rows,
				    array('size' => 5,
					  'class' => 'pool', 'style' => 'width:280px;'
					  ));

	    $ams->setButtonAttributes('add',    array('value' => 'Add >>',
						      'class' => 'inputCommand'
						      ));
	    $ams->setButtonAttributes('remove', array('value' => '<< Remove',
						      'class' => 'inputCommand'
						      ));
	    $template = '
<table bgcolor="#EEEEEE">
<!-- BEGIN label_2 --><tr><th align="center">{label_2}</th><!-- END label_2 -->
<!-- BEGIN label_3 --><th align="center">{label_3}</th></tr><!-- END label_3 -->
<tr>
  <td>{unselected}</td>
  <td>{selected}</td>
</tr>
<tr>
  <td align="center">{add}</td>
  <td align="center">{remove}</td>
</tr>
</table>';
	    $ams->setElementTemplate($template);
	    echo $ams->getElementJs(false);

	    $defaults = array();
	    while ($count <= $array_count)
	      {
		$dcp_array = $this->dcpVal("$table.$count");
		$name = $dcp_array[$column_name];
		$default = array_search($dcp_array[$column_name], $Rows);
		array_push($defaults, $default);
		$count++;
	    }
	    $this->setDefaults(array(
	    			     $column_id => $defaults
				     ));
	  }
	else {
	      $this->addElement('select', $column_id, $dcp_labels[$column_name], $Rows);
	      $this->setDefaults(array(
				       $column_id => array_search($dcp_array[$column_name], $Rows),
				       ));

	}
      }
  }

function getOSStuff ()
{
  // Let's get OS Stuff
  global $connection;
  $os_selection  = new dcpSun_ServerOsSelections($connection);
  $OS_Rows = $os_selection->getContents();
  $dcp_labels = $this->dcpVal('dcp_labels');
  $dcp_array = $this->dcpVal('view_dcp.0');
  $this->addElement('select', 'os_version_release', $dcp_labels['os_release_name'], $OS_Rows);
  $this->setDefaults(array(
			   'os_version_release' => $dcp_array['os_release_name'],
			   ));

}

}

?>