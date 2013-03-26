<?
function add_box_styles() { ?>
<style type="text/css">
.box {
   font-family: arial, verdana, sans-serif;
   font-size: x-small;
   background: #ccc;
}
.box-title {
   font-size: small;
   font-weight: bold;
   color: white;
   background: #777;
   padding: 5px;
   text-align: center;
}
.box-content {
   background: white;
   padding: 5px;
}
</style>
<? }

function start_box( $name ) { ?>
<table class="box" cellspacing="2" cellpadding="0">
<tr><td class="box-title"><? print( $name ) ?></td></tr>
<tr><td class="box-content">
<? }

function end_box() { ?>
</td></tr></table>
<? } ?>
