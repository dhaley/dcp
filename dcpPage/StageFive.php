<?php

class StageFive extends dcpPage
{
    function buildForm()
    {
      $this->_formBuilt = true;
      $data     =& $this->controller->container();
      $hostname = $data['values']['perm']['hostname'];
      global $connection;

      $this->buildPageHeading();
      $this->addElement('header', null, "Please select relevant options for $hostname");	

      $contents = array('frmware_obp' => 'OBP Firmware','frmware_alom' => "ALOM Firmware",'frmware_hypervisor' => 'Hypervisor Firmware','frmware_hba' => 'HBA Firmware','frmware_disks' => 'Disk Firmware');

      foreach ($contents as $table => $label)
	{
	  if (! preg_match ('/^frmware_(obp|alom|hypervisor)/', $table) )
	    {
	      //$this->addElement('select', "$table", "$label :", $Rows);
	      
	      $selection = new dcpSun_ServerSelections($connection, "$table");
	      $Rows = $selection->getContents();

	      $ams =& $this->addElement('advmultiselect', "$table", "$label", $Rows,
				    array('size' => 5,
					  'class' => 'pool', 'style' => 'width:280px;'
					  ));
	      $ams->setLabel(array("$label:", 'Available', 'Selected'));
	      $ams->setButtonAttributes('add',    array('value' => 'Add >>',
						      'class' => 'inputCommand'
						      ));
	      $ams->setButtonAttributes('remove', array('value' => '<< Remove',
							'class' => 'inputCommand'
							));
	      $template = '
<table bgcolor="#EEEEEE">
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
	    }
	  else 
	    {
	      $selection = new dcpSun_ServerSelections($connection, "$table");
	      $Rows = $selection->getContents();
	      if (! preg_match ('/^frmware_(obp|alom)/', $table) )
		{
		  array_unshift($Rows, 'N/A');
		}
	      $this->addElement('select', "$table", "$label :", $Rows);
	    }
	}

      $this->smarty = $this->createSmarty();
      $dcpProcedure_Smarty = new dcpProcedure($this->smarty);
      $dcpProcedure_Smarty->assignLabels();
      
      $this->getOSStuff();

      $prevnext[] =& $this->createElement('submit', $this->getButtonName('back'), '<< Back', array("onClick" => "this.form.onsubmit = null; return true;") );
      $prevnext[] =& $this->createElement('submit',   $this->getButtonName('next'), 'Next >>');
      $this->addGroup($prevnext, null, '', '&nbsp;', false);
      $this->setDefaultAction('next');
    }
}

?>