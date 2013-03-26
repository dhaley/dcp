#ifndef VALUE_H
#define VALUE_H

const int ISINT = 1;
const int ISFLOAT = 2;
const int ISERROR = 3;


class Value 
{
  int code;
  int i;
  double f;
 public:
  Value();
  Value(Value &v) { code = v.code; i = v.i; f = v.f;}
  Value(int v);
  Value(float v);
  Value(double v);
  ~Value() {}
  Value eval();
  void print(); 
  int IsZero();
  int IsInt();
  int IsFloat();
  int IsError();
  friend Value operator+(Value &,Value &);
  friend Value operator-(Value &,Value &);
  friend Value operator+(Value &);
  friend Value operator-(Value &);
  friend Value operator*(Value &,Value &);
  friend Value operator/(Value &,Value &);
  friend Value pow(Value &,Value &);
  operator int();
  operator float();
  operator double();
};

inline Value::Value() 
{
  code = ISERROR; 
  i = 0;
  f = 0;
}

inline Value::Value(int v) 
{
  code = ISINT; 
  i = v;
  f = 0;
}

inline Value::Value(float v) 
{
  code = ISFLOAT; 
  f = v;
  i = 0;
}

inline Value::Value(double v) 
{
  code = ISFLOAT; 
  f = v;
  i = 0;
}

inline Value Value::eval()
{
  return *this;
}

inline void Value::print() 
{
  switch (code)
    {
    case ISINT:
      printf("%d",i);
      break;
    case ISFLOAT:
      printf("%f",f);
      break;
    default:
      printf("ERROR");
    }
}

inline int Value::IsZero()
{
  switch(code)
    {
    case ISINT:
      {if (i == 0) return 0; else return 1; }
    case ISFLOAT:
      {if (f == 0) return 0; else return 1; }
    default:
      return 0;
    }
}

inline int Value::IsInt()
{
  switch(code)
    {
    case ISINT:
      return 1;
    default:
      return 0;
    }
}

inline int Value::IsFloat()
{
  switch(code)
    {
    case ISFLOAT:
      return 1;
    default:
      return 0;
    }
}

inline int Value::IsError()
{
  switch(code)
    {
    case ISERROR:
      return 1;
    default:
      return 0;
    }
}

inline Value::operator int()
{
  switch(code)
    {
    case ISINT: 
      return i;
    default: 
      return (int)f;
    }
}

inline Value::operator float()
{
  switch(code)
    {
    case ISINT: 
      return (float)i;
    default: 
      return (float)f;
    }
}

inline Value::operator double()
{
  switch(code)
    {
    case ISINT: 
      return (double)i;
    default: 
      return f;
    }
}

extern Value value_error(char *);
extern void print_buff(char *buff,Value & v);

#endif VALUE_H
