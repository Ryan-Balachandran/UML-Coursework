// J0 LANGUAGE
// e ::= v | (+ e e) | (* e e)
// v ::= number


// SEXPR
// se ::= empty | (Cons se se) | string
// Cons = pair


// J1 LANGUAGE
//     function  arguments
//           \   /       (if condition true false)
// e ::= v | (e e ...) | (if e e e)
// v ::= number | boolean | prim
// prim ::= '+' | '*' | '/' | '-' | '<=' | '<' | '=' | '>' | '>='


// CONTEXT
// C ::= hole | (if C e e) | (if e C e) | (if e e C) | (e... C e...)


#include <iostream>
#include <string>
using namespace std;



// JEXPRESSIONS ----------------------------------------------------------------------- JEXPRESSIONS
// interface
// e ::= v | (+ e e) | (* e e)
class JExpr
{
public:
    virtual bool isValue() = 0;                         // determine if expression is a value
    virtual string show() = 0;                          // pretty printer to print out expression
    virtual JExpr* interp() = 0;                        // big-step interpreter
    virtual int get_type() = 0;                         // substitute for instanceof in Java
};


// v ::= prim
// prim ::= '+' | '*' | '/' | '-' | '<=' | '<' | '=' | '>' | '>='s
class JPrim: public JExpr
{
public:
    JPrim(string p) {this->p = p;}                      // single argument constructor; takes a string s
    bool isValue() {return true;}                       // JPrim is a value
    string show() {return p;}                           // pretty printer for JPrim
    JExpr* interp() {return this;}
    int get_type() {return 7;}                          // JPrim is type 7
    string get_value() const {return p;}                // getter; access to private

private:
    string p;
};


// v ::= number
class JNumber: public JExpr
{
public:
    JNumber(int n) {this->n = n;}                       // single argument constructor; takes an integer n
    bool isValue() {return true;}                       // JNumber is a value
    string show() {return to_string(this->n);}          // convert value to a string; pretty printer for JNumber
    JExpr* interp() {return this;}                      // return the value
    int get_type() {return 8;}                          // JNumber is type 8
    int get_value() const {return n;}                   // getter; access to private

private:
    int n;
};


// v ::= boolean
class JBool: public JExpr
{
public:
    JBool(bool b) {this->b = b;}                        // single argument constructor; takes a boolean b
    bool isValue() {return true;}                       // JBool is a value
    string show() {return to_string(this->b);}          // pretty printer for JBool
    JExpr* interp() {return this;}
    int get_type() {return 9;}                          // JBool is type 9
    bool get_value() const {return b;}                  // getter; access to private variable s

private:
    bool b;
};


// e ::= (if e e e)
class JIf: public JExpr
{
public:
    JExpr *cond, *tbr, *fbr;                            // JExpr data type with pointers to condition, true branch, and false branch

    JIf(JExpr *cond, JExpr *tbr, JExpr *fbr)            // three argument constructor; takes three JExpr pointers to cond, tbr, and fbr
    {
        this->cond = cond;
        this->tbr = tbr;
        this->fbr = fbr;
    }

    bool isValue() {return false;}                      // JIf is not a value

    string show()                                       // pretty printer for JIf
    {
        return "(if " + this->cond->show() + " " + this->tbr->show() + " " + this->fbr->show() + ")";
    }

    JExpr* interp()
    {
        JExpr* condv = this->cond->interp();

        if((condv->get_type() == 9) && ((JBool*)condv)->get_value() == false)
            return this->fbr->interp();
        else
            return this->tbr->interp();
    }

    int get_type() {return 10;}                          // JIf is type 10
};


class JCons: public JExpr
{
public:
    JExpr *lhs, *rhs;                                   // JExpr data type with pointers to lhs and rhs

    JCons(JExpr *lhs, JExpr *rhs)                       // two argument constructor; takes two JExpr pointers to lhs and rhs
    {
        this->lhs = lhs;
        this->rhs = rhs;
    }

    bool isValue() {return false;}                      // JCons is not a value

    string show()                                       // pretty printer for JCons
    {
        return "(" + this->lhs->show() + " " + this->rhs->show() + ")";
    }

    JExpr* interp()
    {
        return new JCons(this->lhs->interp(), this->rhs->interp());
    }

    int get_type() {return 13;}                          // JBool is type 13
};


class JApp: public JExpr
{
public:
    JExpr *fun, *args;                                  // JExpr data type with pointers to function and arguments

