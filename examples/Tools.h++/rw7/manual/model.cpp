/*
 * This example is from the Tools.h++ manual, version 7
 *
 * Copyright (c) 1989-1999 Rogue Wave Software, Inc.  All Rights Reserved.
 *
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software,
 * Inc. pursuant to a written license agreement and may be used, copied,
 * transmitted, and stored only in accordance with the terms of such
 * license and with the inclusion of the above copyright notice.  This
 * computer software or any other copies thereof may not be provided or
 * otherwise made available to any other person.
 *
 * U.S. Government Restricted Rights.  This computer software is provided
 * with Restricted Rights.  Use, duplication, or disclosure by the
 * Government is subject to restrictions as set forth in subparagraph (c)
 * (1) (ii) of The Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013 or subparagraphs (c) (1) and (2) of the
 * Commercial Computer Software – Restricted Rights at 48 CFR 52.227-19,
 * as applicable.  Manufacturer is Rogue Wave Software, Inc., 5500
 * Flatiron Parkway, Boulder, Colorado 80301 USA.
 */
#include <rw/model.h>

class Dial : public RWModelClient
{
     int dialNumber;

  public:

     Dial(int dialNumber);
     virtual void updateFrom(RWModel* m, void* d);

};


class Thermostat : public RWModel
{
    double setting;

  public:

    Thermostat( Dial* d )
      { addDependent(d); setting = 0; }

    double temperature() const
      { return setting; }

    void setTemperature(double t)
      { setting = t; changed(); }
};


void Dial::updateFrom(RWModel* m, void*)
{
  Thermostat* t = (Thermostat*)m;
  double temp = t -> temperature();

  // Redraw graphic.
  cout << "Dial #" << dialNumber
       << " says " << temp << endl;
}


Dial::Dial(int num) : dialNumber(num)
{;}


main()
{
   Dial one(1);
   Dial two(2);

   Thermostat therm(&one);

   therm.setTemperature(77);
   therm.setTemperature(-4);

   therm.addDependent(&two);

   therm.setTemperature(47); 

   return 0;
}
