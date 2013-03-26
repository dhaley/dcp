<?php
$rows = 5;
$cols = 5;

$maxrows = 40;
$maxcols = 40;
$width = 100;
$height = 100;
?>
<html>
<head>
<script language="Javascript">
var origimgs = [];
<?php
for( $col = 0; $col < $maxcols; $col++ ) {
?>
origimgs[ <?php echo($col); ?> ] = [];
<?php
for( $row = 0; $row < $maxrows; $row++ ) {
  $id = sprintf( "img%02d_%02d", $row, $col );
?>
origimgs[ <?php echo($col); ?> ][ <?php echo($row); ?> ] = "<?php echo( $id ) ?>.jpg";
<?php
} }
?>

var imgs = [];

var dbg;

function startup()
{
<?php
for( $col = 0; $col < $cols + 2; $col++ ) {
?>
imgs[<?php echo($col) ?>] = [];
<?php
for( $row = 0; $row < $rows + 2; $row++ ) {
  $id = sprintf( "img%02d_%02d", $row, $col );
?>
imgs[<?php echo($col) ?>][<?php echo($row) ?>] = document.getElementById( "<?php echo( $id ); ?>" );
<?php
} }
?>
  dbg = document.getElementById("debug");
  position(0,0);
}

var scrollrows = <?php echo( $rows ); ?>;
var scrollcols = <?php echo( $cols ); ?>;
var width = <?php echo( $width ); ?>;
var height = <?php echo( $height ); ?>;
var maxrows = <?php echo( $maxrows ); ?>;
var maxcols = <?php echo( $maxcols ); ?>;
var xpos = 0;
var ypos = 0;

document.onmousemove = function(e)
{
  if ( dragging )
  {

    xpos += e.pageX - dragx;
    ypos += e.pageY - dragy;

    if ( xpos < 0 )
      xpos = 0;
    if ( ypos < 0 )
      ypos = 0;

    position( xpos, ypos );

    dragx = e.pageX;
    dragy = e.pageY;
  }
}

document.onmousedown = function(e)
{
  dragging = true;
  dragx = e.pageX;
  dragy = e.pageY;
}

document.onmouseup = function(e)
{
  dragging = false;
}


function position( x, y )
{
  if ( x < 0 ) x = 0;
  if ( y < 0 ) y = 0;

  startcol = Math.floor( x / width );
  startrow = Math.floor( y / height );

  offsetx = Math.abs( x - ( startcol * width ) ) * -1;
  offsety = Math.abs( y - ( startrow * height ) ) * -1;

  viewheight = ( scrollrows + 1 ) * height;
  viewwidth = ( scrollcols + 1 ) * width;

var txt = "";
txt += "x = "+x+"<br/>";
txt += "y = "+y+"<br/>";
txt += "startrow = "+startrow+"<br/>";
txt += "startcol = "+startcol+"<br/>";
txt += "offsetx = "+offsetx+"<br/>";
txt += "offsety = "+offsety+"<br/>";
txt += "viewheight = "+viewheight+"<br/>";
txt += "viewwidth = "+viewwidth+"<br/>";
dbg.innerHTML = txt;

  for( var row = 0; row < scrollrows + 2; row++)
  {
    for( var col = 0; col < scrollcols + 2; col++)
    {
      var left = offsetx + ( col * width );
      var top = offsety + ( row * height );
      imgs[row][col].style.left = left;
      imgs[row][col].style.top = top;
      imgs[row][col].src = origimgs[startrow+row][startcol+col];

      remainderx = viewwidth - ( left + width );
      remaindery = viewheight - ( top + height );

      if ( remainderx > width )
        remainderx = width;
      if ( remainderx < 0 )
        remainderx = 0;
      if ( remaindery > height )
        remaindery = height;
      if ( remaindery < 0 )
        remaindery = 0;

      imgs[row][col].style.clip = "rect( 0px 0px "+remaindery+"px "+remainderx+"px )";
    }
  }
}

var dragging = false;
var dragx = 0;
var dragy = 0;

</script>
</head>
<body onload="startup();">
<?php
for( $row = 0; $row < $rows + 2; $row++ ) {
for( $col = 0; $col < $cols + 2; $col++ ) {
  $id = sprintf( "img%02d_%02d", $row, $col );
?>
<img src="" style="position:absolute;left:0;top:0;" id="<?php echo($id) ?>" />
<?php
} }
?>
<div style="position:absolute;left:800;top:20;" id="debug"></div>
</body>
</html>
