//
//  main.cpp
//  daily6
//
//  Created by Ryan Balachandran on 10/24/17.
//  Copyright © 2017 Ryan Balachandran. All rights reserved.
//
// Overload the following as friend functions
//      1) (Done) Addition(+)
//      2) (Done) subtraction(-)
//      3) (Done) multiplication(*)
//      4) (Done) Division(/)

/*
 Each of these operations should evaluate as a rational number in simplest form and should
 be able to operate on a rational and an integer promoted to a rational as either argument
 */

// Overload the following boolean functions as friends functions
//      1) (Done) Less than(<)
//      2) (Done) Greater than(>)
//      3) (Done) Less than or equal to (<=)
//      4) (Done) Greater than or equal to (>=)
//      5) (Done) Equal (=)
//      6) (Done) Not Equal (!=)
//
// Overload the pre and post increment and decrement operators (++ and --)
// Although we did not do so in class these operators can both be overloaded and one is distinguished
// from the other by having an extra integer argument (that happens to be unused).




/*
Your operator overloading functions doesn't give correct result when the input is negative. Your output is﻿﻿﻿﻿ 1/2 when the correct output is -1/2, for example.
Also, try 1/2 and -5/10 as inputs for your comparison functions. Your > and <= are not correct.
*/


#include <iostream>
using namespace std;

class Rational
{
public:
    Rational();
    Rational(int num);
    Rational(int num, int den);
    
    friend ostream& operator<<(ostream& out, const Rational& right);
    
    friend Rational operator+(const Rational& left, const Rational& right);
    friend Rational operator-(const Rational& left, const Rational& right);
    friend Rational operator*(const Rational& left, const Rational& right);
    friend Rational operator/(const Rational& left, const Rational& right);

    friend bool operator<(const Rational& left, const Rational& right);
    friend bool operator>(const Rational& left, const Rational& right);
    friend bool operator<=(const Rational& left, const Rational& right);
    friend bool operator>=(const Rational& left, const Rational& right);
    friend bool operator==(const Rational& left, const Rational& right);
    friend bool operator!=(const Rational& left, const Rational& right);
    
    
    // pre increment operator
    friend Rational operator++(Rational& left);
    
    // post increment operator
    friend Rational operator++(Rational& left, int);
    
    // pre decrement operator
    friend Rational operator--(Rational& left);

    // post decrement operator
    friend Rational operator--(Rational& left, int);

    
private:
    void Euclidean(int num, int den);
    int numerator;
    int denominator;
};

int main()
{
    //Rational Default;
    //cout << "Default constructor: " << Default << endl;
    
    //Rational Single(7);
    //cout << "Single Argument Constructor: " << Single << endl;
    
    //Rational Double(1,2);
    //Rational Double(98,56);
    //Rational Double(36,120);
    //Rational Double(600, 400);
    //Rational Double(-3,-2);
    
    //cout << "Two Argument Constructor: " << Double << endl;
    
    
    Rational fraction1(1,2);
    Rational fraction2(2,7);
    
    cout << "Fraction 1: " << fraction1 << endl;
    cout << "Fraction 2: " << fraction2 << endl << endl;


    cout << "Fraction Addition: " << fraction1 << " + " << fraction2 << " = " << fraction1 + fraction2 << endl;
    
    cout << "Fraction Subtraction: " << fraction1 << " - " << fraction2 << " = " << fraction1 - fraction2 << endl;
    
    cout << "Fraction Multiplication: " << fraction1 << " * " << fraction2 << " = " << fraction1 * fraction2 << endl;
    
    cout << "Fraction Division: " << fraction1 << " / " << fraction2 << " = " << fraction1 / fraction2 << endl;
    
    
/*
    cout << fraction1 << " < " << fraction2 << endl;
    fraction1 < fraction2;
    
    cout << endl;
    
    cout << fraction1 << " > " << fraction2 << endl;
    fraction1 > fraction2;
    
    cout << endl;
    
    cout << fraction1 << " <= " << fraction2 << endl;
    fraction1 <= fraction2;
    
    cout << endl;
    
    cout << fraction1 << " >= " << fraction2 << endl;
    fraction1 >= fraction2;
    
    cout << endl;
    
    cout << fraction1 << " == " << fraction2 << endl;
    fraction1 == fraction2;
    
    cout << endl;
    
    cout << fraction1 << " != " << fraction2 << endl;
    fraction1 != fraction2;
    
    cout << endl;
    
    Rational pre_inc(1,2);
    cout << "Fraction before incrementing: " << pre_inc << endl;
    cout << "Pre-increment operator: " << ++pre_inc << endl;
    cout << "Fraction after incrementing: " << pre_inc << endl;

    cout << endl;

    Rational post_inc(1,2);
    cout << "Fraction before incrementing: " << post_inc << endl;
    cout << "Post-increment operator: " << post_inc++ << endl;
    cout << "Fraction after incrementing: " << post_inc << endl;

    cout << endl;

    Rational pre_dec(1,2);
    cout << "Fraction before decrementing: " << pre_dec << endl;
    cout << "Pre-decrement operator: " << --pre_dec << endl;
    cout << "Fraction after decrementing: " << pre_dec << endl;

    cout << endl;

    Rational post_dec(1,2);
    cout << "Fraction before decrementing: " << post_dec << endl;
    cout << "Post-decrement operator: " << post_dec-- << endl;
    cout << "Fraction after decrementing: " << post_dec << endl;
*/
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
    numerator = num;
    denominator = den;
    
    //cout << "Reducing fraction: " << numerator << "/" << denominator << endl << endl;
    
    int gcd{0};

    num = abs(numerator);     //take the absolute value of the numerator and denominator for use in the calculations
    den = abs(denominator);

    while(den > 0)
    {
        gcd = den;
        den = num % den;
        num = gcd;
    }
    
    numerator /= gcd;
    denominator /= gcd;
    
    if(numerator < 0 && denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }
}

