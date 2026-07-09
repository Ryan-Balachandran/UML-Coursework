/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/1/19
 Problem Set 5a
 */

#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <stdint.h>
#include <iostream>

using namespace std;;

class RingBuffer
{
public:
    explicit RingBuffer(int cap);  // creates an empty ring buffer, with given max capacity
    int Size();                    // returns number of items currently in buffer
    bool isEmpty();                // is the buffer empty (size = 0)?
    bool isFull();                 // is the buffer full (size = capacity)?
    void enqueue(int16_t x);       // add item x to the end
    int16_t dequeue();             // delete and return item from the front
    int16_t peek();                // return (but don't delete) item from the front
    
private:
    int size;
    int capacity;
    int16_t first;
    int16_t* data;
};

#endif
