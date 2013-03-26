<?

  // Dru Nelson 8/1/2005
  // Free to use and abuse

  ming_useswfversion(6);    // Important!


  $m = new SWFMovie();
  $m->setBackground(0x80, 0x80, 0x80);
  $m->setDimension(320, 240);
  $m->setRate(30.0);


  $s = new SWFShape();
  $f = $s->addFill(0xff, 0xff, 0xff);
  $s->setRightFill($f);

  $s->movePenTo (-5,  0);
  $s->drawLineTo( 5,  0);
  $s->drawLineTo( 5, -10);
  $s->drawLineTo(-5, -10);
  $s->drawLineTo(-5,  0);

  $p = new SWFSprite();
  $i = $p->add($s);
  $i->setDepth(1);
  $p->nextFrame();


  $i = $m->add($p);
  $i->setDepth(1);
  $i->moveTo(-10, -10);
  $i->setName("box");

  $m->add(new SWFAction("
  

  var data = [];
  var heights = [];
  var actual  = [];
  var timerID;

  // Animate the bars to their final position
  function anim ()
  {
    var done = true;
    for (var k = 0; k < data.length; k++)
    {
      var n = 'D' + k;

      if (heights[k] != actual[k])
         done = false;
      else
         continue;

      var diff = (heights[k] - actual[k]) / 5;
      actual[k] += diff;
      _root[n]._height = actual[k];
      if (diff < 0.1)
         actual[k] = heights[k];

    }
  if (done)
  {
    clearInterval(timerID);
    stop();
  }
  };


  // Take the XML data transformed into a JavaScript/ActionScript
  // object and display it

  function doit(o)
  {
    // Take the data and draw
    // Draw the axes
    createEmptyMovieClip ('grp', 1);
    with (grp)
    {
    lineStyle (1, 0xFFFFFF, 100);
    // X - Axis
    moveTo (40, 200);
    lineTo (280, 200);
    // Y - Axis
    moveTo (40, 200);
    lineTo (40, 20);

    // Draw the Main Title
    createTextField('title', 1, 100, 00, 100, 100);
    var fmt = new TextFormat();
    fmt.color = 0xffffff;
    fmt.font = 'Arial';

    title.text = o['TITLE']['_txt'];
    title.setTextFormat(fmt);

    // Draw the X Axis Title
    createTextField('xtitle', 2, 120, 220, 100, 100);
    var fmt = new TextFormat();
    fmt.color = 0xffffff;
    fmt.font = 'Arial';
    fmt.size = '10';

    xtitle.text = o['XAXIS']['_txt'];
    xtitle.setTextFormat(fmt);

    // Draw the Y Axis Title
    createTextField('ytitle', 3, 0, 100, 100, 100);
    var fmt = new TextFormat();
    fmt.color = 0xffffff;
    fmt.font = 'Arial';
    fmt.size = '10';

    ytitle.text = o['YAXIS']['_txt'];
    ytitle.setTextFormat(fmt);

    // Draw the Y Axis Labels
    createTextField('ylabeltop', 5, 20, 16, 20, 20);
    var fmt = new TextFormat();
    fmt.color = 0xffffff;
    fmt.font = 'Arial';
    fmt.size = '6';
    fmt.align = 'right';
    ylabeltop.text = o['YAXIS']['RANGE']['1'];
    ylabeltop.setTextFormat(fmt);

    createTextField('ylabelbot', 6, 20, 193, 20, 20);
    var fmt = new TextFormat();
    fmt.color = 0xffffff;
    fmt.font = 'Arial';
    fmt.size = '6';
    fmt.align = 'right';
    ylabelbot.text = '0';
    ylabelbot.setTextFormat(fmt);

    };    // End with(grp)



    // Draw the Data


    // Determine how many data items we have
    for (var k = 0; k < 10; k++)
    {
      if (typeof(o['DATA']['D'+k]) == 'object')
        data.push(o['DATA']['D'+k]);
    }

    // Draw the Data
    // Go through each data item and position a movie there

    var increment = 180 / data.length;
    var width = increment / 2;
    var max = Number(o['YAXIS']['RANGE']['1']);

    for (var k = 0; k < data.length; k++)
    {
      // dup the box into a new column
      var n = 'D' + k;
      duplicateMovieClip(box, n, 10+k);

      // move to final position
      _root[n]._x = 40 + ((k + 1) * increment); 
      _root[n]._y = 199.5; 
      _root[n]._width = width;

      // Set heights initially to zero, and animate later
      _root[n]._height = 0;


      // Get the data value and transform to viewport
      var n2 = 'D' + (k+1);
      var h = 180 / max * Number(o['DATA'][n2]['_txt']);

      heights.push(h);
      actual.push(0);

      var c = new Color(_root[n]);
      c.setRGB(Number(o['DATA'][n2]['COLOR']['1']));
    }

    // We are done, setup an animation timer to refresh
    // the movie clip sizes every 32 millis until they achieve
    // their final height.

    timerID = setInterval(anim, 32);
  }

  function convertToJS(nodes, o)
  {
    if (arguments.length == 1)
      o = {};

    for (var i = 0; i < nodes.length; i++)
    {

      if (nodes[i].nodeType == 1)
    {
      var tmp = convertToJS(nodes[i].childNodes);

      // Add attributes
      var attribs = nodes[i].attributes;
      for (var j in attribs)
          tmp[i] = attribs[j];

        var name = nodes[i].nodeName;

      o[name] = tmp;

    }
    else
    {
      var v = nodes[i].nodeValue;
      o._txt = v;
    }
    }

    return o;
  }


  var xml = new XML();
  xml.ignoreWhite = true;  // Otherwise lots of blank nodes created

  xml.onLoad = function(success)
  {
    if (!success)
    {
      // Do a Javascript alert here through a url
      return;
    }
    var o = convertToJS(this.childNodes[0].childNodes);

    doit(o);
  };
  xml.load('data.php');
  
  "));
  $m->nextFrame();

  header('Content-type: application/x-shockwave-flash');
  $m->output();

?>