ostream& operator<<(ostream& out, const Rational& right)
{
    out << right.numerator << "/" << right.denominator;
    //out << "**Hello from the Overloaded ostream function**" << endl;
    
    return out;
}


/*Overloaded Addition, subtraction, multiplication and division operators*/
Rational operator+(const Rational& left, const Rational& right)
{
    return Rational((left.numerator*right.denominator) + (left.denominator*right.numerator), left.denominator*right.denominator);
}

Rational operator-(const Rational& left, const Rational& right)
{
    return Rational((left.numerator*right.denominator) - (left.denominator*right.numerator), left.denominator*right.denominator);
}

Rational operator*(const Rational& left, const Rational& right)
{
    return Rational(left.numerator*right.numerator, left.denominator*right.denominator);
}

Rational operator/(const Rational& left, const Rational& right)
{
    return Rational(left.numerator*right.denominator, left.denominator*right.numerator);
}



//try while loop
//while bigger denominator % smaller != 0, raise iterator
//switch commented code to left ... right


/*Overloaded boolean operators*/
//NOTE: I know I could simplify this code for the second part with fixing the denominators, this is just so I can visualize/understand what is happening
bool operator<(const Rational& left, const Rational& right)
{
    if(left.denominator == right.denominator)   //if left and right denominators are equal, compare numerators
    {
        if(left.numerator < right.numerator)
        {
            cout << "The left fraction is smaller than the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually larger than the right fraction." << endl;
            return false;
        }
    }
    
    else    //else find common denominator and cross mulitply
    {
        cout << "Denominators are not equal, fixing fractions..." << endl;

        //cout << "multiplying denominators: " << left.denominator << " * " << right.denominator << " = " << left.denominator*right.denominator << endl;
        //cout << "Left Numerator changing to: " << left.numerator << " * " << right.denominator << " = " << left.numerator*right.denominator << endl;
        //cout << "Right Numerator changing to: " << right.numerator << " * " << left.denominator << " = " << right.numerator*left.denominator << endl;
        
        cout << "New fractions: " << left.numerator*right.denominator << "/" << left.denominator*right.denominator << " < " << right.numerator*left.denominator << "/" << left.denominator*right.denominator << endl;
        
        if((left.numerator*right.denominator) < (right.numerator*left.denominator))
        {
            cout << "The left fraction is smaller than the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually larger than the right fraction." << endl;
            return false;
        }
    }
}

bool operator>(const Rational& left, const Rational& right)
{
    if(left.denominator == right.denominator)   //if left and right denominators are equal, compare numerators
    {
        if(left.numerator > right.numerator)
        {
            cout << "The left fraction is larger than the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually smaller than the right fraction." << endl;
            return false;
        }
    }
    
    else    //else find common denominator and cross mulitply
    {
        cout << "Denominators are not equal, fixing fractions..." << endl;
        
        //cout << "multiplying denominators: " << left.denominator << " * " << right.denominator << " = " << left.denominator*right.denominator << endl;
        //cout << "Left Numerator changing to: " << left.numerator << " * " << right.denominator << " = " << left.numerator*right.denominator << endl;
        //cout << "Right Numerator changing to: " << right.numerator << " * " << left.denominator << " = " << right.numerator*left.denominator << endl;
        
        cout << "New fractions: " << left.numerator*right.denominator << "/" << left.denominator*right.denominator << " > " << right.numerator*left.denominator << "/" << left.denominator*right.denominator << endl;
        
        if((left.numerator*right.denominator) > (right.numerator*left.denominator))
        {
            cout << "The left fraction is larger than the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually smaller than the right fraction." << endl;
            return false;
        }
    }
}

