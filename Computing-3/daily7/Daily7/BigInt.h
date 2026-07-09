//
//  BigInt.h
//  Daily7
//
//  Created by Ryan Balachandran on 10/19/17.
//  Copyright © 2017 Ryan Balachandran. All rights reserved.
//

#ifndef BigInt_h
#define BigInt_h

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class BigInt
{
public:
    //START OF DAILY 7---------------------------------------------------------------------------------------------------------------------------------------------------------
    BigInt();                       //Initializes the BigInt to zero. (Check)
    BigInt(int x);                  //Initializes the BigInt to have the same value as x (check)
    explicit BigInt(string x);      //Initalizes the BigInt to have the value of the given string BUT must check that the string is valid or exit(1) otherwise.
    
    friend ostream& operator<<(ostream& out, const BigInt& right);
    //END OF DAILY 7-----------------------------------------------------------------------------------------------------------------------------------------------------------
    
private:
    string data;
    bool isNegative;
};

#endif /* BigInt_h */
