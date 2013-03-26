<?php

  // this is the common configuration code - place in a general site wide include file.
  // this  the code used to load and store DataObjects Configuration.
$options = PEAR::getStaticProperty('DB_DataObject','options');

// the simple examples use parse_ini_file, which is fast and efficient.
// however you could as easily use wddx, xml or your own configuration array.
$config = parse_ini_file('myconfig.ini',TRUE);

// because PEAR::getstaticProperty was called with an & (get by reference)
// this will actually set the variable inside that method (a quasi static variable)
$options = $config['DB_DataObject'];

?>