    JApp(JExpr *fun, JExpr *args)                       // two argument constructor; takes two JExpr pointers to fun and args
    {
        this->fun = fun;
        this->args = args;
    }

    bool isValue() {return false;}                      // JApp is not a value

    string show()                                       // pretty printer for JApp
    {
        return "(@ " + this->fun->show() + " " + this->args->show() + ")";
    }

    JExpr* interp()
    {
      JExpr* which_fun = this->fun->interp();
      JExpr* arg_vals = this->args->interp();

      string p = ((JPrim*)which_fun)->get_value();
      int lhs = ((JNumber*)((JCons*)arg_vals)->lhs)->get_value();
      int rhs = ((JNumber*)((JCons*)((JCons*)arg_vals)->rhs)->lhs)->get_value();

      if (p == "+") {return new JNumber(lhs + rhs);}
      if (p == "*") {return new JNumber(lhs * rhs);}
      if (p == "/") {return new JNumber(lhs / rhs);}
      if (p == "-") {return new JNumber(lhs - rhs);}
      if (p == "<") {return new JBool(lhs < rhs);}
      if (p == "<=") {return new JBool(lhs <= rhs);}
      if (p == "==") {return new JBool(lhs == rhs);}
      if (p == ">") {return new JBool(lhs > rhs);}
      if (p == ">=") {return new JBool(lhs >= rhs);}
      if (p == "!=") {return new JBool(lhs != rhs);}

      return new JNumber(666);
    }

    int get_type() {return 11;}                          // JApp is type 11
};


class JNull: public JExpr
{
public:
    JNull() {}                                          // default constructor
    bool isValue() {return true;}                       // JNull is a value
    string show() {return "⊥";}                         // pretty printer for JNull
    JExpr* interp() {return this;}
    int get_type() {return 12;}                          // JNull is type 12
};
// JEXPRESSIONS ----------------------------------------------------------------------- JEXPRESSIONS




// SEXPRESSIONS ----------------------------------------------------------------------- SEXPRESSIONS
// interface
// se ::= empty | (Cons se se) | string
class Sexpr
{
public:
    virtual string show() = 0;                          // print out Sexpr
    virtual int get_type() = 0;                         // substitute for instanceof in Java
};


// se ::= string
class SE_String: public Sexpr
{
public:
    SE_String(string s) {this->s = s;}                  // single argument constructor; takes a string s
    string show() {return s;}                           // pretty printer for SE_String
    int get_type() {return 3;}                          // SE_String is type 3
    string get_value() const {return s;}                // getter; access to private variable s

private:
    string s;
};


// se ::= number
class SE_Number: public Sexpr
{
public:
    SE_Number(int n) {this->n = n;}                     // single argument constructor; takes an integer s
    string show() {return to_string(this->n);}          // pretty printer for SE_Number
    int get_type() {return 4;}                          // SE_Number is type 4
    int get_value() const {return n;}                   // getter; access to private variable n

private:
    int n;
};


// se ::= empty
class SE_MT: public Sexpr
{
public:
    SE_MT() {}                                          // empty string default constructor
    string show() {return "⊥";}                         // pretty printer for SE_MT
    int get_type() {return 5;}                          // SE_MT is type 5
};


// se ::= (Const se se)
class SE_Cons: public Sexpr
{
public:
    Sexpr *lhs, *rhs;                                   // Sexpr data type with pointers to lhs and rhs

    string show()                                       // pretty printer for SE_Cons
    {
        return "(" + this->lhs->show() + " " + this->rhs->show() + ")";

    }

    SE_Cons(Sexpr *lhs, Sexpr *rhs)                     // two argument constructor; takes two Sexpr pointers to lhs and rhs
    {
        this->lhs = lhs;
        this->rhs = rhs;
    }

    int get_type() {return 6;}
};
// SEXPRESSIONS ----------------------------------------------------------------------- SEXPRESSIONS



// CONTEXT --------------------------------------------------------------------------------- CONTEXT
class Expr
{

};

class Context
{

};

class Hole: public Context
{

};

class IfC: public Context
{
public:
    Context *c;
};

class AppC: public Context
{

};
// CONTEXT --------------------------------------------------------------------------------- CONTEXT



