/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 2/4/19
 Problem Set 1a
 */

#ifndef LFSR_H
#define LFSR_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LFSR
{
public:
    LFSR(string seed, int t); 
    int step();
    int generate(int k);
    int bit;                 // Result of XOR
    
    friend ostream& operator<< (ostream &out, const LFSR &right);
    
private:
    int N;                    // Number of bits in string
    int tap_val;              // value of tap
    int tap_pos;              // position of tap
    vector<bool> value;       // Register for seed
};

#endif
