//
//main.cpp
//  daily5
//
//Created by Ryan Balachandran on 10/1/17.
//Copyright © 2017 Ryan Balachandran. All rights reserved.
//
//  1. (Done) Create a class called Rational
//  2. (Done) create two integer member variables, numerator and denominator
//  3. (Done) Write three constructors
//      a. (Done) default constructor that constructs the fraction 0/1
//      b. (Done) single argument constructor that constructs a given integer value into a rational number by placing it as the numerator/1
//      c. (Done) two argument constructor that allows the user to select both a numerater and a denominator
//          (Done( I) Last constructor can be a bit tricky because it allows the user to give you values that are not in simplest form, for example. They could ask you to construct
//          the fraction 4/2, which should be stored internally as 2/1
//          (Done) II) Take a look at the Euclidean algorithm for computing the gcd of two numbers. Implement this function as a helper function (private function) that your class can
//          use when simplifying fractions
//  4. (Done) Overload the << operator so that you can output objects of type Rational to the given stream so they appear as numerator/denominator.

/*
Three problems:
(Fixed) First, when the input are 600 & 400, you need to simplify it to 3/2.
(Fixed) Second, input ﻿-3/-2 should output 3/2. You need to simplify the negation symbols.
(Fixed) Third, when the denominator is 0, you need to end the program with an error message.﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿
*/

#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

class Rational
{
public:
    Rational();
    Rational(int num);
    Rational(int num, int den);
    
    friend ostream& operator<<(ostream& out, const Rational& right);
    
private:
    void Euclidean(int num, int den);
    int numerator;
    int denominator;
};

int main()
{
    Rational Default;

    cout << "Default constructor: " << Default << endl;
    
    Rational Single(7);
    
    cout << "Single Argument Constructor: " << Single << endl;
    
    //Rational Double(98,56);
    Rational Double(36,120);
    //Rational Double(600, 400);
    //Rational Double(-3,-2);
    
    cout << "Two Argument Constructor: " << Double << endl;
    
    return 0;
}

Rational::Rational()
{
    numerator = 0;
    denominator = 1;
    
    //cout << "**Hello from the Default constructor**" << endl;
}

Rational::Rational(int num)
{
    numerator = num;
    denominator = 1;
    
    //cout << "**Hello from the Single Argument constructor**" << endl;
}

Rational::Rational(int num, int den)
{
    if(num == 0 || den == 0)
    {
        cout << "Error, exiting program...";
        exit(1);
    }
    
    Euclidean(num, den);
    
    //cout << "**Hello from the Two Argument constructor**" << endl;
}

void Rational::Euclidean(int num, int den)
{
    cout << "Reducing fraction: " << num << "/" << den << endl << endl;
    int gcd = 0;
    
    int tempnum = num;  //copy the values of the numerator and denominator to temporary variables to avoid changing the value in the calculations
    int tempden = den;
    
    num = abs(num);     //take the absolute value of the numerator and denominator for use in the calculations
    den = abs(den);
    tempnum = abs(tempnum);     //take the absolute value of the temporary numerator and denominator for use in the output
    tempden = abs(tempden);
    
    //cout << "Absolute value of numerator: " << num << endl;
    //cout << "Absolute value of Denominator: " << den << endl << endl;
    
    while(den > 0)
    {
        gcd = den;
        den = num % den;
        num = gcd;
        
        //cout << "Num: " << num << endl;
        //cout << "den: " << den << endl;
        //cout << "gcd: " << gcd << endl << endl;
    }
     
    tempnum /= gcd;
    tempden /= gcd;
    
    numerator = tempnum;
    denominator = tempden;
}

ostream& operator<<(ostream& out, const Rational& right)
{
    out << right.numerator << "/" << right.denominator << endl;
    //out << "**Hello from the Overloaded ostream function**" << endl;
    
    return out;
}