//*************** TEST SUIT HELPER FUNCTIONS FOR JEXPRESSIONS ***************//
JExpr *JN(int n) {return new JNumber(n);}
JExpr *JA(JExpr *lhs, JExpr *rhs) {return new JApp(new JPrim("+"), new JCons(lhs, new JCons(rhs, new JNull())));}
JExpr *JM(JExpr *lhs, JExpr *rhs) {return new JApp(new JPrim("*"), new JCons(lhs, new JCons(rhs, new JNull())));}

Sexpr *SApp(string op, Sexpr *lhs, Sexpr *rhs)
{
    return new SE_Cons(new SE_String(op),
                       new SE_Cons(lhs,
                                   new SE_Cons(rhs,
                                               new SE_MT())));
}
//*************** TEST SUIT HELPER FUNCTIONS FOR JEXPRESSIONS ***************//


//***************** TEST SUIT HELPER FUNCTIONS FOR SEXPR'S *****************//
Sexpr *SN(int n) {return new SE_Number(n);}                             // function pointer to SE_Number class
Sexpr *SA(Sexpr *lhs, Sexpr *rhs) {return SApp("+", lhs, rhs); }
Sexpr *SM(Sexpr *lhs, Sexpr *rhs) {return SApp("*", lhs, rhs); }

Sexpr *SIf(Sexpr *cond, Sexpr *lhs, Sexpr *rhs)
{
    return new SE_Cons(new SE_String("if"),
                       new SE_Cons(cond,
                                   new SE_Cons(lhs,
                                               new SE_Cons(rhs,
                                                           new SE_MT()))));
}
//***************** TEST SUIT HELPER FUNCTIONS FOR SEXPR'S *****************//



