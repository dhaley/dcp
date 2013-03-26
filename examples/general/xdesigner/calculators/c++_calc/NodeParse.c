#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "Value.h"
#include "Nodes.h"

int token;
char lexeme[128];
Nament *symtab;
char *textInput;
char *textInputPtr;

char GetNextChar()
{
  char c;

  c = *textInputPtr;
  textInputPtr++;
  return c;
}

void UnGetChar(char c)
{
  textInputPtr--;
  *textInputPtr = c;
}

extern Node *Exp(), *Term(), *Factor();  

/* ---------------------------------------------------------------- */

/*
 * Pre-defined functions
 */

Value Vsin(Value &v)
{
  Value val;
  if (!v.IsError())
    val = (Value) sin((double)v);
  return val;
}

Value Vcos(Value &v)
{
  Value val;
  if (!v.IsError())
    val = (Value) cos((double)v);
  return val;
}

Value Vatan(Value &v)
{
  Value val;
  if (!v.IsError())
    val = (Value) atan((double)v);
  return val;
}

Value Vlog(Value &v)
{
  Value val;
  if (!v.IsError())
    if ((double)v > 0.0)
      {
	val = (Value) log((double)v);
	return val;
      }
  return val;
}

Value Vlog10(Value &v)
{
  Value val;
  if (!v.IsError())
    if ((double)v > 0.0)
      {
	val = (Value) log10((double)v);
	return val;
      }
  return val;
}

static FunTable PreDefinedFuns[] = 
{
  {"sin", Vsin},
  {"cos", Vcos},
  {"atan", Vatan},
  {"loge", Vlog},
  {"log10", Vlog10}
};

Funptype GetFun(char *nm)
{
  int i;
  
  for(i = 0; i < 5; i++)
    {
      if (strcmp(nm,PreDefinedFuns[i].name) == 0)
	return(PreDefinedFuns[i].fun);
    }
  return((Funptype)NULL);
}


/* ---------------------------------------------------------------- */

/* 
 * Error function
 */

int calc_error(char * s)
{
  printf("Calculation Error: \"%s\" \n",s);
  return 0;
}

/* ---------------------------------------------------------------- */

/* 
 * look() member funciton for ID
 */

Nament * Id::look(char *nm)
{
  for( Nament *p = symtab; p; p = p->next )
    if (strcmp(p->name, nm) == 0)
      return p;
  return symtab = new Nament( nm, symtab );
}
/* ---------------------------------------------------------------- */

/* 
 * Add a name value pair to the symtab...used for predefined constants
 */

void AddSymtabEntry(char * nm,Value & v)
{
  symtab = new Nament(nm, symtab);
  symtab->value = v;
}

/* ---------------------------------------------------------------- */

/* 
 * An escape function
 */

void eval_input()
{
  if (strcmp(lexeme,"exit") == 0)
    exit(0);
}

/* ---------------------------------------------------------------- */

/* 
 * A function for verifying that a char * represents an integer
 */

int VerifyIntString(char * int_str,int len)
{
  char ch;
  int i,isanint;
  
  isanint = 1;
  i = 0;
  
  if (len == 0) return(0);
  
  /* Read through white space */
  while(int_str[i] == ' ') 
    i = i + 1;
  
  /* Check for leading '+' or '-' */
  if ((int_str[i] == '-') || (int_str[i] == '+')) 
    i = i + 1;
  
  /* Now check the rest of the string */
  while (isanint && (i < len))
    {
      ch = int_str[i];
      isanint = isdigit(ch);
      i = i + 1;
    }
  return(isanint);
}


/* ----------------------------------------------------------------- */

int VerifyFloatString(char * float_str,int len)
{
  char ch;
  int i,isafloat,found_dot;
  
  found_dot = 0;
  isafloat = 1;
  i = 0;
  
  if (len == 0) return(0);
  
  /* Read through white space */
  while(float_str[i] == ' ')
    i = i + 1;
  
  /* Check for leading '+' or '-' */
  if ((float_str[i] == '-') || (float_str[i] == '+'))
    i = i + 1;
  
  /* Check for leading '.' */
  if (float_str[i] == '.')
    {
      found_dot = 1;
      i = i + 1;
    }
  
  /* Now check the rest of the string */
  while (isafloat && (!found_dot) && (i < len))
    {
      ch = float_str[i];
      if (ch == '.')
	found_dot = 1;
      else
	isafloat = isdigit(ch);
      i = i + 1;
    }
  while (isafloat && (i < len))
    {
      ch = float_str[i];
      isafloat = isdigit(ch);
      i = i + 1;
    }
  return(isafloat);
}


