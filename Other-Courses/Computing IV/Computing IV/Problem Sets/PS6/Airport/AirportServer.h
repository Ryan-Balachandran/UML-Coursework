/**
 *  AirportServer.h
 *  This class defines the methods called by the Airplanes
 */

#ifndef AIRPORT_SERVER_H
#define AIRPORT_SERVER_H

#include <thread>
#include <mutex>
#include <random>
#include <condition_variable>

#include "AirportRunways.h"

class AirportServer
{
public:
    
    /**
     *  Default constructor for AirportServer class
     */
    AirportServer()
    {
        // ***** Initialize any Locks and/or Condition Variables here as necessary *****
        
        mutex();
        condition_variable();
        
        _14_occupied = false;
        _4L_occupied = false;
        _4R_occupied = false;
        _15L_occupied = false;
        _15R_occupied = false;
        _9_occupied = false;
        
    } // end AirportServer default constructor
    
    
    /**
     *  Called by an Airplane when it wishes to land on a runway
     */
    void reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway);
    
    /**
     *  Called by an Airplane when it is finished landing
     */
    void releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway);
    
    
private:
    
    // Constants and Random number generator for use in Thread sleep calls
    static const int MAX_TAXI_TIME = 10; // Maximum time the airplane will occupy the requested runway after landing, in milliseconds
    static const int MAX_WAIT_TIME = 100; // Maximum time between landings, in milliseconds
    
    /**
     *  Declarations of mutexes and condition variables
     */
    mutex runwaysMutex; // Used to enforce mutual exclusion for acquiring & releasing runways
    
    /**
     *  ***** Add declarations of your own Locks and Condition Variables here *****
     */
    
    // mutex lock for each runway	
    mutex lock_14;
    mutex lock_4L;
    mutex lock_4R;
    mutex lock_15L;
    mutex lock_15R;
    mutex lock_9;
    
    /*
     condition variables to make other planes wait if
     runway is occupied or if runway is unable to be used with another runway
     */
    condition_variable _14;
    condition_variable _4L;
    condition_variable _4R;
    condition_variable _15L;
    condition_variable _15R;
    condition_variable _9;
    
    bool _14_occupied;
    bool _4L_occupied;
    bool _4R_occupied;
    bool _15L_occupied;
    bool _15R_occupied;
    bool _9_occupied;
    
}; // end class AirportServer

#endif
