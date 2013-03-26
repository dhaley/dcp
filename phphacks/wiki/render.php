<html>
<body>
<?php
// Include the Wiki Text Pear library
require_once( "Text/Wiki.php" );

// Create the Wiki object
$wiki = new Text_Wiki();

$wiki->enableRule('html');

$text = $_POST["text" ];

// Render the text field sent to us in the form
echo( $wiki->transform( $text, 'Xhtml' ) );
?>
</body>
</html>
