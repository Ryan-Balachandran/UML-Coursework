/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/8/19
 Problem Set 5b
 */

#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <stdint.h>
#include <iostream>
#include <vector>

using namespace std;

class RingBuffer
{
public:
    ~RingBuffer();
    explicit RingBuffer(int cap);  // creates an empty ring buffer, with given max capacity
    int size();                    // returns number of items currently in buffer
    bool isEmpty();                // is the buffer empty (size = 0)?
    bool isFull();                 // is the buffer full (size = capacity)?
    void enqueue(int16_t x);       // add item x to the end
    int16_t dequeue();             // delete and return item from the front
    int16_t peek();                // return (but don't delete) item from the front
    void print();
    
private:
    int first, last, capacity;
    bool full;
    vector<int16_t> buffer;
};


#endif
