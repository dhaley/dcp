<html>
<head><title>Login</title></head>
<body>
<?php if ( $_GET['bad'] == 1 ) { ?>
<font color="red">Bad login or password, please try again<br/></font>
<?php } ?>
<form action="login.php" method="post">
<table width="300" border="0" cellspacing="0" cellpadding="2">
<tr><td>User name:</td><td><input type="text" name="user" /></td></tr>
<tr><td>Password:</td><td><input type="password" name="password" /></td></tr>
<tr><td colspan="2"><center><input type="submit" value="Login" /></center></td></tr>
</table>
</form>
</body>
</html>
