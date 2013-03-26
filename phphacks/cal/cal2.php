<?php
# This code comes courtesy of Alexander Naumann (mail at herrnaumann dot de)
?>
<html>
<head>
 <!-- <DEFANGED_STYLE type="text/css">
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
 --> </DEFANGED_STYLE>
</head>
<body>
<?php
class Day
{
	
public $inmonth;
public $month;	
public $day;	
public $year;
	
public function __construct( $inmonth, $month, $day, $year )
{
	$this->month	= $month;
	$this->day		= $day;
	$this->year		= $year;
	$this->inmonth	= $inmonth;
	$this->text		= '';
}

public function get_day() { return $this->day; }

public function get_month() { return $this->month; }

public function get_year() { return $this->year; }

public function get_inmonth() { return $this->inmonth; }

public function get_text() { return $this->text; }

public function set_text( $text ) { $this->text = $text; }

} # end class

#	sets the text to appear in the daycells
function setCalendarText( $days, $m, $d, $y, $text )
{
	foreach( $days as $day )
	{
		if ($day->get_day() == $d && $day->get_month() == $m && $day->get_year() == $y )
			$day->set_text( $text );
	}
}

#	returns the previous month 
function get_last_month( $month, $year )
{
	$lastmonth	= $month - 1;
	$lastyear	= $year;
	
	if ( $lastmonth < 1 )
	{
		$lastmonth = 12;
		$lastyear -= 1;
	}
	return array( $lastmonth, $lastyear );
}

#	returns the next month 
function get_next_month( $month, $year )
{
	$nextmonth	= $month + 1;
	$nextyear	= $year;
	
	if ( $nextmonth > 12 )
	{
		$nextmonth	= 1;
		$nextyear	+= 1;
	}
	return array( $nextmonth, $nextyear );
}

#	creates objects of each visible day in
#	the calendar
function makeCalendarDays( $month, $year )
{
	list( $nextmonth, $nextyear ) = get_next_month( $month, $year );
	list( $lastmonth, $lastyear ) = get_last_month( $month, $year );

	#	count of days in the previous month
	$dimlm = cal_days_in_month( CAL_GREGORIAN, $lastmonth, $lastyear );
	
	#	converts the first day in the current month
	#	to Julian format
	$jd	= cal_to_jd( CAL_GREGORIAN, $month, 1, $year );
	
	#	numeric weekday of the first day in
	#	the current monthz
	$day = jddayofweek( $jd ) - 1;
	
	#	count of days in the current month 
	$dim	= cal_days_in_month( CAL_GREGORIAN, $month, $year );
  
	$days	= array( );
  
	#	the remaining day numbers in the 
	#	calendar's first row up to the 
	#	first day of the current month are
	#	set with the last days of the previous month
	for( $d = 1; $d <= $day; $d++ )
		$days []= new Day( 0, $lastmonth, $dimlm - ( $day - $d ), $lastyear );
		
	#	day numbers of the current month
	for( $d = 1; $d <= $dim; $d++ )
		$days []= new Day( 1, $month, $d, $year );

	#	the remaining day numbers in the 
	#	calendar's last row from the 
	#	last day of the current month are
	#	set with the first days of the next month
	$left = ( ( floor( ( $day + $dim ) / 7 ) + 1 ) * 7 ) - ( $day + $dim );
	
	for( $d = 1; $d <= $left; $d++ )
		$days []= new Day( 0, $nextmonth, $d, $nextyear );
	
	
	#	returns the visible days as an array of objects
	return $days; 
}

$today	= getdate();

$year	= $today['year'];
$month	= $today['mon'];

if ( $_GET['year'] )	$year	= $_GET['year'];
if ( $_GET['month'] )	$month	= $_GET['month'];

$days = makeCalendarDays( $month, $year );

setCalendarText( &$days, $month, 5, $year, "Meet<br/>Jim" );
setCalendarText( &$days, $month, 10, $year, "Meet<br/>Sue" );

$months = array(
  "", "January", "February", "March", "April",
  "May", "June", "July", "August",
  "September", "October", "November", "December" );

$day_names = array( "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" );
?>
<div DEFANGED_STYLE="width:600px;">
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
