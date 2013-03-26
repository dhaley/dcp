<?php $states = array(
  array( "Alabama",4447100,1963711,52419.02,1675.01,50744,87.6,38.7 ),
  array( "Alaska",626932,260978,663267.26,91316,571951.26,1.1,0.5 ),
  array( "Arizona",5130632,2189189,113998.3,363.73,113634.57,45.2,19.3 ),
  array( "Arkansas",2673400,1173043,53178.62,1110.45,52068.17,51.3,22.5 ),
  array( "California",33871648,12214549,163695.57,7736.23,155959.34,217.2,78.3 ),
  array( "Colorado",4301261,1808037,104093.57,376.04,103717.53,41.5,17.4 ),
  array( "Connecticut",3405565,1385975,5543.33,698.53,4844.8,702.9,286.1 ),
  array( "Delaware",783600,343072,2489.27,535.71,1953.56,401.1,175.6 ),
  array( "District of Columbia",572059,274845,68.34,6.94,61.4,9316.4,4476.1 ),
  array( "Florida",15982378,7302947,65754.59,11827.77,53926.82,296.4,135.4 ),
  array( "Georgia",8186453,3281737,59424.77,1518.63,57906.14,141.4,56.7 ),
  array( "Hawaii",1211537,460542,10930.98,4508.36,6422.62,188.6,71.7 ),
  array( "Idaho",1293953,527824,83570.08,822.87,82747.21,15.6,6.4 ),
  array( "Illinois",12419293,4885615,57914.38,2330.79,55583.58,223.4,87.9 ),
  array( "Indiana",6080485,2532319,36417.73,550.83,35866.9,169.5,70.6 ),
  array( "Iowa",2926324,1232511,56271.55,402.2,55869.36,52.4,22.1 ),
  array( "Kansas",2688418,1131200,82276.84,461.96,81814.88,32.9,13.8 ),
  array( "Kentucky",4041769,1750927,40409.02,680.85,39728.18,101.7,44.1 ),
  array( "Louisiana",4468976,1847181,51839.7,8277.85,43561.85,102.6,42.4 ),
  array( "Maine",1274923,651901,35384.65,4523.1,30861.55,41.3,21.1 ),
  array( "Maryland",5296486,2145283,12406.68,2632.86,9773.82,541.9,219.5 ),
  array( "Massachusetts",6349097,2621989,10554.57,2714.55,7840.02,809.8,334.4 ),
  array( "Michigan",9938444,4234279,96716.11,39912.28,56803.82,175,74.5 ),
  array( "Minnesota",4919479,2065946,86938.87,7328.79,79610.08,61.8,26 ),
  array( "Mississippi",2844658,1161953,48430.19,1523.24,46906.96,60.6,24.8 ),
  array( "Missouri",5595211,2442017,69704.31,818.39,68885.93,81.2,35.5 ),
  array( "Montana",902195,412633,147042.4,1489.96,145552.43,6.2,2.8 ),
  array( "Nebraska",1711263,722668,77353.73,481.31,76872.41,22.3,9.4 ),
  array( "Nevada",1998257,827457,110560.71,734.71,109825.99,18.2,7.5 ),
  array( "New Hampshire",1235786,547024,9349.94,381.84,8968.1,137.8,61 ),
  array( "New Jersey",8414350,3310275,8721.3,1303.96,7417.34,1134.4,446.3 ),
  array( "New Mexico",1819046,780579,121589.48,233.96,121355.53,15,6.4 ),
  array( "New York",18976457,7679307,54556,7342.22,47213.79,401.9,162.6 ),
  array( "North Carolina",8049313,3523944,53818.51,5107.63,48710.88,165.2,72.3 ),
  array( "North Dakota",642200,289677,70699.79,1723.86,68975.93,9.3,4.2 ),
  array( "Ohio",11353140,4783051,44824.9,3876.53,40948.38,277.3,116.8 ),
  array( "Oklahoma",3450654,1514400,69898.19,1231.13,68667.06,50.3,22.1 ),
  array( "Oregon",3421399,1452709,98380.64,2383.85,95996.79,35.6,15.1 ),
  array( "Pennsylvania",12281054,5249750,46055.24,1238.63,44816.61,274,117.1 ),
  array( "Rhode Island",1048319,439837,1545.05,500.12,1044.93,1003.2,420.9 ),
  array( "South Carolina",4012012,1753670,32020.2,1910.73,30109.47,133.2,58.2 ),
  array( "South Dakota",754844,323208,77116.49,1231.85,75884.64,9.9,4.3 ),
  array( "Tennessee",5689283,2439443,42143.27,926.15,41217.12,138,59.2 ),
  array( "Texas",20851820,8157575,268580.82,6783.7,261797.12,79.6,31.2 ),
  array( "Utah",2233169,768594,84898.83,2755.18,82143.65,27.2,9.4 ),
  array( "Vermont",608827,294382,9614.26,364.7,9249.56,65.8,31.8 ),
  array( "Virginia",7078515,2904192,42774.2,3180.13,39594.07,178.8,73.3 ),
  array( "Washington",5894121,2451075,71299.64,4755.58,66544.06,88.6,36.8 ),
  array( "West Virginia",1808344,844623,24229.76,152.03,24077.73,75.1,35.1 ),
  array( "Wisconsin",5363675,2321144,65497.82,11187.72,54310.1,98.8,42.7 ),
  array( "Wyoming",493782,223854,97813.56,713.16,97100.4,5.1,2.3 ),
  array( "Puerto Rico",3808610,1418476,5324.5,1899.94,3424.56,1112.1,414.2 )
);
?>
<html>
<head>
<script language="Javascript">
var width = 300;
var height = 300;

