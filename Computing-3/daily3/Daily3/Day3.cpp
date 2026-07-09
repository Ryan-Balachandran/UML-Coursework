//
//main.cpp
//Daily3
//
//Created by Ryan Balachandran on 9/18/17.
//Copyright © 2017 Ryan Balachandran. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

void calculations(string operation, double number1, double number2);

int main()
{
    string operation;
    double number1;
    double number2;
    
    cout << "Please enter what operation you would like to do in and two numbers." << endl;
    cout << "Operations available: add (+), subtract (-), divide (/), multiply (*)." << endl;
    
    cout << endl << "Operation: ";
    cin >> operation;
    //operation = addition;
    //operation = +;
    //operation = add;
    
    while(operation != "add" && operation != "subtract" && operation != "divide" && operation != "multiply" &&
          operation != "addition" && operation != "subtraction" && operation != "division" && operation != "multiplication" &&
          operation != "+" && operation != "-" && operation != "/" && operation != "*")         //checks to see if user entered two possible wordings of the operation or the sign
    {
        cout << "Invalid operation, please try again..." << endl;
        
        cout << endl << "Select new Operation: ";
        cin >> operation;
    }

    cout << endl << "Number 1: ";
    cin >> number1;
    
    cout << endl << "Number 2: ";
    cin >> number2;
    
    cout << endl << "Operation entered: " << operation << endl;
    cout << endl << "Numbers entered: " << number1 << " and " << number2 << endl;
    
    calculations(operation, number1, number2);
    
    return 0;
}

/*
 pre-condition: The proper operation and two numbers must be entered
 
 post-condition: The proper calculation is performed and displayed
*/
void calculations(string operation, double number1, double number2)
{
    double sum{0};
    
    if(operation == "add" || operation == "addition" || operation == "+")
    {
        sum = number1 + number2;
        //cout << "This is addition. " << endl;
    }
    
    else if(operation == "subtract" || operation == "subtraction" || operation == "-")
    {
        sum = number1 - number2;
        //cout << "This is subtraction. " << endl;
    }
    
    else if(operation == "divide" || operation == "division" || operation == "/")
    {
        if(number1 == 0 || number2 == 0)
        {
            cout << endl << "Error, division by zero is not possible!!!" << endl;
            exit(1);
        }
        
        else if(number1 !=0 && number2 != 0)
        {
            sum = number1 / number2;
            //cout << "This is division. " << endl;
        }
    }
    
    else if(operation == "multiply" || operation == "multiplication" || operation == "*")
    {
        sum = number1 * number2;
        //cout << "This is multiplication. " << endl;
    }
    
    cout.setf(ios::fixed);
    cout.precision(3);
        
    cout << endl << "Your answer is: " << sum << endl;
}
