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
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

#include "RingBuffer.hpp"
#include "GuitarString.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(GS)
{
    vector<int16_t> v;
    
    v.push_back(0);
    v.push_back(2000);
    v.push_back(4000);
    v.push_back(-10000);
    
    BOOST_REQUIRE_NO_THROW(GuitarString gs = GuitarString(v));
    
    GuitarString gs = GuitarString(v);
    
    // GS is 0 2000 4000 -10000
    BOOST_REQUIRE(gs.sample() == 0);
    
    gs.tic();
    // now it's 2000 4000 -10000 996
    BOOST_REQUIRE(gs.sample() == 2000);
    
    gs.tic();
    // now its 4000 -10000 996 2988
    BOOST_REQUIRE(gs.sample() == 4000);
    
    gs.tic();
    // now its -10000 996 2988 -2988
    BOOST_REQUIRE(gs.sample() == -10000);
    
    gs.tic();
    // now its 996 -2988 -2988 -4483
    BOOST_REQUIRE(gs.sample() == 996);
    
    gs.tic();
    // now its 2988 -2988 -4483 1984
    BOOST_REQUIRE(gs.sample() == 2988);
    
    gs.tic();
    // now its -2988 -4483 1984 0
    BOOST_REQUIRE(gs.sample() == -2988);
    
    gs.tic();
    BOOST_REQUIRE(gs.sample() == -4483);
    
    gs.tic();
    BOOST_REQUIRE(gs.sample() == 1984);  
    
    gs.tic();
    BOOST_REQUIRE(gs.sample() == 0);
}

