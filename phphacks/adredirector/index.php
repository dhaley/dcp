<?php
function redir_link( $url, $text )
{
?>
<a href="redir.php?url=<?php echo( $url ); ?>"><?php echo( $text ); ?></a>
<?php
}
?>
<html>
<body>
Here are my articles:<br/><br/>
<?php redir_link( 'article1.html', 'Article one' ); ?><br/>
<?php redir_link( 'article2.html', 'Article two' ); ?><br/>
<?php redir_link( 'article3.html', 'Article three' ); ?><br/>
</body>
</html>