JExpr *desugar(Sexpr *se)
{
    // se instance of SE_Num
    // desugar 'n = n                   (' encoding of a number)
    if(se->get_type() == 4)
    {
        return JN(((SE_Number*)se)->get_value());
    }


    // desugar('+) = 0
    if(se->get_type() == 6
       && (((SE_Cons*)se)->lhs)->get_type() == 3
       && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "+"
       && (((SE_Cons*)se)->rhs)->get_type() == 5)
    {
        return JN(0);
    }


    // desugar ('+ lhs rhs ...) = (+ desugar(lhs) desugar('+ rhs ...))
    // Don't care if right hand sid is empty anymore
    if(se->get_type() == 6
       && (((SE_Cons*)se)->lhs)->get_type() == 3
       && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "+"
       && (((SE_Cons*)se)->rhs)->get_type() == 6)
    {
        return JA(desugar(((SE_Cons*)((SE_Cons*)se)->rhs)->lhs),
                  desugar(new SE_Cons(((SE_Cons*)se)->lhs, ((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)));
    }


    // desugar ('- lhs) = (* -1 desugar(lhs))
    if(se->get_type() == 6
       && (((SE_Cons*)se)->lhs)->get_type() == 3
       && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "-"
       && (((SE_Cons*)se)->rhs)->get_type() == 6
       && (((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->get_type() == 5)
    {
        return JM(JN(-1), desugar(((SE_Cons*)((SE_Cons*)se)->rhs)->lhs));
    }


    // desugar ('- e e) = (+ desugar(lhs) desugar('- rhs))
    if(se->get_type() == 6
       && (((SE_Cons*)se)->lhs)->get_type() == 3
       && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "-"
       && (((SE_Cons*)se)->rhs)->get_type() == 6
       && (((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->get_type() == 6
       && (((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->rhs)->get_type() == 5)
    {
        return JA(desugar(((SE_Cons*)((SE_Cons*)se)->rhs)->lhs),
                  JM(JN(-1), desugar(((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->lhs)));
    }


    // desugar('*) = 1
    if(se->get_type() == 6
       && (((SE_Cons*)se)->lhs)->get_type() == 3
       && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "*"
       && (((SE_Cons*)se)->rhs)->get_type() == 5)
    {
        return JN(1);
    }


    // desugar ('* lhs rhs ...) = (* desugar(lhs) desugar('* rhs ...))
    // Don't care if right hand sid is empty anymore
    if(se->get_type() == 6
        && (((SE_Cons*)se)->lhs)->get_type() == 3
        && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "*"
        && (((SE_Cons*)se)->rhs)->get_type() == 6)
     {
         return JM(desugar(((SE_Cons*)((SE_Cons*)se)->rhs)->lhs),
                   desugar(new SE_Cons(((SE_Cons*)se)->lhs, ((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)));
     }


    //JApp
    if(se->get_type() == 6
       && (((SE_Cons*)se)->lhs)->get_type() == 3
       && (((SE_Cons*)se)->rhs)->get_type() == 6
       && (((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->get_type() == 6
       && (((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->rhs)->get_type() == 5)
    {
        return new JApp(new JPrim(((SE_String*)((SE_Cons*)se)->lhs)->get_value()),
                        new JCons(desugar(((SE_Cons*)((SE_Cons*)se)->rhs)->lhs),
                                  new JCons(desugar(((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->lhs),
                                            new JNull())));
    }


    //JIf
    if (se->get_type() == 6
        && (((SE_Cons*)se)->lhs)->get_type() == 3
        && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "if"
        && (((SE_Cons*)se)->rhs)->get_type() == 6
        && (((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->get_type() == 6
        && (((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->rhs)->get_type() == 6
        && (((SE_Cons*)((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->rhs)->rhs)->get_type() == 5)
    {
        return new JIf(desugar(((SE_Cons*)((SE_Cons*)se)->rhs)->lhs),
                       desugar(((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->lhs),
                       desugar(((SE_Cons*)((SE_Cons*)((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->rhs)->lhs) );
    }


    return JN(666);                                     // if there's a problem
}



static int tests_passed = 0;                            // integer counter for test function

// TEST FUNCTION TO PRINT OUT RESULT
void test(Sexpr *se, JExpr *expected)
{
    JExpr *e = desugar(se);                             // Convert Sexpr's into JExpr's

    //cout << se->show() << " desugars to " << e->show() << endl;

    JExpr *actual = e->interp();                        // interpret expression and store it in actual

    if(!(actual->show() == expected->show()))
    {
        cout << e->show() << " = " << actual->show() << " but should = " << expected->show() << endl;
    }
    else
    {
        tests_passed++;
    }
}

void test_num(Sexpr *se, int n)
{
    test(se, JN(n));
}

int main()
{
    test_num(SN(42), 42);
    test_num(SN(7), 7);
    test_num(SA(SN(42), SN(0)), 42);
    test_num(SM(SN(42), SN(0)), 0);
    test_num(SA(SM(SN(42), SN(0)), SN(0)), 0);
    test_num(SA(SM(SN(42), SN(0)), SA(SM(SN(42), SN(0)), SN(0))), 0);
    test_num(SM(SN(54), SA(SM(SN(42), SN(6)), SN(2))), 13716);

    test_num(SA(SN(42), SN(1)), 43);
    test_num(SM(SN(42), SN(1)), 42);
    test_num(SA(SM(SN(42), SN(1)), SN(1)), 43);
    test_num(SA(SM(SN(42), SN(1)), SA(SM(SN(42), SN(1)), SN(1))), 85);




    test_num(new SE_Cons(new SE_String("+"), new SE_MT()), 0);
    test_num(new SE_Cons(new SE_String("*"), new SE_MT()), 1);

    Sexpr* three_things =
        new SE_Cons(new SE_Number(1),
                    new SE_Cons(new SE_Number(2),
                                new SE_Cons(new SE_Number(4),
                                            new SE_MT())));

    test_num(new SE_Cons(new SE_String("+"), three_things), 7);
    test_num(new SE_Cons(new SE_String("*"), three_things), 8);

    test_num(new SE_Cons(new SE_String("-"), new SE_Cons(new SE_Number(4), new SE_MT())), -4);
    test_num(new SE_Cons(new SE_String("-"), new SE_Cons(new SE_Number(4), new SE_Cons(new SE_Number(2), new SE_MT()))), 2);


    test(new SE_Cons(new SE_String("=="), new SE_Cons(new SE_Number(4), new SE_Cons(new SE_Number(2), new SE_MT()))), new JBool(false));
    test(new SE_Cons(new SE_String("=="), new SE_Cons(new SE_Number(4), new SE_Cons(new SE_Number(4), new SE_MT()))), new JBool(true));


    test(SApp("==", new SE_Number(4), new SE_Number(4)), new JBool(true));
    test(SIf(SApp("==", new SE_Number(4), new SE_Number(4)),
             new SE_Number(5),
             new SE_Number(6)), JN(5));
    test(SIf(SApp("==", new SE_Number(4), new SE_Number(2)),
             new SE_Number(5),
             new SE_Number(6)), JN(6));


    cout << endl << endl << tests_passed << " tests passed!" << endl;

    return 0;
}
