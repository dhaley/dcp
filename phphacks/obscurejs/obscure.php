<?php
function obscurejs_start()
{
    ob_start();
}

$funcs = array();

function decreplace( $matches )
{
    global $funcs;

    $newname = "af".count($funcs);

    $funcs[ $matches[1] ] = $newname;

    return "function ".$newname."(";
}

function objscurejs( $matches )
{
    global $funcs;

    $js = $matches[2];
    $js = preg_replace_callback( "/function\s+(.*?)\s*\(/", "decreplace", $js );
    foreach( $funcs as $oldfunc => $newfunc )
    {
      $js = preg_replace( "/".$oldfunc."/", $newfunc, $js );
    }
    return "<script".$matches[1].">".$js."</script>";
}

function obscurejs_end()
{
    $doc = ob_get_clean();
    $doc = preg_replace_callback( "/\<script(.*?)\>(.*?)\<\/script\>/s", "objscurejs", $doc );
    print( $doc );
}
?>
