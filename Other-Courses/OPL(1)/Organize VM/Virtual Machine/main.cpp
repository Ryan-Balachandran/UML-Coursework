// J0
// e ::= v | (+ e e) | (* e e)
// v ::= number


// Sexpr
// se ::= empty | (Cons se se) | string
// Cons = pair


#include <iostream>
#include <string>
using namespace std;


// JEXPRESSION ------------------------------------------------------------------------- JEXPRESSION
// interface
// se ::= empty | (Cons se se) | string
class Sexpr
{
public:
    virtual string show() = 0;                      // print out Sexpr
    virtual int get_type() = 0;
};

// se ::= empty
class SE_MT: public Sexpr
{
public:
    SE_MT() {}
    string show() {return "⊥";}
    int get_type()                                      // SE_String is type 3
    {
        return 5;
    }
};

// se ::= string
class SE_String: public Sexpr
{
public:
    SE_String(string s) {this->s = s;}              // single argument constructor; takes a string s
    string show() {return s;}
    int get_type() {return 3;}
    string get_value() const {return s;}

private:
    string s;
};

// se ::= number
class SE_Number: public Sexpr
{
public:
    SE_Number(int n) {this->n = n;}                 // single argument constructor; takes an integer s
    string show() {return to_string(this->n);}
    int get_type() {return 4;}
    int get_value() const {return n;}

private:
    int n;
};

// se ::= (Const se se)
class SE_Cons: public Sexpr
{
public:
    Sexpr *lhs, *rhs;                               // Sexpr data type with pointers to lhs and rhs
    SE_Cons(Sexpr *lhs, Sexpr *rhs)                 // two argument constructor; takes two pointers to lhs and rhs
    {
        this->lhs = lhs;
        this->rhs = rhs;
    }
    string show()                                       
    {
        return "(" + this->lhs->show() + " " + this->rhs->show() + ")";
    }
    int get_type() {return 6;}
};
// JEXPRESSION ------------------------------------------------------------------------- JEXPRESSION



// JEXPRESSION ------------------------------------------------------------------------- JEXPRESSION
class JExpr
{
public:
    virtual bool isValue() = 0;                     // determine if JExpr is a value
    virtual string show() = 0;                      // pretty printer
    virtual int interp() = 0;                       // big-step interpreter
};


// v ::= number
class JNumber: public JExpr
{
public:
    JNumber(int n) {this->n = n;}                   // single argument constructor; takes an integer n
    bool isValue() {return true;}                   // JNumber returns a value
    string show() {return to_string(this->n);}      // pretty printer for JNumber
    int interp() {return this->n;}                  // return the value

private:
    int n;
};


// e ::= (+ e e)
class JAdd: public JExpr
{
public:
    JExpr *lhs, *rhs;                               // JExpr data type with pointers to lhs and rhs
    JAdd(JExpr *lhs, JExpr *rhs)                    // two argument constructor; takes two JExpr pointers to lhs and rhs
    {
        this->lhs = lhs;
        this->rhs = rhs;
    }
    bool isValue() {return false;}                  // JAdd does not return a value
    string show()                                   // pretty printer for JAdd
    {
        return "(" + this->lhs->show() + " + " + this->rhs->show() + ")";
    }
    int interp()                                    // add two expressions
    {
        return this->lhs->interp() + this->rhs->interp();
    }
};


// e ::= (* e e)
class JMul: public JExpr
{
public:
    JExpr *lhs, *rhs;                               // JExpr data type with pointers to lhs and rhs
    JMul(JExpr *lhs, JExpr *rhs)                    // two argument constructor; takes two JExpr pointers to lhs and rhs
    {
        this->lhs = lhs;
        this->rhs = rhs;
    }
    bool isValue() {return false;}                  // JMul does not return a value
    string show()                                   // pretty printer for JMul
    {
        return "(" + this->lhs->show() + " * " + this->rhs->show() + ")";
    }
    int interp()                                    // multiply two expressions
    {
        return this->lhs->interp() * this->rhs->interp();
    }
};
// JEXPRESSION ------------------------------------------------------------------------- JEXPRESSION



