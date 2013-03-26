<?php
require( 'Net/GameServerQuery.php' );

$protocol = 'halflife';
$ip = '66.159.222.15';

$gsq = new Net_GameServerQuery();
$gsq->addServer( $protocol, $ip );
$res = $gsq->execute();
?>
<html>
<head>
<title>Game Server Status</title>
</head>
<style>
body { font-family: arial, verdana, sans-serif; }
th { font-size: xx-small; border-bottom: 1px solid black; }
td { font-size: xx-small; vertical-align: top; }
.num-players { text-align: center; }
.header { font-weight: bold; }
</style>
<body>
<table>
<tr>
<td class="header">Protocol</td>
<td><?php echo($protocol); ?></td>
</tr>
<tr>
<td class="header">IP</td>
<td><?php echo($ip); ?></td>
</tr>
</table>
<table width="100%" cellspacing="0" cellpadding="3">
<tr>
<th width="20%">IP/Port</th>
<th width="20%">Password</th>
<th width="20%">Hostname</th>
<th width="20%">Players</th>
<th width="20%">Mod</th>
</tr>
<?php foreach( $res[0] as $r ) { ?>
<tr>
<td width="20%"><?php echo($r['ip']); ?><br/><?php echo($r['port']); ?></td>
<td width="20%"><?php echo($r['password']); ?></td>
<td width="20%"><?php echo($r['hostname']); ?></td>
<td width="20%" class="num-players">
<?php echo($r['numplayers']); ?> current<br/>
<?php echo($r['maxplayers']); ?> max
</td>
<td width="20%"><?php echo($r['mod']); ?></td>
</tr>
<?php } ?>
</table>
</body>
</html>
