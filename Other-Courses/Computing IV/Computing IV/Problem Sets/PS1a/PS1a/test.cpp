/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 2/4/19
 Problem Set 1a
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

#include "LFSR.hpp"

using namespace boost;
using namespace boost::unit_test;  

BOOST_AUTO_TEST_SUITE(LFSR_test)

BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo)
{
    LFSR lfsr("00111", 2);
    BOOST_REQUIRE(lfsr.step() == 1);
    BOOST_REQUIRE(lfsr.step() == 1);
    BOOST_REQUIRE(lfsr.step() == 0);
    BOOST_REQUIRE(lfsr.step() == 0);
    BOOST_REQUIRE(lfsr.step() == 0);
    BOOST_REQUIRE(lfsr.step() == 1);
    BOOST_REQUIRE(lfsr.step() == 1);
    BOOST_REQUIRE(lfsr.step() == 0);
    
    LFSR lfsr_2("00111", 2);
    BOOST_REQUIRE(lfsr_2.generate(8) == 198);
}

BOOST_AUTO_TEST_SUITE_END( )


/*NEED TWO MORE SETS OF TESTS IN ADDITIONAL BOOST_AUTO_TEST_CASE blocks
 Each block should be commented with a short discussion. Try to test some
 edge cases of your implementation; very long or short seed strings*/