var axes = [ "population", "housing_units", "total_area", "total_water", "total_land", "people_density", "housing_density" ];

var data = [
<?php $first = true; foreach( $states as $state ) { if ( !$first ) echo( "," ); ?>
{ state: "<?php echo($state[0]); ?>", population: <?php echo($state[1]); ?>,
  housing_units: <?php echo($state[2]); ?>, total_area: <?php echo($state[3]); ?>,
  total_water: <?php echo($state[4]); ?>, total_land: <?php echo($state[5]); ?>,
  people_density: <?php echo($state[6]); ?>, housing_density: <?php echo($state[7]); ?> }
<?php $first = false; } ?>
];

var axmin = {};
var axmax = {};

for( axind in axes )
{
    axmin[ axes[axind] ] = 100000000;
    axmax[ axes[axind] ] = -100000000;
}
for( ind in data )
{
  row = data[ind];
  for( axind in axes )
  {
    axis = axes[axind];
    if ( row[axis] < axmin[axis] )
      axmin[axis] = row[axis];
    if ( row[axis] > axmax[axis] )
      axmax[axis] = row[axis];
  }
}

function cleargraph()
{
    graph = document.getElementById( "graphdiv" );
    graph.innerHTML = "";
}

function adddot( value, size, x, y, text )
{
    var left = x - ( size / 2 );
    var top = width - ( y + ( size / 2 ) );

    var cleft = "auto";
    var ctop = "auto";
    var cright = "auto";
    var cbottom = "auto";

    if ( left < 0 ) { cright = ( left * -1 ) + "px"; }
    if ( left + size > width ) { cleft = ( width - left ) + "px"; }
    if ( top < 0 ) { ctop = ( top * -1 ) + "px"; }
    if ( top + size > height ) { cbottom = ( height - top ) + "px"; }

    if ( value <= 0.25 )
      img = "ltgray.gif";
    else if ( value <= 0.50 )
      img = "gray.gif";
    else if ( value <= 0.75 )
      img = "dkgray.gif";
    else
      img = "black.gif";

    html = "<img src=\""+img+"\" width=\""+size+"\" height=\""+size+"\" ";
    html += "style=\"position:absolute;left:"+left+"px;top:"+top+"px;";
    html += "clip:rect( "+ctop+" "+cleft+" "+cbottom+" "+cright+" );";
    html += "\" onclick=\"alert(\'"+text+"\')\"/>";

    graph = document.getElementById( "graphdiv" );
    graph.innerHTML += html;
}

function calculate_value( row, field, min, max )
{
    var val = row[ field ] - axmin[ field ];
    var scale = ( max - min ) / ( axmax[ field ] - axmin[ field ] );
    return min + ( scale * val );
}

function drawgraph()
{
    cleargraph();

    var xvar = document.getElementById( "bottom" ).value;
    var yvar = document.getElementById( "side" ).value;
    var sizevar = document.getElementById( "size" ).value;
    var valuevar = document.getElementById( "color" ).value;

    for( rowind in data )
    {
        var row = data[rowind];
        var x = calculate_value( row, xvar, 5, width - 5 );
        var y = calculate_value( row, yvar, 5, height - 5 );
        var size = calculate_value( row, sizevar, 5, 30 );
        var value = calculate_value( row, valuevar, 0, 1 );
        adddot( value, size, x, y, row.state );
    }
}

function buildselect( axis, current )
{
    var html = "<select id=\""+axis+"\" onchange=\"drawgraph()\">";
    for( axind in axes )
    {
      var selected = "";
      if ( axes[axind] == current )
        selected = " selected=\"true\"";
      html += "<option value=\""+axes[axind]+"\""+selected+">"+axes[axind]+"</option>";
    }
    html += "</select>";
    document.write( html );
}
</script>
</head>
<body onload="drawgraph();">
Side: <script language="Javascript">buildselect( "side", "population" );</script> 
Bottom: <script language="Javascript">buildselect( "bottom", "housing_units" );</script> 
Size: <script language="Javascript">buildselect( "size", "total_area" );</script> 
Color: <script language="Javascript">buildselect( "color", "total_water" );</script> 
<div style="position:relative;border:1px solid #eee; clip:rect(0px 0px 300px 300px); width:300px; height:300px;" id="graphdiv">
</div>
</body>
</html>
