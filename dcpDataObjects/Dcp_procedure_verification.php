<?php
/**
 * Table Definition for dcp_procedure_verification
 */
require_once 'DB/DataObject.php';

class dcpDataObjects_Dcp_procedure_verification extends DB_DataObject 
{
    ###START_AUTOCODE
    /* the code below is auto generated do not remove the above tag */

    public $__table = 'dcp_procedure_verification';      // table name
    public $sdesk_num;                       // int(10)  not_null primary_key
    public $login;                           // string(18)  not_null
    public $submit_time;                     // datetime(19)  binary
    public $close_time;                      // datetime(19)  binary
    public $usr_sunid;                       // string(10)  not_null
    public $usr_nm;                          // string(41)  not_null
    public $usr_dept;                        // string(15)  not_null
    public $priority;                        // int(1)  not_null
    public $new_priority;                    // int(1)  not_null
    public $request_status;                  // string(80)  not_null
    public $short_desc;                      // string(80)  not_null
    public $sysid;                           // real(14)  multiple_key unsigned
    public $note;                            // string(144)  
    public $regtool_prod_status_sdt;         // int(10)  
    public $gcn_num;                         // int(10)  
    public $os_load_date;                    // datetime(19)  not_null binary
    public $netwrk_inferfaces_full_duplex;    // string(3)  not_null enum
    public $netwrk_interfaces_any_faults;    // string(3)  not_null enum
    public $ipmp_configured;                 // string(3)  not_null enum
    public $sendmail_verified;               // string(3)  not_null enum
    public $sendmail_root_alias;             // string(3)  not_null enum
    public $dumpadm_validated;               // string(3)  not_null enum
    public $backups_started;                 // string(3)  not_null enum
    public $backups_sdt_num;                 // int(10)  
    public $explorer_enabled;                // string(3)  not_null enum
    public $scic_enabled;                    // string(3)  not_null enum
    public $sunmc_enabled;                   // string(3)  not_null enum
    public $sunswat_enabled;                 // string(3)  not_null enum
    public $helios_entry;                    // string(3)  not_null enum
    public $eis_radiance_case;               // int(10)  
    public $netcool_inventory_sdt;           // int(10)  
    public $root_password_set;               // string(3)  not_null enum
    public $pts_applied;                     // string(3)  not_null enum
    public $fss_enabled;                     // string(3)  not_null enum
    public $eds_tools_installed;             // string(3)  not_null enum
    public $frmware_obp_validation;          // string(3)  not_null enum
    public $frmware_hba_validation;          // string(3)  not_null enum
    public $frmware_disks_validation;        // string(3)  not_null enum
    public $frmware_alom_validation;         // string(3)  not_null enum
    public $frmware_hypervisor_validation;    // string(3)  not_null enum
    public $lu_patch_update;                 // string(3)  enum

    /* Static get */
    function staticGet($k,$v=NULL) { return DB_DataObject::staticGet('dcpDataObjects_Dcp_procedure_verification',$k,$v); }

    /* the code above is auto generated do not remove the tag below */
    ###END_AUTOCODE


    // now define your table structure.
    // key is column name, value is type
    // function table() {
    //     return array(
    //         'sdesk_num'     => DB_DATAOBJECT_INT,
    //         'login'   => DB_DATAOBJECT_STR,
    // 	    'submit_time'   => DB_DATAOBJECT_STR + DB_DATAOBJECT_DATE + DB_DATAOBJECT_TIME,
    //         'bday'   => DB_DATAOBJECT_STR + DB_DATAOBJECT_DATE,
    //         'last'   => DB_DATAOBJECT_STR + DB_DATAOBJECT_DATE + DB_DATAOBJECT_TIME,
    //         'active' => DB_DATAOBJECT_INT + DB_DATAOBJECT_BOOL,
    //         'desc'   => DB_DATAOBJECT_STR + DB_DATAOBJECT_TXT,
    //         'photo'  => DB_DATAOBJECT_STR + DB_DATAOBJECT_BLOB,
    //     );
    // }


    
    //    var $fb_createSubmit = true;
    //    var $fb_linkDisplayLevel = 2;
    var $fb_fieldLabels;
     var $fb_formHeaderText = 'Edit DCP';
     var $fb_fieldsToRender;

     

//     ////////////// ENUM FIELD STUFF
     var $fb_enumFields = array('netwrk_inferfaces_full_duplex','netwrk_interfaces_any_faults','ipmp_configured','sendmail_verified','sendmail_root_alias','dumpadm_validated','backups_started','explorer_enabled','scic_enabled','sunmc_enabled','sunswat_enabled','helios_entry','root_password_set','pts_applied','fss_enabled','eds_tools_installed','frmware_obp_validation','frmware_hba_validation','frmware_disks_validation','frmware_alom_validation','frmware_hypervisor_validation','lu_patch_update');
     var $fb_enumOptions = array('enumField' => array('option1' => 'option1',
                                                    'option2' => 'option2',
                                                    'optionTheThird' => 'optionTheThird'));
     var $fb_linkElementTypes = array('netwrk_inferfaces_full_duplex' => 'radio', 'netwrk_interfaces_any_faults' => 'radio','ipmp_configured' => 'radio','sendmail_verified' => 'radio','sendmail_root_alias' => 'radio','dumpadm_validated' => 'radio','backups_started' => 'radio','explorer_enabled' => 'radio','scic_enabled' => 'radio','sunmc_enabled' => 'radio','sunswat_enabled' => 'radio','helios_entry' => 'radio','root_password_set' => 'radio','pts_applied' => 'radio','fss_enabled' => 'radio','eds_tools_installed' => 'radio','frmware_obp_validation' => 'radio','frmware_hba_validation' => 'radio','frmware_disks_validation' => 'radio','frmware_alom_validation' => 'radio','frmware_hypervisor_validation' => 'radio','lu_patch_update' => 'radio');


     //     var $fb_dateFields = array('os_load_date');



     //    var $fb_selectAddEmpty = array('os_load_date');
     //$dateOptions['emptyOptionText'] = $fb_selectAddEmptyLabel;
     //var $fb_timeFields = array('os_load_date');
     //    $form->setDefaults(array('date' => date('d / M / Y')));
// >  $form->addElement('date', 'in_service_date', 'In service date',
// >    array(
// >        'language'  => $p->rs->language,
// >        'format'    => 'M / d / Y',
// >        'minYear'   => (intval(date('Y')) - 3),
// >        'maxYear' => (intval(date('Y')) + 2)
// >    )

    
    var $fb_textFields = array('note');

    var $fb_linkDisplayFields = array('hostname','sysid');

    var $fb_fieldAttributes = array('note' => array('length' => 144),
				    'regtool_prod_status_sdt' => array('length' => '10'),
				    'gcn_num' => array('length' => '10'),
				    'backups_sdt_num' => array('length' => '10'),
				    'eis_radiance_case' => array('length' => '10'),
				    'netcool_inventory_sdt' => array('length' => '10'),
				    'sysid' => 'style="background-color: blue;"');


    function preGenerateForm(&$fb) {
      $this->fb_fieldLabels['note'] = 'User note';
      $this->fb_fieldLabels['sysid'] = 'Hostname';
    }



    
    //You can do this with the preGenerateFormCallback option. 
}
