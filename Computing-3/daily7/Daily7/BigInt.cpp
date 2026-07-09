//
//  BigInt.cpp
//  Daily7
//
//  Created by Ryan Balachandran on 10/19/17.
//  Copyright © 2017 Ryan Balachandran. All rights reserved.
//

#include <iostream>
#include "BigInt.h"
#include <string>
#include <cctype>
using namespace std;

int main()
{
    // Test stub for BigInt
    
    BigInt x;
    cout << "Should be 0, is really: " << x << endl;

    x = BigInt(42);
    cout << "Starting number is: 42" << endl;
    cout << "Should be 42, is really: " << x << endl;

    x = BigInt(-29462);
    cout << "Starting number is: -29462" << endl;
    cout << "Should be -29462, is really: " << x << endl;

    x = BigInt("     -123456789012345678901234567890 and more stuff");
    cout << "Starting number is:     -123456789012345678901234567890 and more stuff" << endl;
    cout << "Should be -123456789012345678901234567890, is really: " << x << endl;

    x = BigInt("10498382547");
    cout << "Starting number is: 10498382547" << endl;
    cout << "Should be 10498382547, is really: " << x << endl;

    x = BigInt("                    +29104545 packman");
    cout << "Starting number is:                    +29104545 packman" << endl;
    cout << "Should be +29104545, is really: " << x << endl;

//    x = BigInt("+-4848484848484848");
//    cout << x << endl;
//
//    x = BigInt("              ");
//    cout << x << endl;
//
//    x = BigInt("     rucksewe");
//    cout << x << endl;
	
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------START OF DAILY 7
BigInt::BigInt()
{
    data = '0';
    isNegative = false;
}

BigInt::BigInt(int x)
{
    int number{x};
    int ascii{0};
    int remainder{0};
    int reversed_number{0};
    
    if(number > 0)
    {
        isNegative = false;
        //cout << "Starting number of x: " << x << endl;
        
        while(number > 0)
        {
            remainder = (number % 10);
            ascii = remainder + '0';
            data.push_back(ascii);
            number /= 10;
            reversed_number = reversed_number * 10 + remainder;
        }
        
        //cout << "Ending number: " << data << endl;
    }
    else if(number < 0)
    {
        isNegative = true;
        number = -number;
        
        while(number > 0)
        {
            remainder = (number % 10);
            ascii = remainder + '0';
            data.push_back(ascii);
            number /= 10;
            reversed_number = reversed_number * 10 + remainder;
        }
    }
}

BigInt::BigInt(string x)    //Initalizes the BigInt to have the value of the given string BUT must check that the string is valid or exit(1) otherwise.
{
    // cout << "Running single argument constructor" << endl;
    int i;
    string temp;
    
    for(i = 0; i < x.length(); i++) // skip leading spaces
    {
        if(!isspace(x[i]))  // if the next character is not a space, break out of loop
        {
            break;
        }
    }
    
    if(i >= x.size() || (!isdigit(x[i]) && x[i] != '-' && x[i] != '+'))     // Determining if string is out of bounds or doesnt have a digit and doesnt have either + or - sign
    {
        cout << "Tried to construct an invalid BigInt from string: " << endl;
        exit(1);
    }
    else
    {
        if(x[i+1] == '-' || x[i+1] == '+')      // if the next digit is another - or +, exit out
        {
            cout << "Confusing signs, exiting program..." << endl;
            exit(1);
        }
        else    // otherwise continue on
        {
            // if isNegative is true, then it is negative, else it is positive
            if(x[i] == '-')
            {
                //cout << "String starts with: " << x[i] << endl;
                isNegative = true;
                
                // while isdigit, move to temporary, then data
                while(isdigit(x[i+1]))
                {
                    //cout << x[i+1];
                    temp.push_back(x[i+1]);
                    i++;
                }
                
                //cout << endl << endl;
                
                reverse(temp.begin(), temp.end());
                
                data = temp;
            }
            else if(x[i] == '+')
            {
                //cout << "Starts with: " << x[i] << endl;
                isNegative = false;
                
                // while isdigit, move to temporary, then data
                while(isdigit(x[i+1]))
                {
                    //cout << x[i+1];
                    temp.push_back(x[i+1]);
                    i++;
                }
                
                //cout << endl << endl;
                
                reverse(temp.begin(), temp.end());
                
                data = temp;
            }
            else
            {
                //cout << "Starts with: " << x[i] << endl;
                isNegative = false;
                
                // while isdigit, move to temporary, then data
                while(isdigit(x[i]))
                {
                    //cout << x[i];
                    temp.push_back(x[i]);
                    i++;
                }
                
                //cout << endl << endl;
                
                reverse(temp.begin(), temp.end());
                
                data = temp;
            }
        }
    }
}

ostream& operator<<(ostream& out, const BigInt& right)
{
    // if isNegative is true, then it is negative, else it is positive
    if(right.isNegative == true)
    {
		out << '-';
		
		for(int i = right.data.size()-1; i >= 0; i--)
		{
			out << right.data[i];
		}
		cout << endl;
    }
    else if(right.isNegative == false)
    {
		out << '+';
		
		for(int i = right.data.size()-1; i >= 0; i--)
		{
			out << right.data[i];
		}
		cout << endl;
    }
    
    return out;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------END OF DAILY 7
