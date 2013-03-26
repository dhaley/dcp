#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "Value.h"


Value value_error(char * s)
{
  Value val;
  printf("Value Error: %s \n",s);
  return val;
}

void print_buff(char *buff,Value & v)
{
  int i;
  float f;
  
  if (v.IsInt())
    {
      i = int(v);
      sprintf(buff,"%d",i);
    }
  else if (v.IsFloat())
    {
      f = (float)v;
      sprintf(buff,"%f",f);
    }
  else
    sprintf(buff,"%s","ERROR");
}

Value operator+(Value & v1,Value & v2)
{
  Value val;
  if ((v1.code == ISERROR) || (v2.code == ISERROR)) return val;
  switch(v1.code)
    {
    case ISINT:
      {
	switch(v2.code)
	  {
	  case ISINT:
	    val.code = ISINT;
	    val.i = (v1.i) + (v2.i);
	    return val;
	  default:
	    val.code = ISFLOAT;
	    val.f = (double)(v1.i) + (v2.f);
	    return val;
	  }
      }
    default:
      switch(v2.code)
	{
	case ISINT:
	  val.code = ISFLOAT;
	  val.f = (v1.f) + (double)(v2.i);
	  return val;
	default:
	  val.code = ISFLOAT;
	  val.f = (v1.f) + (v2.f);
	  return val;
	}
    }
}

Value operator-(Value & v1,Value & v2)
{
  Value val;
  if ((v1.code == ISERROR) || (v2.code == ISERROR)) return val;
  switch(v1.code)
    {
    case ISINT:
      {
	switch(v2.code)
	  {
	  case ISINT:
	    val.code = ISINT;
	    val.i = (v1.i) - (v2.i);
	    return val;
	  default:
	    val.code = ISFLOAT;
	    val.f = (double)(v1.i) - (v2.f);
	    return val;
	  }
      }
    default:
      switch(v2.code)
	{
	case ISINT:
	  val.code = ISFLOAT;
	  val.f = (v1.f) - (double)(v2.i);
	  return val;
	default:
	  val.code = ISFLOAT;
	  val.f = (v1.f) - (v2.f);
	  return val;
	}
    }
}


Value operator-(Value & v)
{
  Value val;
  if (v.code == ISERROR) return val;
  switch(v.code)
    {
    case ISINT:
      val.code = ISINT;
      val.i = -(v.i);
      return val;
    default:
      val.code = ISFLOAT;
      val.f = -(v.f);
      return val;
    }
}


Value operator+(Value & v)
{
  Value val;
  if (v.code == ISERROR) return val;
  switch(v.code)
    {
    case ISINT:
      val.code = ISINT;
      val.i = (v.i);
      return val;
    default:
      val.code = ISFLOAT;
      val.f = (v.f);
      return val;
    }
}


Value operator*(Value & v1,Value & v2)
{
  Value val;
  if ((v1.code == ISERROR) || (v2.code == ISERROR)) return val;
  switch(v1.code)
    {
    case ISINT:
      {
	switch(v2.code)
	  {
	  case ISINT:
	    val.code = ISINT;
	    val.i = (v1.i) * (v2.i);
	    return val;
	  default:
	    val.code = ISFLOAT;
	    val.f = (double)(v1.i) * (v2.f);
	    return val;
	  }
      }
    default:
      switch(v2.code)
	{
	case ISINT:
	  val.code = ISFLOAT;
	  val.f = (v1.f) * (double)(v2.i);
	  return val;
	default:
	  val.code = ISFLOAT;
	  val.f = (v1.f) * (v2.f);
	  return val;
	}
    }
}


Value pow(Value & v1,Value & v2)
{
  Value val;
  if ((v1.code == ISERROR) || (v2.code == ISERROR)) return val;
  switch(v1.code)
    {
    case ISINT:
      {
	switch(v2.code)
	  {
	  case ISINT:
	    val.code = ISINT;
	    if (((v1.i < 0)&&(v2.i <= 0)) || ((v1.i < 0)&&(v2.IsInt())))
	      {
		return value_error(" illegal exponentiation");
	      }
	    else
	      {
		val.i = (int)pow((double)v1.i,v2.i);
		return val;
	      }
	  default:
	    val.code = ISFLOAT;
	    if (((v1.i < 0)&&(v2.f <= 0)) || ((v1.i < 0)&&(v2.IsInt())))
	      {
		return value_error(" illegal exponentiation");
	      }
	    else
	      {
		val.f = pow((double)(v1.i),v2.f);
		return val;
	      }
	  }
      }
    default:
      switch(v2.code)
	{
	case ISINT:
	  val.code = ISFLOAT;
	  if (((v1.f < 0)&&(v2.i <= 0)) || ((v1.f < 0)&&(v2.IsInt())))
	    {
	      return value_error(" illegal exponentiation");
	    }
	  else
	    {
	      val.f = pow(v1.f,(double)(v2.i));
	      return val;
	    }
	default:
	  val.code = ISFLOAT;
	  if (((v1.f < 0)&&(v2.f <= 0)) || ((v1.f <  0)&&(v2.IsInt())))
	    {
	      return value_error(" illegal exponentiation");
	    }
	  else
	    {
	      val.f = pow(v1.f,v2.f);
	      return val;
	    }
	}
    }
}


Value operator/(Value & v1,Value & v2)
{
  Value val;
  if ((v1.code == ISERROR) || (v2.code == ISERROR)) return val;
  switch(v1.code)
    {
    case ISINT:
      {
	switch(v2.code)
	  {
	  case ISINT:
	    val.code = ISINT;
	    if (v2.i == 0)
	      {
		value_error(" divide by 0");
		val.i = 0;
	      }
	    else
	      {
		val.i = (v1.i) / (v2.i);
	      }
	    return val;
	  default:
	    val.code = ISFLOAT;
	    if (v2.f == 0)
	      {
		value_error(" divide by 0");
		val.f = 0;
	      }
	    else
	      {
		val.f = (double)(v1.i) / (v2.f);
	      }
	    return val;
	  }
      }
    default:
      {
	switch(v2.code)
	  {
	  case ISINT:
	    val.code = ISFLOAT;
	    if (v2.i == 0)
	      {
		value_error(" divide by 0");
		val.f = 0;
	      }
	    else
	      {
		val.f = (v1.f) / (double)(v2.i);
	      }
	    return val;
	  default:
	    val.code = ISFLOAT;
	    if (v2.f == 0)
	      {
		value_error(" divide by 0");
		val.f = 0;
	      }
	    else
	      {
		val.f = (v1.f) / (v2.f);
	      }
	    return val;
	  }
      }
      
    }
}

