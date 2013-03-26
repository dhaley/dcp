#pragma ident   "@(#)police.h	1.8    02/02/05 SMI"

//Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved


#ifndef V_POLICE_H
#define V_POLICE_H
//
// Header file for police class for "Freeway"
//


// #include <stream.h> - Not used.


#include "maniac.h"

#define CLASS_POLICE 4

class Police : public Maniac {
 protected:
  int flash_state;		// state of flashing lights
  
 public:
  Police (int = 0, int = 0, double = 0.0, double = 0.0);

//  virtual char   *classname()       { return "Police"; }
  virtual char   *classname()       { return (char *)"Police"; }
  virtual int     classnum()        { return CLASS_POLICE; }
  virtual double  vehicle_length();
  virtual void    recalc_pos();
  virtual void    draw (Display *display, Drawable pix, GC gc, 
			int x, int y, int direction_right, int scale, 
			int xorg, int yorg, int selected);
};

#endif
