#ifndef NODES_H
#define NODES_H

extern int calc_error(char * s);

class Node 
{
 public:
  Node() {}
  virtual ~Node() {}
  virtual Value  eval(){return value_error(" trying to evaluate an illegal node");}
  virtual void print() {calc_error(" apparently no print defined for this Node \n");}
};

class Binop : public Node 
{
 public:
  Node *left, *right;
  Binop(Node *l, Node *r) { left = l; right = r;}
  ~Binop() { delete left; delete right;}
  void print() {printf("Error: apparently no print defined for this Binop \n");}
};

class Plus : public Binop 
{
 public:
  Plus(Node *l, Node *r) : Binop(l,r) {}
  Value  eval() 
    {
      Value  l = left->eval();
      return l + right->eval();
    }
  void print() {printf("(");left->print();printf(" + ");right->print();printf(")");}
};

class Minus : public Binop 
{
 public:
  Minus(Node *l, Node *r) : Binop(l,r) {}
  Value  eval() 
    {
      Value  l = left->eval();
      return l - right->eval();
    }
  void print() {printf("(");left->print();printf(" - ");right->print();printf(")");}
};


class Times : public Binop 
{
 public:
  Times(Node *l, Node *r) : Binop(l,r) {}
  Value  eval() 
    {
      Value  l = left->eval();
      return l * right->eval();
    }
  void print() {printf("(");left->print();printf(" * ");right->print();printf(")");}
};

class Div : public Binop 
{
 public:
  Div(Node *l, Node *r) : Binop(l,r) {}
  Value  eval() 
    {
      Value  l = left->eval();
      return l / right->eval();
    }
  void print() {printf("(");left->print();printf(" / ");right->print();printf(")");}
};

class Power : public Binop 
{
 public:
  Power(Node *l, Node *r) : Binop(l,r) {}
  Value  eval() 
    {
      Value  l = left->eval();
      return pow(l, right->eval());
    }
  void print() {printf("(");
		left->print();
		printf("^");
		right->print();
		printf(")");}
};


class Uminus : public Node 
{
  Node *operand;
 public:
  Uminus (Node *o) {operand = o;}
  ~Uminus() {delete operand;}
  Value  eval() {return - operand->eval();}
  void print() {printf("(-");operand->print();printf(")");}
};

class Uplus : public Node 
{
  Node *operand;
 public:
  Uplus (Node *o) {operand = o;}
  ~Uplus() {delete operand;}
  Value  eval() {return + operand->eval();}
  void print() {printf("(+");operand->print();printf(")");}
};

typedef Value (*Funptype)(Value &);

typedef struct _fun_table {
  char *name;
  Funptype fun;
} FunTable;

extern Funptype GetFun(char *);

class UnaryFun : public Node
{
  Node *operand;
  Funptype fun;
  char *name;
 public:
  UnaryFun() { operand = (Node *)NULL; fun = (Funptype)NULL; }
  ~UnaryFun() {delete operand; delete name;}
  UnaryFun(char * nm,Node *op) { operand = op; 
				 fun = GetFun(nm); 
				 name = strcpy( new char[ strlen(nm)+1 ], nm);
			       }
  Value eval(); 
  void print() {printf("%s",name);printf("(");operand->print();printf(")");}
};
  
inline Value UnaryFun::eval()
{
  Value val;
  val = operand->eval();

  if (!val.IsError() && fun)
    return (*fun)(val);
  return val;
}

class Literal : public Node 
{
  Value  value;
 public:
  Literal() {}
  Literal(int v) {value = (Value)v;}
  Literal(float v) {value = (Value)v;}
  Literal(double v) {value = (Value)v;}
  Value  eval() {return value;}
  void print() {value.print();}
};

/* --------------------------------------------------------- */
/*
 * Variable symbol table
 */

class Nament
{
public:
  char *name;
  Value  value;
  Nament *next;
  Nament() {name = NULL; next = NULL;}
  Nament (char *nm, Nament *n)
    {
      name = strcpy( new char[ strlen(nm)+1 ], nm);
      next = n;
    }
};

extern Nament *symtab;
extern int token;
extern char lexeme[128];

class Id : public Node
{
  Nament *entry;
  Nament *look(char *);
 public:
  Id (char *nm) { entry = look( nm ); }
  Value  set( Value & v ) { return entry->value = v; }
  Value  eval() { return entry->value.eval(); }
  void print() {printf("%s",entry->name);}
  char *get_name()
    {
      return strcpy(new char[ strlen(entry->name)+1 ], 
		    entry->name);
    }
};

class Assign : public Binop
{
 public:
  Assign( Id *t, Node *e) : Binop( t , e) {}
  Value  eval()
    { return ((Id *)left)->set(right->eval() ); }
  void print() {left->print();printf(" = ");right->print();}
};


extern int scan();
extern Node *Exp(), *Term(), *Factor(), *Powfactor();  
extern void AddSymtabEntry(char *,Value &);
enum { ID = 257, FUN, INT, FLOAT, EOLN, BAD };

#endif NODES_H

