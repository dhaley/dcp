<?php
$xml = new DOMDocument();
$xml->Load( "input.xml" );

$xsl = new DOMDocument();
$xsl->Load( "format.xsl" );

$xslproc = new XSLTProcessor();
$xslproc->importStylesheet( $xsl );
print( $xslproc->transformToXML( $xml ) );
?>
