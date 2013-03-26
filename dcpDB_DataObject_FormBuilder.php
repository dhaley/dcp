<?php

require_once 'DB/DataObject/FormBuilder.php';

class dcpDB_DataObject_FormBuilder extends DB_DataObject_FormBuilder {
  // var $createSumbit = true;
  
  // function DB_DataObject_FormBuilder_MyDriver(&$do, $options = false)
  // {
  //   // Calling the parent at the beginning of the constructor causes the options
  //   // set below to override options set in $options and PEAR::setStaticProperty()
  //   parent::DB_DataObject_FormBuilder($do, $options);
  //   $this->linkDispayLevel = 2;
  //   // Calling the parent in the middle of the constructor allows $options and
  //   // PEAR::setStaticProperty() to only override the options set before
  //   $this->elementTypeMap['date'] = 'myDate';
  //   // Calling the parent at the end of the constructor allows $options and
  //   // PEAR::setStaticProperty() to override the options set above
  //   //parent::DB_DataObject_FormBuilder($do, $options);
  // }
 
  // //this is important. This needs to be done to insure your class is used
  // function &create(&$do, $options = false, $driver = 'QuickForm')
  //   {
  //     parent::create($do, $options, $driver, 'db_dataobject_formbuilder_myformbuilder');
  //   }

  // set up user-defined error handler
  function errHandler($e) {
    die($e->getMessage());
  }

  
}

?>