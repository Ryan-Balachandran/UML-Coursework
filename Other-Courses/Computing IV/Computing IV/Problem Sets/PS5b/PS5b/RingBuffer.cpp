/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/8/19
 Problem Set 5b
 */

#include <stdint.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>

#include "RingBuffer.hpp"

using namespace std;

RingBuffer::~RingBuffer() {}

RingBuffer::RingBuffer(int cap)
{
    if (cap < 1)
    {
        throw invalid_argument("RB constructor: capacity must be greater than zero!\n");
    }
    else
    {
        first = 0;
        last = 0;
        full = false;
        capacity = cap;
        
        buffer.resize(capacity);
    }
}

int RingBuffer::size()
{
    if (isEmpty())
    {
        return 0;
    }
    else if (isFull())
    {
        return capacity;
    }
    else if (last > first)
    {
        return (last - first);
    }
    else
    {
        int end = capacity - first;
        int beginning = last;
        return (end + beginning);
    }
}

bool RingBuffer::isEmpty()
{
    if (first == last && full == false)
        return true;
    else
        return false;
}

bool RingBuffer::isFull()
{
    if (first == last && full == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void RingBuffer::enqueue(int16_t x)
{
    if (isFull())
    {
        throw runtime_error("Enqueue: can't enqueue to a full ring!\n");
    }
    
    buffer.at(last) = x;
    last++;
    
    if (last == capacity)
        last = 0;
    
    if (last == first)
        full = true;
}

int16_t RingBuffer::dequeue()
{
    if (isEmpty())
    {
        throw runtime_error("RingBuffer is already empty!\n");
    }
    
    int16_t dequeued = buffer.at(first);
    buffer.at(first) = 0;
    first++;
    
    if (first == capacity)
        first = 0;
    
    if (first == last)
        full = false;
    
    return dequeued;
}

int16_t RingBuffer::peek()
{
    if (isEmpty())
    {
        throw runtime_error("Cannot peak at an empty RingBuffer!\n");
    }
    else
    {
        return buffer.at(first);
    }
}

void RingBuffer::print()
{
    vector<int16_t>::iterator it;
    int i = 0;
    
    for (it = buffer.begin(); it != buffer.end(); ++it)
    {
        cout << i << " ";  // index
        i++;
    }
    cout << endl;
    
    for (it = buffer.begin(); it != buffer.end(); ++it)
    {
        cout << *it << " ";  // element
    }
    cout << endl;
}
