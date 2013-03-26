<?php

require_once 'Structures/DataGrid.php';
require_once 'PEAR.php';
define("DB_DATAOBJECT_NO_OVERLOAD",true); /* This is needed for some buggy versions of PHP4 */
require_once "HTML/Table.php";
require_once "dcpPage.php";

class dcpDataGrid
 {
   var $dcpPage;

   // functions
   function printHeader ($dcp_action) 
   {
     $this->dcpPage =& new dcpPage('PSC DCP Tracker');
     //     $this->dcpPage->buildPageHeading('http://psc.central.sun.com:9000/dcp/dcp_view_all.php');
     $this->dcpPage->buildPageHeading("$dcp_action");     
   }
   
   function printHeader2 () {
     $out = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" ";
     $out .= "\"http://www.w3.org/TR/html401/loose.dtd\">\n";
     $out .= "<html>\n";
     $out .=  "<head>\n";
     print $out;
     // echo <<<END
     //   <!-- Require the Prototype JS framework from http://www.prototypejs.org -->
     // <script type="text/javascript" src="prototype.js"></script>
     //   <script type="text/javascript">
     //   function updateGrid(info)
     //   {
     // 	 var url = 'psc.central.sun.com:9000/dcp/dcp_view_all.php'; 
     // 	 var pars = 'page=' + info.page;
     // 	 if (info.sort.length > 0) {
     // 	   pars += '&orderBy=' + info.sort[0].field + '&direction=' + info.sort[0].direction;
     // 	 }
       
     // 	 new Ajax.Updater( 'grid', url, { method: 'get', parameters: pars + '&ajax=table' });
     // 	 new Ajax.Updater( 'pager', url, { method: 'get', parameters: pars + '&ajax=pager' });

     // 	 // Important: return false to avoid href links
     // 	 return false;
     //   } 
     //   </script>
     echo <<< END
<title>PSC DCP Tracker</title>       
</head>

END;
   }
   
   function printFooter () {
     $out = "</body>\n";
     $out .= "</html>\n";
     print $out;
   }

   function printLink($params, $args = array())
   {
     extract($params);
     extract($args);
     $edit_url = 'http://psc.central.sun.com:9000/dcp/dcp_edit.php';
     return '<a href="' . $edit_url . '?sdesk_num=' . $record['sdesk_num'] . '">' . $record['sdesk_num'] . '</a>';
   }

   function printEditLink($params)
   {
     $sdesk_num = $record['sdesk_num'];
     extract($params);
     return '<a href="' . $edit_url . '?dcp_action=view_dcp' . '&sdesk_num=' . $record['sdesk_num'] . '">'. $record['sdesk_num'] . '</a>';
   }
   
   function printFullOS($params)
   {
     extract($params);
     return $record['os_name'] . ' ' . $record['os_version_name'];
   }
   
   function printDesc($params, $args = array())
   {
     extract($params);
     extract($args);
     
     if (strlen($record[$fieldName]) > $length) {
       return nl2br(substr($record[$fieldName], 0, $length)) . '...';
     } else {
       return nl2br($record[$fieldName]);
     }
   }

   function printCheckbox($params)
   {
     extract($params);
     return '<input type="checkbox" name="idList[]" value="' . $record['id'] . '">';
   }


   function printRoleSelector($params)
   {
     global $roleList;
     
     extract($params);
     
     $html = '<select name="role_id">';
     foreach ($roleList as $roleId => $roleName) {
       $html .= "<option value=\"$roleId\">$roleName</option>\n";
     }
     $html .= '</select>';
     
     return $html;
   }

   // set up user-defined error handler
   function errHandler($e) {
     die($e->getMessage());
   }

   function formatRowNumber($params, $recordNumberStart)
   {
     return $params['currRow'] + $recordNumberStart;
   }
   
   
 }

?>