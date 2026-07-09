/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/1/19
 Problem Set 5a
 */

#include <stdint.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "RingBuffer.hpp"

using namespace std;
RingBuffer::RingBuffer(int cap)
{
    if (cap < 1)
    {
        throw invalid_argument("RB constructor: capacity must be greater than zero!\n");
    }
    else
    {
        size = 0;
        first = 0;
        capacity = cap;
        data = new int16_t[capacity];
    }
}

int RingBuffer::Size()
{
    return size;
}

bool RingBuffer::isEmpty()
{
    return size == 0;
}

bool RingBuffer::isFull()
{
    return size == capacity;
}

void RingBuffer::enqueue(int16_t x)
{
    if (isFull())
    {
        throw runtime_error("Enqueue: can't enqueue to a full ring!\n");
    }
    else
    {
        data[(first + size) % capacity] = x;
        size++;
    }
}

int16_t RingBuffer::dequeue()
{
    if (isEmpty())
    {
        throw runtime_error("RingBuffer is already empty!\n");
    }
    else
    {
        size--;
        int dequeued = first;
        first = (first + 1) % capacity;
        return data[dequeued];
    }
}

int16_t RingBuffer::peek()
{
    if (isEmpty())
    {
        throw runtime_error("Cannot peak at an empty RingBuffer!\n");
    }
    else
    {
        return data[first];
    }
}

