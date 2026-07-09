#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdint>
//#include <vector>
//#include <regex>

#include "scan.h"

using namespace std;

const char* names[] = {"read", "write", "id", "literal", "gets", "add", "sub", "mult", "div", "lparen", "rparen", "eof",
                       "equiv", "notEquiv", "lt", "gt", "ltEquiv", "gtEquiv", "if", "fi", "do", "od", "check"};

string syntax_tree = "";

static token input_token;

void error()
{
    cout << "syntax error" << endl;
    exit(1);

    //throw new exception();
}

void match(token expected)
{
    if(input_token == expected)
    {
        cout << "matched " << names[input_token];

        if(input_token == t_id || input_token == t_literal)
        {
            cout << ": " << token_image;
        }

        cout << endl;
        input_token = scan();
    }
    else error();
}

// changed void to string to enable display of parse tree:
void program();
void stmt_list();
void stmt();
void expr();
void term_tail();
void term();
void factor_tail();
void factor();
void add_op();
void mul_op();

/*
 void relation();   // 'R'
 string relation_op(); // encompasses all of the below:
 void equivOp();    // '=='
 void notEquivOp(); // '<>'
 void ltOp();       // '<'
 void gtOp();       // '>'
 void ltEquivOp();  // '<='
 void gtEquivOp();  // '>='
 void checkOp();    // test iteration exit;
 void doOp();       // start iteration;
 void odOp();       // terminate iteration;
 void ifOp();       // start comparator block;
 void fiOp();       // end comparator block;
 */

void program()
{
    switch(input_token)
    {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict program --> stmt_list eof" << endl;
            stmt_list();
            match(t_eof);
            break;

        default: error();
    }
}

void stmt_list()
{
    switch(input_token)
    {
        case t_id:
        case t_read:
        case t_write:
            cout << "predict stmt_list --> stmt stmt_list" << endl;
            stmt();
            stmt_list();
            break;

        case t_eof:
            cout << "predict stmt_list --> epsilon" << endl;
            break;          /*  epsilon production */

        default: error();
    }
}

void stmt()
{
    switch(input_token)
    {
        case t_id:
            cout << "predict stmt --> id gets expr" << endl;
            match(t_id);
            match(t_gets);
            expr();
            break;

        case t_read:
            cout << "predict stmt --> read id" << endl;
            match(t_read);
            match(t_id);
            break;

        case t_write:
            cout << "predict stmt --> write expr" << endl;
            match(t_write);
            expr();
            break;
            
        default: error();
    }
}

void expr()
{
    switch(input_token)
    {
        case t_id:
        case t_literal:
        case t_lparen:
            cout << "predict expr --> term term_tail" << endl;
            term();
            term_tail();
            break;

        default: error();
    }
}

void term_tail()
{
    switch(input_token)
    {
        case t_add:
        case t_sub:
            cout << "predict term_tail --> add_op term term_tail" << endl;
            add_op();
            term();
            term_tail();
            break;

        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict term_tail --> epsilon" << endl;
            break;          /*  epsilon production */

        default: error();
    }
}

void term()
{
    switch(input_token)
    {
        case t_id:
        case t_literal:
        case t_lparen:
            cout << "predict term --> factor factor_tail" << endl;
            factor();
            factor_tail();
            break;

        default: error();
    }
}

void factor_tail()
{
    switch(input_token)
    {
        case t_mult:
        case t_div:
            cout << "predict factor_tail --> mul_op factor factor_tail" << endl;
            mul_op();
            factor();
            factor_tail();
            break;

        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict factor_tail --> epsilon" << endl;
            break;          /*  epsilon production */

        default: error();
    }
}

void factor()
{
    switch(input_token)
    {
        case t_id :
            cout << "predict factor --> id" << endl;
            match(t_id);
            break;

        case t_literal:
            cout << "predict factor --> literal" << endl;
            match(t_literal);
            break;

        case t_lparen:
            cout << "predict factor --> lparen expr rparen" << endl;
            match(t_lparen);
            expr();
            match(t_rparen);
            break;

        default: error();
    }
}

void add_op()
{
    switch(input_token)
    {
        case t_add:
            cout << "predict add_op --> add" << endl;
            match(t_add);
            break;

        case t_sub:
            cout << "predict add_op --> sub" << endl;
            match(t_sub);
            break;

        default: error();
    }
}

void mul_op()
{
    switch(input_token)
    {
        case t_mult:
            cout << "predict mul_op --> mult" << endl;
            match(t_mult);
            break;

        case t_div:
            cout << "predict mul_op --> div" << endl;
            match(t_div);
            break;

        default: error();
    }
}

int main()
{
    input_token = scan();
    program();
    
    return 0;
}
