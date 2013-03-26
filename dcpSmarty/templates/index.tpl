<html>
<head>
<title>Smarty</title>
</head>
<body>
Hello, {$name}!
{section name=display loop=$view_dcp}
{$view_dcp[display].SDESK_NUM}
{/section}
</body>
</html>
