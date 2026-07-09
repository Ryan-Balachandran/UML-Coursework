//
//main.cpp
//daily2
//
//Created by Ryan Balachandran on 9/12/17.
//Copyright © 2017 Ryan Balachandran. All rights reserved.
//
//Program that has the user enter a number in feet and inches. Code combines feet and inches before converting and seperating it into meters and centimeters

#include <iostream>
#include <cmath>
using namespace std;

void user_input(int &feet, double &inches);
void unit_convert(int feet, double inches, int &meters, double &centimeters);
void output(int feet, double inches, int meters, double centimeters);

const double INCHES_TO_FEET = 1/12.0;
const double FEET_TO_METERS = .3048;
const double METERS_TO_CENTIMETERS = 100;

int main()
{
    double inches{0};
    int feet{0};
    
    int meters{0};
    double centimeters{0};
    
    user_input(feet, inches);
    unit_convert(feet, inches, meters, centimeters);
    output(feet, inches, meters, centimeters);

    return 0;
}


void user_input(int &feet, double &inches)
{
    cout << "Please enter the number of feet: " << endl;
    //cin >> feet;
    feet = 4;
    cout << "Number of feet entered: " << feet;
    
    cout << endl << "Please enter the number of inches: " << endl;
    //cin >> inches;
    inches = 7;
    cout << "Number of inches entered: ";
    cout << endl;
}

void unit_convert(int feet, double inches, int &meters, double &centimeters)
{
    double total_feet = feet + inches * INCHES_TO_FEET;
    double total_meters = total_feet * FEET_TO_METERS;
    
    meters = floor(total_meters);
    centimeters = (total_meters - meters) * METERS_TO_CENTIMETERS;
}

void output(int feet, double inches, int meters, double centimeters)
{
    cout << feet << "' feet and " << inches << "\" inches converts to ";
    cout.setf(ios::fixed);
    cout.precision(8);
    cout << meters << " meters and " << centimeters << " centimeters." << endl;
}



