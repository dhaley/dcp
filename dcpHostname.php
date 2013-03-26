<?php

  // Definition of dcp class dcpAHostname
  // methods act on and validate hostnames
  // this will include approriate headers, footers and formatting
  //

class dcpHostname {
  // Member variables
  var $full_hostname;
  var $host_name;
  var $domain_name;

  private $__domains = array("argentina", "asia","aus","austria","belgium","brazil","callcenter.partner","canada","central","central.sun.com","chile","colombia","czech","denmark","dubai","east","ebay","egypt","eng","eu","eu-spn","eu.sun.com","europe.stortek.com","finland","france","germany","greece","holland","hungary","india","ipc","ireland","israel","italy","japan","kazakhstan","korea","luxembourg","malaysia","mysql.com","newzealand","norway","opensolaris.org","org","pacificrim.stortek.c","plano.webhost.eds.ne","poland","portugal","pr","pr.sun.com","prc","prc.sun.com","red.iplanet","red.iplanet.com","rsa","russia","saudi","sfbay","singapore","singapore.sun.com","slovakia","spain","stc.com","storagetek","stortek.com","sun","sun.co.jp","sun.com","sun.com.au","sunmexico","swds","sweden","swiss","system","taiwan","thailand","turkey","uk","uk.sun.com","venezuela","west");

  
  // functions

  function validateDomain () {
    foreach ($this->__domains as $realdomain ) {
      $pattern = "/^$realdomain\..+$/";
      if ( preg_match( $pattern , $this->domain_name ) ) {
 	$this->domain_name = $realdomain; # shorten primary domain
	return;
      }
    }
  }
  
  function validateHostname () { // make sure hostname and domain exist
    if ( preg_match('/^([^.]+)\.(.+)$/', $this->full_hostname,$hostname_parts ) ) {
      $this->host_name = $hostname_parts[1];
      $this->domain_name = $hostname_parts[2];
      $this->validateDomain();
      return 1;
    } else {
      return 0;
    }
  }

  function returnOnlyHostname () {
    return $this->host_name;
  }

  function returnOnlyDomainname () {
    return $this->domain_name;
  }

  // constructor function
  function __construct($full_hostname) {
    $this->full_hostname = $full_hostname;
  }
  
  }

?>