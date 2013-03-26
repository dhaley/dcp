<html>
<head>
<style type="text/css">
.calendar { 
  font-family: arial, verdana, sand serif;
}
.calendar td {
  border: 1px solid #eee;
}
.calendar-title {
  text-align: center;
  font-style: italic;
}
.calendar-day-title {
  text-align: center;
  font-size: small;
  background: #ccc;
  font-weight: bold;
}
.calendar-day, .calendar-outmonth-day {
  height: 60px;
  vertical-align: top;
  text-align: center;
  font-size: small;
  padding: 0px;
}
.calendar-day-number {
  text-align: right;
  background: #ddd;
}
.calendar-content {
  padding: 2px;
  font-size: x-small;
}
.calendar-outmonth-day {
  color: #666;
  font-style: italic;
  background: #ddd;
}
</style>
</head>
<body>
<?php
class Day
{
  function Day( $inmonth, $month, $day, $year )
  {
    $this->{'month'} = $month;
    $this->{'day'} = $day;
    $this->{'year'} = $year;
    $this->{'inmonth'} = $inmonth;
    $this->{'number'} = $number;
    $this->{'text'} = "";
  }
  function get_day() { return $this->{'day'}; }
  function get_month() { return $this->{'month'}; }
  function get_year() { return $this->{'year'}; }
  function get_inmonth() { return $this->{'inmonth'}; }
  function get_number() { return $this->{'number'}; }
  function get_text() { return $this->{'text'}; }
  function set_text( $text ) { $this->{'text'} = $text; }
}

function setCalendarText( $days, $m, $d, $y, $text )
{
  foreach( $days as $day )
  {
    if ( $day->get_day() == $d &&
         $day->get_month() == $m &&
       $day->get_year() == $y )
      $day->set_text( $text );
  }
}

function get_last_month( $month, $year )
{
  $lastmonth = $month - 1;
  $lastyear = $year;
  if ( $lastmonth < 0 ) { $lastmonth = 11; $lastyear -= 1; }
  return array( $lastmonth, $lastyear );
}

function get_next_month( $month, $year )
{
  $nextmonth = $month + 1;
  $nextyear = $year;
  if ( $nextmonth > 11 ) { $nextmonth = 0; $nextyear += 1; }
  return array( $nextmonth, $nextyear );
}

function makeCalendarDays( $month, $year )
{
  list( $nextmonth, $nextyear ) = get_next_month( $month, $year );
  list( $lastmonth, $lastyear ) = get_last_month( $month, $year );

  $dimlm = cal_days_in_month( CAL_GREGORIAN, $lastmonth, $lastyear );
  
  $jd = cal_to_jd( CAL_GREGORIAN, $month + 1, 1, $year );
  $day = jddayofweek( $jd );
  $dim = cal_days_in_month( CAL_GREGORIAN, $month + 1, $year );
  
  $days = array( );
  
  for( $d = 0; $d < $day; $d++ )
    $days []= new Day( 0, $lastmonth + 1, $dimlm - ( $day - $d ), $lastyear );
   
  for( $d = 1; $d <= $dim; $d++ )
    $days []= new Day( 1, $month + 1, $d, $year );
  
  $left = ( ( floor( ( $day + $dim ) / 7 ) + 1 ) * 7 ) - ( $day + $dim );
  for( $d = 0; $d < $left; $d++ )
    $days []= new Day( 0, $nexmonth + 1, $d+1, $nextyear );

  return $days; 
}

$today = getdate();

$year = $today['year'];
$month = $today['mon'] - 1;

if ( $_GET['year'] ) $year = $_GET['year'];
if ( $_GET['month'] ) $month = $_GET['month'];

$days = makeCalendarDays( $month, $year );

setCalendarText( &$days, $month + 1, 5, $year, "Meet<br/>Jim" );
setCalendarText( &$days, $month + 1, 10, $year, "Meet<br/>Sue" );

$months = array(
  "January", "February", "March", "April",
  "May", "June", "July", "August",
  "September", "October", "November", "December" );
$day_names = array( "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" );
?>
<div style="width:600px;">
<table class="calendar" width="100%" cellspacing="0" cellpadding="1">
<tr><td colspan="7" class="calendar-title" width="13%">
<?php
list( $nextmonth, $nextyear ) = get_next_month( $month, $year );
list( $lastmonth, $lastyear ) = get_last_month( $month, $year );
?>
<a href="cal.php?year=<?php echo($lastyear); ?>&month=<?php echo( $lastmonth ); ?>">&lt;&lt;</a>
<?php echo( $months[$month] ); ?> <?php echo( $year ); ?>
<a href="cal.php?year=<?php echo($nextyear); ?>&month=<?php echo( $nextmonth ); ?>">&gt;&gt;</a>
</td></tr>
<tr>
<?php foreach( $day_names as $day ) { ?>
<td class="calendar-day-title"><?php echo( $day ); ?></td>
<?php } ?>
</tr>
<?php
$p = 0;
foreach( $days as $d ) {
if ( $p == 0 ) echo ( "<tr>" );
$day_style = $d->get_inmonth() ? "calendar-day" : "calendar-outmonth-day";
?>
<td class="<?php echo( $day_style ); ?>" width="13%">
<div class="calendar-day-number">
<?php echo( $d->get_day() ); ?>
</div>
<div class="calendar-content">
<?php echo( $d->get_text() ); ?>
</div>
</td>
<?php
$p += 1;
if ( $p == 7 ) $p = 0;
}
?>
</tr>
</table>
</div>
<body>
</html>