bool operator<=(const Rational& left, const Rational& right)
{
    if(left.denominator == right.denominator)   //if left and right denominators are equal, compare numerators
    {
        if(left.numerator <= right.numerator)
        {
            cout << "The left fraction is smaller than or equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually larger than or equal to the right fraction." << endl;
            return false;
        }
    }
    
    else    //else find common denominator and cross mulitply
    {
        cout << "Denominators are not equal, fixing fractions..." << endl;
        
        //cout << "multiplying denominators: " << left.denominator << " * " << right.denominator << " = " << left.denominator*right.denominator << endl;
        //cout << "Left Numerator changing to: " << left.numerator << " * " << right.denominator << " = " << left.numerator*right.denominator << endl;
        //cout << "Right Numerator changing to: " << right.numerator << " * " << left.denominator << " = " << right.numerator*left.denominator << endl;
        
        cout << "New fractions: " << left.numerator*right.denominator << "/" << left.denominator*right.denominator << " <= " << right.numerator*left.denominator << "/" << left.denominator*right.denominator << endl;
        
        if((left.numerator*right.denominator) <= (right.numerator*left.denominator))
        {
            cout << "The left fraction is smaller than or equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually larger than or equal to the right fraction." << endl;
            return false;
        }
    }
}

bool operator>=(const Rational& left, const Rational& right)
{
    if(left.denominator == right.denominator)   //if left and right denominators are equal, compare numerators
    {
        if(left.numerator >= right.numerator)
        {
            cout << "The left fraction is larger than or equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually smaller than or equal to the right fraction." << endl;
            return false;
        }
    }
    
    else    //else find common denominator and cross mulitply
    {
        cout << "Denominators are not equal, fixing fractions..." << endl;
        
        //cout << "multiplying denominators: " << left.denominator << " * " << right.denominator << " = " << left.denominator*right.denominator << endl;
        //cout << "Left Numerator changing to: " << left.numerator << " * " << right.denominator << " = " << left.numerator*right.denominator << endl;
        //cout << "Right Numerator changing to: " << right.numerator << " * " << left.denominator << " = " << right.numerator*left.denominator << endl;
        
        cout << "New fractions: " << left.numerator*right.denominator << "/" << left.denominator*right.denominator << " >= " << right.numerator*left.denominator << "/" << left.denominator*right.denominator << endl;
        
        if((left.numerator*right.denominator) >= (right.numerator*left.denominator))
        {
            cout << "The left fraction is larger than or equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is actually smaller than or equal to the right fraction." << endl;
            return false;
        }
    }
}

bool operator==(const Rational& left, const Rational& right)
{
    if(left.denominator == right.denominator)   //if left and right denominators are equal, compare numerators
    {
        if(left.numerator == right.numerator)
        {
            cout << "The left fraction is equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is not equal to right fraction." << endl;
            return false;
        }
    }
    
    else    //else find common denominator and cross mulitply
    {
        cout << "Denominators are not equal, fixing fractions..." << endl;
        
        //cout << "multiplying denominators: " << left.denominator << " * " << right.denominator << " = " << left.denominator*right.denominator << endl;
        //cout << "Left Numerator changing to: " << left.numerator << " * " << right.denominator << " = " << left.numerator*right.denominator << endl;
        //cout << "Right Numerator changing to: " << right.numerator << " * " << left.denominator << " = " << right.numerator*left.denominator << endl;
        
        cout << "New fractions: " << left.numerator*right.denominator << "/" << left.denominator*right.denominator << " == " << right.numerator*left.denominator << "/" << left.denominator*right.denominator << endl;
        
        if((left.numerator*right.denominator) == (right.numerator*left.denominator))
        {
            cout << "The left fraction is equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is not equal to the right fraction." << endl;
            return false;
        }
    }
}

bool operator!=(const Rational& left, const Rational& right)
{
    if(left.denominator == right.denominator)   //if left and right denominators are equal, compare numerators
    {
        if(left.numerator != right.numerator)
        {
            cout << "The left fraction is not equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is equal to right fraction." << endl;
            return false;
        }
    }
    
    else    //else find common denominator and cross mulitply
    {
        cout << "Denominators are not equal, fixing fractions..." << endl;
        
        //cout << "multiplying denominators: " << left.denominator << " * " << right.denominator << " = " << left.denominator*right.denominator << endl;
        //cout << "Left Numerator changing to: " << left.numerator << " * " << right.denominator << " = " << left.numerator*right.denominator << endl;
        //cout << "Right Numerator changing to: " << right.numerator << " * " << left.denominator << " = " << right.numerator*left.denominator << endl;
        
        cout << "New fractions: " << left.numerator*right.denominator << "/" << left.denominator*right.denominator << " != " << right.numerator*left.denominator << "/" << left.denominator*right.denominator << endl;
        
        if((left.numerator*right.denominator) != (right.numerator*left.denominator))
        {
            cout << "The left fraction is not equal to the right fraction." << endl;
            return true;
        }
        
        else
        {
            cout << "The left fraction is equal to the right fraction." << endl;
            return false;
        }
    }
}



Rational operator++(Rational& left)
{
    left.numerator += left.denominator;
    return left;
}

Rational operator++(Rational& left, int unused)
{
    Rational temp = left;
    
    left.numerator += left.denominator;
    
    return temp;
}



Rational operator--(Rational& left)
{
    left.numerator -= left.denominator;
    return left;
}

Rational operator--(Rational& left, int unused)
{
    Rational temp = left;
    
    left.numerator -= left.denominator;
    
    return temp;
}


