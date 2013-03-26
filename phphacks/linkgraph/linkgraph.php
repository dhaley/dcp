<?php
$wordcounts = array();
$words = split( " ", "CNN  number Americans disapproving President Bush job perance risen highest level presidency according CNN USA Today Gallup poll released Monday According poll  percent respondents disapproved Bush performance compared  percent approved margerror plus minus  percentage points  percent figure highest disapproval rating recorded CNN USA Today Gallup poll Bush president January approval percentage  percent matches low point late March  point gap between those disapproved approved largest recorded during Bush tenure As Bush prepares address nation Tuesday defend Iraq policy just  percent those responding poll approved handling war  percent disapproved Full story approval rating Iraq unchanged poll late May disapproval figure marked increase  percentage points But poll found issues other Iraq war dragging down Bush numbers Respondents expressed stronger disapproval handling economy energy policy health care Social Security lone bright spot president poll handling terrorism which scored  percent approval rating compared just  percent disapproved presidents worst numbers latest poll came issue Social Security respondents disapproving performance margmore percent  percent Bush made changing Social Security system signature issue second term He  proposed creating voluntary government sponsored personal retirement accounts workers  younger Under proposal workers could invest portion their Social Security taxes range government selected funds exchange guaranteed benefits retirement plan run instiff opposition Democrats accounts are too risky undermine Social Security system Some Republicans are wary taking such politically risky economy only  percent poll respondents approved Bush performance compared  percent disapproved On energy policy percent approved percent disapproved health care percent approved percent disapproved poll results based interviews Friday Sunday American adults" );
foreach( $words as $word )
{
  $word = strtolower( $word );
  if ( strlen( $word ) > 0 )
  {
    if ( ! array_key_exists( $word, $wordcounts ) )
      $wordcounts[ $word ] = 0;
    $wordcounts[ $word ] += 1;
  }
}

$min = 1000000;
$max = -1000000;
foreach( array_keys( $wordcounts ) as $word )
{
  if ( $wordcounts[ $word ] > $max )
    $max = $wordcounts[ $word ];
  if ( $wordcounts[ $word ] < $min )
    $min = $wordcounts[ $word ];
}
$ratio = 18.0 / ( $max - $min );
?>
<html>
<head>
<style type="text/css">
body { font-family: arial, verdana, sans-serif; }
.link { line-height: 20pt; }
</style>
</head>
<body>
<div style="width:600px;">
<?php
$wc = array_keys( $wordcounts );
sort( $wc );
foreach( $wc as $word )
{
$fs = (int)( 9 + ( $wordcounts[ $word ] * $ratio ) );
?>
<a class="link" href="http://en.wikipedia.org/wiki/<?php echo($word); ?>" style="font-size:<?php echo( $fs ); ?>pt;">
<?php echo( $word ); ?></a> &nbsp;
<?php } ?>
</div>
</body>
</html>
