<html>
<head>
<title>JSON Test</title>
<script>
var req;

function processReqChange()
{
  if ( req.readyState == 4 && req.status == 200 )
  {
    var rows = eval( req.responseText );

    var html = "<table>";
    for( r in rows )
    {
	html += "<tr>";
	html += "<td>"+rows[r].id+"</td>";
	html += "<td>"+rows[r].first+"</td>";
	html += "<td>"+rows[r].last+"</td>";
	html += "</tr>";
    }
    html += "</table>";

    document.getElementById( "data" ).innerHTML = html;
  }
}

function getNames()
{
  if (typeof window.ActiveXObject != 'undefined' )
  {
    req = new ActiveXObject("Microsoft.XMLHTTP");
    req.onreadystatechange = processReqChange;
  }
  else
  {
    req = new XMLHttpRequest();
    req.onload = processReqChange;
  }
  try { 
    req.open( 'GET', 'http://localhost:1222/json/getdata.php', true );
  } catch( e ) {
    alert( e );
  }
  req.send("");
}
</script>
</head>
<body>
<div id="data">
</div>
<script>
getNames();
</script>
</body>
</html>
