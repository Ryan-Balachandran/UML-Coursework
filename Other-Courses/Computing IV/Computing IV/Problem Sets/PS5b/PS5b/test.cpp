/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/8/19
 Problem Set 5b
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <stdint.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "RingBuffer.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(RingBuffercontructor)
{
    // normal constructor
    BOOST_REQUIRE_NO_THROW(RingBuffer(100));
    BOOST_REQUIRE_NO_THROW(RingBuffer(1));
    
    // this should fail
    // input is less than 1
    BOOST_REQUIRE_THROW(RingBuffer(0), invalid_argument);
    BOOST_REQUIRE_THROW(RingBuffer(-13), invalid_argument);
}


BOOST_AUTO_TEST_CASE(RingBufferEnque_dequeue)
{
    // make a ringbuffer
    RingBuffer rb(3);
    
    // enqueue 3 items
    rb.enqueue(2);
    rb.enqueue(1);
    rb.enqueue(0);
    
    // check if the ringbuffer is full
    BOOST_REQUIRE(rb.isFull());
    
    // dequeue 3 items, make sure they match the enqueued items in the same order
    BOOST_REQUIRE(rb.dequeue() == 2);
    BOOST_REQUIRE(rb.dequeue() == 1);
    BOOST_REQUIRE(rb.dequeue() == 0);
    
    // check if the ringbuffer is empty
    BOOST_REQUIRE(rb.isEmpty());
    
    // dequeueing one more item when ringbuffer is already empty will throw an exception
    BOOST_REQUIRE_THROW(rb.dequeue(), runtime_error);
    
    // make another ringbuffer
    RingBuffer rb2(4);
    
    // enqueue 4 items, then one more. Can't enqueue to an already full buffer
    rb2.enqueue(4);
    rb2.enqueue(7);
    rb2.enqueue(3);
    rb2.enqueue(2);
    BOOST_REQUIRE_THROW(rb2.enqueue(5), runtime_error);
}

BOOST_AUTO_TEST_CASE(peek)
{
    // make ringbuffer
    RingBuffer rb(20);
    
    // enqueue 4 items
    rb.enqueue(1);
    rb.enqueue(3);
    rb.enqueue(6);
    rb.enqueue(51);
    
    // enqueueing one more item when size of buffer is 20 wont throw and exception
    BOOST_REQUIRE_NO_THROW(rb.enqueue(2));
    
    // check if peeking at first item in buffer outputs correct item
    BOOST_REQUIRE(rb.peek() == 1);
    BOOST_REQUIRE(rb.peek() != 5);
    
    // make sure dequeued items match the order in which they were dequeued
    BOOST_REQUIRE(rb.dequeue() == 1);
    BOOST_REQUIRE(rb.dequeue() == 3);
    BOOST_REQUIRE(rb.dequeue() == 6);
    BOOST_REQUIRE(rb.dequeue() == 51);
    BOOST_REQUIRE(rb.dequeue() == 2);
    
    // peeking at an empty buffer will throw an exception
    BOOST_REQUIRE_THROW(rb.peek(), runtime_error);
}

