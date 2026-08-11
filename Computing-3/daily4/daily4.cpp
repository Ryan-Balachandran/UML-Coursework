//
//main.cpp
//daily4
//
//Created by Ryan Balachandran on 9/27/17.
//  Copyright © 2017 Ryan Balachandran. All rights reserved.
//
//Temperature Conversion

/*
 1. (Done) create temperature class that internally stores a temperature in degree kelvin
 2. (Done) create functions named set_temp_kelvin, set_temp_fahrenheit, set_temp_celsius that take an input temperature in the specified temperature scale
 3. (Sort of) Convert to kelvin, store temperature in the class member variable
 4. (Done) Create accessor functions that return the stored temperature in degrees kelvin, fahrenheit, or celsius
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Temperature
{
public:
    void set_temp_kelvin(int &Kel, int choice);
    void set_temp_fahrenheit(int &Fahren, int choice);
    void set_temp_celsius(int &Cel, int choice);
    
    int getkelvin() const;
    int getfahrenheit() const;
    int getcelsius() const;
    
private:
    int kelvin{0};
};

int main()
{
    Temperature temp;
    
    int input{0};
    int choice{0};
    
    cout << "What temperature scale do you want to enter? Kelvin (1), Fahrenheit (2), or Celsius (3): ";
    cin >> choice;
    cout << endl;
    
    switch(choice)
    {
        case 1:
            cout << "Enter your temperature in Kelvin: ";
            cin >> input;
            cout << endl;
            
            temp.set_temp_kelvin(input, choice);
            cout << "Your temperature in Kelvin is: " << temp.getkelvin() << endl << endl;
            
            temp.set_temp_fahrenheit(input, choice);
            cout << "Your temperature in fahrenheit is: " << temp.getfahrenheit() << endl << endl;
            
            temp.set_temp_celsius(input, choice);
            cout << "Your temperature in celsius is: " << temp.getcelsius() << endl << endl;
            break;
            
        case 2:
            cout << "Enter your temperature in Fahrenheit: ";
            cin >> input;
            cout << endl;
            
            temp.set_temp_kelvin(input, choice);
            cout << "Your temperature in Kelvin is: " << temp.getkelvin() << endl << endl;
            
            temp.set_temp_fahrenheit(input, choice);
            cout << "Your temperature in fahrenheit is: " << temp.getfahrenheit() << endl << endl;
            
            temp.set_temp_celsius(input, choice);
            cout << "Your temperature in celsius is: " << temp.getcelsius() << endl << endl;
            break;
            
        case 3:
            cout << "Enter your temperature in Celsius: ";
            cin >> input;
            cout << endl;
            
            temp.set_temp_kelvin(input, choice);
            cout << "Your temperature in Kelvin is: " << temp.getkelvin() << endl << endl;
            
            temp.set_temp_fahrenheit(input, choice);
            cout << "Your temperature in fahrenheit is: " << temp.getfahrenheit() << endl << endl;
            
            temp.set_temp_celsius(input, choice);
            cout << "Your temperature in celsius is: " << temp.getcelsius() << endl << endl;
            break;
            
        default:
            cout << "Something went wrong, closing program... ";
            return 0;
    }

    return 0;
}

void Temperature::set_temp_kelvin(int &Kel, int choice)
{
    switch(choice)
    {
        case 1:
            kelvin = Kel;
            break;
        case 2:
            kelvin = (Kel - 32) * 5/9 + 273;
            break;
        case 3:
            kelvin = Kel + 273;
            break;
        default:
            cout << "Something went wrong, closing program... ";
            break;
    }
}

void Temperature::set_temp_fahrenheit(int &Fahren, int choice)
{
    switch(choice)
    {
        case 1:
            kelvin = ((Fahren - 273) * 9/5) + 32;
            break;
        case 2:
            kelvin = Fahren;
            break;
        case 3:
            kelvin = (Fahren * 9/5) + 32;
            break;
        default:
            cout << "Something went wrong, closing program... ";
            break;
    }
}

void Temperature::set_temp_celsius(int &Cel, int choice)
{
    switch(choice)
    {
        case 1:
            kelvin = Cel - 273;
            break;
        case 2:
            kelvin = (Cel - 32) * 5/9;
            break;
        case 3:
            kelvin = Cel;
            break;
        default:
            cout << "Something went wrong, closing program... ";
            break;
    }
}

int Temperature::getkelvin() const
{
    return kelvin;
}

int Temperature::getcelsius() const
{
    return kelvin;
}

int Temperature::getfahrenheit() const
{
    return kelvin;
}
