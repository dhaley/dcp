<?
function add_box_styles() { ?>
<style type="text/css">
.box {
   font-family: arial, verdana, sans-serif;
}
.box-title {
   font-size: small;
   font-weight: bold;
   color: white;
   background: #000063;
   text-align: center;
}
.box-content-container {
   background: #000063;
}
.box-content {
   background: white;
   font-size: x-small;
   padding: 5px;
}
</style>
<? }

function start_box( $name ) { ?>
<table cellspacing="0" cellpadding="0" class="box">
<tr><td>

<table cellspacing="0" cellpadding="0" width="100%" class="box-title">
<tr><td width="20" height="20"><img src="blue_ul.png" /></td>
<td><? print( $name ) ?></td>
<td width="20" height="20"><img src="blue_ur.png"></td></tr></table>

</td></tr>
<tr><td>

<table width="100%" cellspacing="2" cellpadding="0"
  class="box-content-container">
<tr><td class="box-content">
<? }

function end_box() { ?>
</td></tr></table>
<tr><td>

<table cellspacing="0" cellpadding="0" width="100%" class="box-title">
<tr><td width="20" height="20"><img src="blue_ll.png" /></td>
<td>&nbsp;</td>
<td width="20" height="20"><img src="blue_lr.png"></td></tr></table>

</td></tr></table>
<? } ?>
