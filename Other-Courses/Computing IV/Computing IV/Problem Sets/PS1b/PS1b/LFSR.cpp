/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 2/11/19
 Problem Set 1b
 */

#include <iostream>
#include <string>
#include <vector>

#include "LFSR.hpp"

using namespace std;

LFSR::LFSR(string seed, int t)
{
    tap_pos = t;
    N = seed.length();
    
    for (int i = 0; i < N - 1; i++)
    {
        if (seed[i] == '0')
        {
            value.push_back(0);
        }
        
        else if (seed[i] == '1')
        {
            value.push_back(1);
        }
    }
}

int LFSR::step()
{
    int result;
    
    bit = value[0];
    tap_val = value[N - tap_pos - 1];
    result = bit ^ tap_val;
    
    for (int i = 0; i < N - 1; i++)
    {
        value[i] = value[i + 1];
    }
    
    value[N - 1] = result;
    
    return result;
}

int LFSR::generate(int k)
{
    int result = 0;
    
    for (int i = 0; i < k; i++)
    {
        int step_result = step();
        result = result * 2 + step_result;
    }
    
    return result;
}

ostream& operator<< (ostream &out, const LFSR &right)
{
    for (int j = right.value.size() - 1; j >= 0; j--)
    {
        out << right.value[j];
    }
        
    out << " " << right.bit << endl;
        
    return out;
}
        
        
        
