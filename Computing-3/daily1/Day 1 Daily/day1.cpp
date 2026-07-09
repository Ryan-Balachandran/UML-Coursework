//
//Day 1 Daily
//
//Created by Ryan Balachandran on 9/11/17.
//Copyright © 2017 Ryan Balachandran. All rights reserved.
//
//This program asks for two numbers from the user, the first greater than one, and the second greater than the first
//It then finds all the primes within the range including whether the input is prime or not before summing them up

#include <iostream>
using namespace std;

void input_numbers(int  &low, int &high, int &added_low);                               //function prototype for input of two numbers
void prime_range(int added_low, int high, int flag, int &prime_sum, int &prime_count);  //function prototype for finding all the prime numbers within the range of the two given numbers

int main()
{
    int low;
    int added_low;
    int high;
    int flag = 0;

    int prime_sum = 0;
    int prime_count = 0;
    
    input_numbers(low, high, added_low);    //function declaration for input of two numbers
    
    cout << "Prime numbers between " << low << " and " << high << " are: " << endl;
    
    prime_range(added_low, high, flag, prime_sum, prime_count);         //function declaration to find all the primes within the range of the two given numbers
    
    cout << endl;
    
    cout << "The sum of all prime numbers from " << low << " to " << high << " is: " << prime_sum << endl;
    
    cout << endl;
    
    cout << "The number of prime numbers between " << low << " to " << high << " is: " << prime_count << endl;
    
    cout << endl;
    
    return 0;
}

/*
pre-condition: Nothing
 
post-condition: Input of two numbers
 
*/
void input_numbers(int &low, int &high, int &added_low)
{
    cout << "Please enter a starting value greater than 1." << endl;
    
    //cin >> low;
    low = 2;
    cout << "Starting value entered: " << low;
    
    cout << endl;
    
    added_low = low;    //to keep low the same for later use, assign the value of low to added_low
    
    
    while(low <= 1)
    {
        cout << "You did not enter a number greater than one, please try again." << endl;
        
        //cin >> low;
        low = 2;
        cout << "Starting value entered: " << low;
        
        cout << endl;
        
        added_low = low;
    }
    
    cout << "Please enter ending value. \n";
    
    //cin >> high;
    high = 20;
    cout << "Ending value entered: " << high;
    
    cout << endl;
    
    while(high <= low)
    {
        cout << "Error, this number has to be greater than the first number, try again: " << endl;
        
        //cin >> high;
        //high = another number
        
        cout << endl;
    }
}

/*
pre-condition: Nothing
 
post-condition: Summing up all the prime numbers from the low to high number given
*/
void prime_range(int added_low, int high, int flag, int &prime_sum, int &prime_count)
{
    do
    {
        flag = 0;
        
        for(int interval = 2; interval <= added_low/2; interval++)
        {
            if(added_low % interval == 0)
            {
                flag = 1;
            }
        }
        
        if(flag == 0)
        {
            cout << added_low << " " << endl;
            prime_sum = prime_sum + added_low;
            prime_count++;
        }
        
        added_low++;
        
    }
    while(added_low <= high);
}

