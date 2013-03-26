<?php
$to = "jack_d_herrington@codegeneration.net";
$to_full = "Jack Herrington";
$from = "jherr@pobox.com";
$from_full = "Jack Herrington";
$subject = "HTML Mail Test";

$random_hash = "zzz582x";

ob_start();
?>
To: <?php echo($to_full); ?> <<?php echo($to); ?>> 
From: <?php echo($from_full); ?> <<?php echo($from); ?>>
MIME-Version: 1.0 
Content-Type: multipart/alternative; 
			 boundary="==Multipart_Boundary_<?php echo($random_hash); ?>" 
<?php
$headers = ob_get_clean();
ob_start();
?>

This is a multi-part message in MIME format. 

--==Multipart_Boundary_<?php echo( $random_hash ); ?> 
Content-Type: text/plain; charset="iso-8859-1" 
Content-Transfer-Encoding: 7bit 

This is the text of the message in a a simple text format.

--==Multipart_Boundary_<?php echo( $random_hash ); ?> 
Content-Type: text/html; charset="iso-8859-1" 
Content-Transfer-Encoding: 7bit 

<html> 
<body> 
<p>Here is something with <b>HTML</b> formatting. That can include all of the usual:</p>
<ul>
<li>Bulleted lists</li>
<li>Tables</li>
<li>Images (if you include them as attachements or external links)</li>
<li>Character formatting</li>
<li>...and more!</li>
</ul>
</body> 
</html> 

--==Multipart_Boundary_<?php echo( $random_hash ); ?>--

<?php
$message = ob_get_clean();

$ok = @mail( $to, $subject, $message, $headers); 

echo( $ok ? "Mail sent\n" : "Mail failed\n" );
?>
