/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/8/19
 Problem Set 5b
*/

#ifndef GUITARSTRING_HPP
#define GUITARSTRING_HPP

#include <SFML/Audio.hpp>

#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

#include "RingBuffer.hpp"

using namespace std;

class GuitarString
{
public:
  ~GuitarString();
  explicit GuitarString(double frequency);      // create a guitar string of the given frequency using a sampling rate of 44,100
  explicit GuitarString(vector<int16_t> init);  // create a guitar string with size and initial values given by the vector
  void pluck();                                 // pluck the guitar string by replacing the buffer with random values
  void tic();                                   // advance the simulation one time step
  int16_t sample();                             // return the current sample
  int Time();                                   // return the number of times tic was called so far

private:
  RingBuffer* rb;
  int N;
  int tic_count;
};

#endif