/* ----------------------------------------------------------------- */

/*
 * Scanner: return the next token in the input stream.
 *          Attributes for integer constants and identifiers
 *          dumped in global variable "lexeme".
 */

int scan()
{
  int c;
  while (1)
    switch( c = GetNextChar() )
      {
      case '+': 
      case '-':
      case '*': 
      case '/':
      case ')': 
      case '(':
      case '=':
      case '^':
        return (c);
      case ' ': 
      case '\t':
 	continue;
      case '\n':
      case '\0':
	return EOLN;
      default:
	if (isdigit ( c ) || (c == '.'))
	  {
	    char *s = lexeme;
	    do
	      {
		*s++ = c;
	      }
	    while (isdigit( c = GetNextChar() ) || (c == '.'));
	    *s = '\0';
	    UnGetChar(c);
	    if (VerifyIntString(lexeme,strlen(lexeme)))
	      {
		return INT;
	      }
	    else if (VerifyFloatString(lexeme,strlen(lexeme)))
	      {
		return FLOAT;
	      }
	    else 
	      return BAD;
	  }
	if (isalnum( c ))
	  {
	    char *s = lexeme;
	    do
	      {
		*s++ = c;
	      }
	    while (isalnum(c = GetNextChar()));
	    *s = '\0';
	    UnGetChar( c);
	    eval_input(); /* check to see if exit called */
	    /*
	     * See if the lexeme is a function name
	     */
	    if (GetFun(lexeme))
	      return FUN;
	    else
	      return ID;
	  }
	return BAD;
      }
}


/*
 * Predictive parser for a simple expression grammer
 *  
 *  Exp --> Term { (+ | -) Term }
 *  Term -->  Powfactor { ( * | / ) Powfactor }
 *  Powfactor -->  Factor { ^ Factor }
 *  Factor --> ID | INT | ( Exp ) | ID = Exp | -Factor | +Factor | Fun(Exp) 
 */

Node * Exp()
{
  Node *root = Term();
  while (1)
    switch ( token )
      {
      case '+':
	token = scan();
	root = new Plus(root, Term());
	break;
      case '-':
	token = scan();
	root = new Minus(root, Term());
	break;
      default:
	return root;
      }
}

Node *Term()
{
  Node *root = Powfactor();
  while (1)
    switch( token )
      {
      case '*':
	token = scan();
	root = new Times(root, Powfactor());
	break;
      case '/':
	token = scan();
	root = new Div(root, Powfactor());
	break;
      default:
	return root;
      }
}

Node *Powfactor()
{
  Node *root = Factor();
  while (1)
    switch( token )
      {
      case '^':
	token = scan();
	root = new Power(root, Factor());
	break;
      default:
	return root;
      }
}

Node *Factor()
{
  Node *root;
  char *fun_name;
  switch ( token )
    {
    case FUN:
      /*
       * Parse as a function call, looking
       * for left and right parens.
       */
      fun_name = strcpy( new char[ strlen(lexeme)+1 ], lexeme);
      token = scan();
      if (token == '(')
	{
	  token = scan();
	  if (token != EOLN)
	    {
	      root = new UnaryFun( fun_name, Exp());
	      delete fun_name;
	      if (token != ')')
		{
		  calc_error(" right paren not found");
		  return root = new Node();
		}
	      token = scan();
	      return root;
	    }
	}
      else
	{
	  calc_error(" left paren not found");
	  return root = new Node();
	}
    case ID:
      root = new Id(lexeme);
      token = scan();
      if ( token == '=' )
	{
	  token = scan();
	  if (token != EOLN)
	    root = new Assign( (Id *)root, Exp());
	  else
	    {
	      printf(" no assignment; set to 0\n");
	      return root = new Node;
	    }
	}
      return root;
    case INT:
      root = new Literal( atoi(lexeme) );
      token = scan();
      return root;
    case FLOAT:
      root = new Literal( atof(lexeme) );
      token = scan();
      return root;
    case '(':
      token = scan();
      root = Exp();
      if (token != ')')
	{
	  calc_error(" right paren not found.");
	  return root;
	}
      token = scan();
      return root;
    case '-':
      token = scan();
      return new Uminus( Factor() );
    case '+':
      token = scan();
      return new Uplus( Factor() );
    default:
      if (strlen(lexeme) > 0)
	calc_error(strcat(lexeme, " unrecognized token."));
      return root = new Literal( 0 );
    }
} 





