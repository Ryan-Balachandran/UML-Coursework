/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/8/19
 Problem Set 5b
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <stdint.h>
#include <cmath>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>

#include "RingBuffer.hpp"
#include "GuitarString.hpp"

const int SAMPLING_RATE = 44100;

using namespace sf;
using namespace std;

GuitarString::~GuitarString()
{
    delete rb;
}

GuitarString::GuitarString(double frequency)
{
    tic_count = 0;
    
    N = ceil(SAMPLING_RATE/frequency);
    
    rb = new RingBuffer(N);
    
    while (rb->isFull() == false)
    {
        rb->enqueue(0);
    }
}

GuitarString::GuitarString(vector<int16_t> init)
{
    tic_count = 0;
    
    rb = new RingBuffer(init.size());
    
    vector<int16_t>::iterator it;
    
    for (it = init.begin(); it != init.end(); ++it)
    {
        rb->enqueue(*it);
    }
    
}

int16_t GuitarString::sample()
{
    return rb->peek();
}

int GuitarString::Time()
{
    return tic_count;
}

void GuitarString::pluck()
{
    while (rb->isEmpty() == false)
    {
        rb->dequeue();
    }
    
    while (rb->isFull() == false)
    {
        rb->enqueue((int16_t)(rand() & 0xffff));
    }
}

void GuitarString::tic()
{
    int16_t first = rb->dequeue();
    int16_t second = rb->peek();
    int16_t decayed = 0.996 * (first + second)/2;
    
    rb->enqueue(decayed);
    tic_count++;
}