// *************** TEST SUIT HELPER FUNCTIONS FOR JEXPRESSIONS *************** //
JExpr *JN(int n) {return new JNumber(n);}
JExpr *JA(JExpr *lhs, JExpr *rhs) {return new JAdd(lhs, rhs);}
JExpr *JM(JExpr *lhs, JExpr *rhs) {return new JMul(lhs, rhs);}
// *************** TEST SUIT HELPER FUNCTIONS FOR JEXPRESSIONS *************** //



// *************** TEST SUIT HELPER FUNCTIONS FOR JEXPRESSIONS *************** //
Sexpr *SN(int n) {return new SE_Number(n);}
Sexpr *SA(Sexpr *lhs, Sexpr *rhs)
{
    return new SE_Cons(new SE_String("+"),
                       new SE_Cons(lhs,
                                   new SE_Cons(rhs,
                                               new SE_MT())));
}
Sexpr *SM(Sexpr *lhs, Sexpr *rhs)
{
    return new SE_Cons(new SE_String("*"),
                       new SE_Cons(lhs,
                                   new SE_Cons(rhs,
                                               new SE_MT())));
}
// *************** TEST SUIT HELPER FUNCTIONS FOR JEXPRESSIONS *************** //



JExpr *desugar(Sexpr *se)
{
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

    //
    if(se->get_type() == 6
       && (((SE_Cons*)se)->lhs)->get_type() == 3
       && ((SE_String*)((SE_Cons*)se)->lhs)->get_value() == "-"
       && (((SE_Cons*)se)->rhs)->get_type() == 6
       && (((SE_Cons*)((SE_Cons*)se)->rhs)->rhs)->get_type() == 5)
    {
        return JM(JN(-1), desugar(((SE_Cons*)((SE_Cons*)se)->rhs)->lhs));
    }

    //
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

    return JN(666);
}



static int tests_passed = 0;

// TEST FUNCTION TO PRINT OUT RESULT
void test(Sexpr *se, int expected)
{
    JExpr *e = desugar(se);
    
    int actual = e->interp();

    if(actual != expected)
    {
        cout << e->show() << " = " << actual << " but should = " << expected << endl;
    }
    else
    {
        tests_passed++;
    }
}



int main()
{
    cout << "*******************" << endl;
    cout << "* VIRTUAL MACHINE *" << endl;
    cout << "*******************" << endl << endl;


    test(SN(42), 42);
    test(SN(7), 7);
    test(SA(SN(42), SN(0)), 42);
    test(SM(SN(42), SN(0)), 0);
    test(SA(SM(SN(42), SN(0)), SN(0)), 0);
    test(SA(SM(SN(42), SN(0)), SA(SM(SN(42), SN(0)), SN(0))), 0);
    test(SM(SN(54), SA(SM(SN(42), SN(6)), SN(2))), 13716);
    test(SM(SN(42), SN(9)), 378);
    test(SM(SN(42), SM(SN(42), SA(SM(SN(42), SN(6)), SN(2)))), 448056);

    test(SA(SN(42), SN(1)), 43);
    test(SM(SN(42), SN(1)), 42);
    test(SA(SM(SN(42), SN(1)), SN(1)), 43);
    test(SA(SM(SN(42), SN(1)), SA(SM(SN(42), SN(1)), SN(1))), 85);

    test(new SE_Cons(new SE_String("+"), new SE_MT()), 0);
    test(new SE_Cons(new SE_String("*"), new SE_MT()), 1);

    Sexpr* three_things =
        new SE_Cons(new SE_Number(1),
                    new SE_Cons(new SE_Number(2),
                                new SE_Cons(new SE_Number(4),
                                            new SE_MT())));

    test(new SE_Cons(new SE_String("+"), three_things), 7);
    test(new SE_Cons(new SE_String("*"), three_things), 8);

    test(new SE_Cons(new SE_String("-"), new SE_Cons(new SE_Number(4), new SE_MT())), -4);
    test(new SE_Cons(new SE_String("-"), new SE_Cons(new SE_Number(4), new SE_Cons(new SE_Number(2), new SE_MT()))), 2);

    cout << tests_passed << " tests passed!" << endl;

    return 0;
}
