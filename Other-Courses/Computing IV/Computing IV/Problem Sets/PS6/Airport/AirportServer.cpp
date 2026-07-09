#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "AirportServer.h"

/*
 *  Called by an Airplane when it wishes to land on a runway
 */
void AirportServer::reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
    // Acquire runway(s)
    {  // Begin critical region

        //unique_lock<mutex> runwaysLock(runwaysMutex);

        {
            lock_guard<mutex> lk(AirportRunways::checkMutex);

            cout << "-------------Airplane #" << airplaneNum << " is acquiring any needed runway(s) for landing on Runway "
            << AirportRunways::runwayName(runway) << endl;
        }

        /*
         *  ***** Add your synchronization here! *****
         */

        //#####################################################################################################

        if(AirportRunways::runwayName(runway) == "14")
        {
            unique_lock<mutex> Runway_14(lock_14);
            _14_occupied = true;
        }
        else
        {
            unique_lock<mutex> Runway_14(lock_14);
            while (_14_occupied == true)
                _14.wait(Runway_14);
        }







        //******************************RUNWAY 14******************************
        if(AirportRunways::runwayName(runway) == "14" && _14_occupied == false)
        {
            // Requested Runway 14 can be used simultaneously with any other runway

            unique_lock<mutex> Runway_14(lock_14);
            _14_occupied = true;
        }
        else if(AirportRunways::runwayName(runway) == "14" && _14_occupied == true)
        {
            // Runway 14 is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_14(lock_14);
            while(_14_occupied == true)
                _14.wait(Runway_14);
        }

        //******************************RUNWAY 4L******************************
        if((AirportRunways::runwayName(runway) == "4L" && _4L_occupied == false && _4R_occupied == false)
            && _15L_occupied == false && _15R_occupied == false)
        {
            // Requested Runway is 4L
            // Runway's 15L and 15R are not occupied

            unique_lock<mutex> Runway_4L(lock_4L);
            _4L_occupied = true;
            _15L_occupied = true;
            _15R_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "4L" && _4L_occupied == false && _4R_occupied == true)
                 && _15L_occupied == false && _15R_occupied == false)
        {
            // Requested Runway is 4L
            // Runway's 15L and 15R are blocked by runwy 4R

            unique_lock<mutex> Runway_4L(lock_4L);
            _4L_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "4L" && _4L_occupied == true && _4R_occupied == false)
                 && _15L_occupied == false && _15R_occupied == false)
        {
            // Runway 4L is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_4L(lock_4L);
            while(_4L_occupied == true)
                _4L.wait(Runway_4L);
        }
        else if((AirportRunways::runwayName(runway) == "4L" && _4L_occupied == true && _4R_occupied == true)
                 && _15L_occupied == false && _15R_occupied == false)
        {
            // Runway 4L is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_4L(lock_4L);
            while(_4L_occupied == true)
                _4L.wait(Runway_4L);
        }
        else if((AirportRunways::runwayName(runway) == "4L" && _4L_occupied == true)
                 && _15L_occupied == true || _15R_occupied == true)
        {
            if(_15L_occupied == true && _15R_occupied == false)
            {
                unique_lock<mutex> Runway_15L(lock_15L);
                while(_15L_occupied == true)
                    _15L.wait(Runway_15L);
            }
            else if(_15L_occupied == false && _15R_occupied == true)
            {
                unique_lock<mutex> Runway_15R(lock_15R);
                while(_15R_occupied == true)
                    _15R.wait(Runway_15R);
            }
            else if(_15L_occupied == true && _15R_occupied == true)
            {
                unique_lock<mutex> Runway_15L(lock_15L);
                while(_15L_occupied == true)
                    _15L.wait(Runway_15L);
            }
        }

        //******************************RUNWAY 4R******************************
        if((AirportRunways::runwayName(runway) == "4R" && _4R_occupied == false && _4L_occupied == false)
            && _15L_occupied == false && _15R_occupied == false && _9_occupied == false)
        {
            // Requested Runway is 4R
            // Runway's 15L and 15R are not occupied

            unique_lock<mutex> Runway_4R(lock_4R);
            _4R_occupied = true;
            _15L_occupied = true;
            _15R_occupied = true;
            _9_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "4R" && _4R_occupied == false && _4L_occupied == true)
                 && _15L_occupied == false && _15R_occupied == false && _9_occupied == false)
        {
            // Requested Runway is 4R
            // Runway's 15L and 15R are blocked by runwy 4L

            unique_lock<mutex> Runway_4R(lock_4R);
            _4R_occupied = true;
            _9_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "4R" && _4R_occupied == true && _4L_occupied == false)
                 && _15L_occupied == false && _15R_occupied == false && _9_occupied == false)
        {
            // Runway 4R is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_4R(lock_4R);
            while(_4R_occupied == true)
                _4R.wait(Runway_4R);
        }
        else if((AirportRunways::runwayName(runway) == "4R" && _4R_occupied == true && _4L_occupied == true)
                 && _15L_occupied == false && _15R_occupied == false && _9_occupied == false)
        {
            // Runway 4R is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_4R(lock_4R);
            while(_4R_occupied == true)
                _4R.wait(Runway_4R);
        }
        else if((AirportRunways::runwayName(runway) == "4R" && _4R_occupied == true)
                 && _15L_occupied == true || _15R_occupied == true || _9_occupied == true)
        {
            if(_15L_occupied == true && _15R_occupied == false && _9_occupied == false)
            {
                unique_lock<mutex> Runway_15L(lock_15L);
                while(_15L_occupied == true)
                    _15L.wait(Runway_15L);
            }
            else if(_15L_occupied == false && _15R_occupied == true && _9_occupied == false)
            {
                unique_lock<mutex> Runway_15R(lock_15R);
                while(_15R_occupied == true)
                    _15R.wait(Runway_15R);
            }
            else if(_15L_occupied == true && _15R_occupied == true && _9_occupied == false)
            {
                unique_lock<mutex> Runway_15L(lock_15L);
                while(_15L_occupied == true)
                    _15L.wait(Runway_15L);
            }
            else if(_15L_occupied == true && _15R_occupied == false && _9_occupied == true)
            {
                unique_lock<mutex> Runway_9(lock_9);
                while (_9_occupied == true)
                    _9.wait(Runway_9);
            }
        }

        //******************************RUNWAY 15L******************************
        if((AirportRunways::runwayName(runway) == "15L" && _15L_occupied == false && _15R_occupied == false)
            && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Requested Runway is 15L
            // Runway's 4L and 4R are not occupied

            unique_lock<mutex> Runway_15L(lock_15L);
            _15L_occupied = true;
            _4L_occupied = true;
            _4R_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "15L" && _15L_occupied == false && _15R_occupied == true)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Requested Runway is 15L
            // Runway's 4L and 4R are blocked by runwy 15R

            unique_lock<mutex> Runway_15L(lock_15L);
            _15L_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "15L" && _15L_occupied == true && _15R_occupied == false)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Runway 15L is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_15L(lock_15L);
            while(_15L_occupied == true)
                _15L.wait(Runway_15L);
        }
        else if((AirportRunways::runwayName(runway) == "15L" && _15L_occupied == true && _15R_occupied == true)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Runway 15L is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_15L(lock_15L);
            while(_15L_occupied == true)
                _15L.wait(Runway_15L);
        }
        else if ((AirportRunways::runwayName(runway) == "15L" && _15L_occupied == false && _15R_occupied == false)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == true)
        {
            // Requested Runway is 15L
            // Runway's 4L and 4R are not occupied
            // Runway 15L may be used simultaneously with runway 9

            unique_lock<mutex> Runway_15L(lock_15L);
            _15L_occupied = true;
            _4L_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "15L" && _15L_occupied == true && _15R_occupied == false)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == true)
        {
            // Runway 15L is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_15L(lock_15L);
            while(_15L_occupied == true)
                _15L.wait(Runway_15L);
        }
        else if((AirportRunways::runwayName(runway) == "15L" && _15L_occupied == true)
                 && _4L_occupied == true || _4R_occupied == true)
        {
            if(_4L_occupied == true && _4R_occupied == false)
            {
                unique_lock<mutex> Runway_4L(lock_4L);
                while (_4L_occupied == true)
                    _4L.wait(Runway_4L);
            }
            else if(_4L_occupied == false && _4R_occupied == true)
            {
                unique_lock<mutex> Runway_4R(lock_4R);
                while(_4R_occupied == true)
                    _4R.wait(Runway_4R);
            }
            else if(_15L_occupied == true && _15R_occupied == true)
            {
                unique_lock<mutex> Runway_4L(lock_4L);
                while(_4L_occupied == true)
                    _4L.wait(Runway_4L);
            }
        }

        //******************************RUNWAY 15R******************************
        if((AirportRunways::runwayName(runway) == "15R" && _15R_occupied == false && _15L_occupied == false)
            && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Requested Runway is 15R
            // Runway's 4L and 4R are not occupied

            unique_lock<mutex> Runway_15R(lock_15R);
            _15R_occupied = true;
            _4L_occupied = true;
            _4R_occupied = true;
            _9_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "15R" && _15R_occupied == false && _15L_occupied == true)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Requested Runway is 15R
            // Runway's 4L and 4R are blocked by runwy 15L

            unique_lock<mutex> Runway_15R(lock_15R);
            _15R_occupied = true;
            _9_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "15R" && _15R_occupied == true && _15L_occupied == false)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Runway 15R is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_15R(lock_15R);
            while(_15R_occupied == true)
                _15R.wait(Runway_15R);
        }
        else if((AirportRunways::runwayName(runway) == "15R" && _15R_occupied == true && _15L_occupied == true)
                 && _4L_occupied == false && _4R_occupied == false && _9_occupied == false)
        {
            // Runway 15R is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_15R(lock_15R);
            while(_15R_occupied == true)
                _15R.wait(Runway_15R);
        }
        else if((AirportRunways::runwayName(runway) == "15R" && _15R_occupied == true)
                 && _4L_occupied == true || _4R_occupied == true || _9_occupied == true)
        {
            if(_4L_occupied == true && _4R_occupied == false && _9_occupied == false)
            {
                unique_lock<mutex> Runway_4L(lock_4L);
                while(_4L_occupied == true)
                    _4L.wait(Runway_4L);
            }
            else if(_4L_occupied == false && _4R_occupied == true && _9_occupied == false)
            {
                unique_lock<mutex> Runway_4R(lock_4R);
                while (_4R_occupied == true)
                    _4R.wait(Runway_4R);
            }
            else if(_15L_occupied == true && _15R_occupied == true && _9_occupied == false)
            {
                unique_lock<mutex> Runway_4L(lock_4L);
                while (_4L_occupied == true)
                    _4L.wait(Runway_4L);
            }
            else if(_15L_occupied == false && _15R_occupied == false && _9_occupied == true)
            {
                unique_lock<mutex> Runway_9(lock_9);
                while (_9_occupied == true)
                    _9.wait(Runway_9);
            }
            else if(_15L_occupied == true && _15R_occupied == false && _9_occupied == true)
            {
                unique_lock<mutex> Runway_4L(lock_4L);
                while(_4L_occupied == true)
                    _4L.wait(Runway_4L);
            }
        }

        //******************************RUNWAY 9******************************
        if((AirportRunways::runwayName(runway) == "9" && _9_occupied == false && _15L_occupied == false)
            && _4R_occupied == false && _15R_occupied == false)
        {
            // Requested Runway is 9
            // Runway's 4R and 15R are not occupied

            unique_lock<mutex> Runway_9(lock_9);
            _9_occupied = true;
            _15R_occupied = true;
            _4R_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "9" && _9_occupied == false && _15L_occupied == true)
                 && _4R_occupied == false && _15R_occupied == false)
        {
            // Requested Runway is 9
            // Runway's 4R and 15R are blocked by runwy 15L

            unique_lock<mutex> Runway_9(lock_9);
            _9_occupied = true;
            _15R_occupied = true;
        }
        else if((AirportRunways::runwayName(runway) == "9" && _9_occupied == true && _15L_occupied == false)
                 && _4R_occupied == false && _15R_occupied == false)
        {
            // Runway 9 is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_9(lock_9);
            while(_9_occupied == true)
                _9.wait(Runway_9);
        }
        else if((AirportRunways::runwayName(runway) == "9" && _9_occupied == true && _15L_occupied == true)
                 && _4R_occupied == false && _15R_occupied == false)
        {
            // Runway 9 is occupied
            // Plane(s) must wait

            unique_lock<mutex> Runway_9(lock_9);
            while(_9_occupied == true)
                _9.wait(Runway_9);
        }
        else if((AirportRunways::runwayName(runway) == "9" && _9_occupied == true)
                 && _4R_occupied == true || _15R_occupied == true)
        {
            if(_4R_occupied == true && _15R_occupied == false)
            {
                unique_lock<mutex> Runway_4R(lock_4R);
                while(_4R_occupied == true)
                    _4R.wait(Runway_4R);
            }
            else if(_4R_occupied == false && _15R_occupied == false)
            {
                unique_lock<mutex> Runway_15R(lock_15R);
                while(_15R_occupied == true)
                    _15R.wait(Runway_15R);
            }
        }

        //#####################################################################################################

        // Check status of the airport for any rule violations
        AirportRunways::checkAirportStatus(runway);

        //runwaysLock.unlock();

    } // End critical region

    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Taxi for a random number of milliseconds
    std::uniform_int_distribution<int> taxiTimeDistribution(1, MAX_TAXI_TIME);
    int taxiTime = taxiTimeDistribution(generator);

    {
        lock_guard<mutex> lk(AirportRunways::checkMutex);

        cout << "-------------Airplane #" << airplaneNum << " is taxiing on Runway " << AirportRunways::runwayName(runway)
        << " for " << taxiTime << " milliseconds\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(taxiTime));

} // end AirportServer::reserveRunway()






/**
 *  Called by an Airplane when it is finished landing
 */
void AirportServer::releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
    // Release the landing runway and any other needed runways
    { // Begin critical region

        //unique_lock<mutex> runwaysLock(runwaysMutex);

        {
            lock_guard<mutex> lk(AirportRunways::checkMutex);

            cout << "Airplane #" << airplaneNum << " is releasing any needed runway(s) after landing on Runway "
            << AirportRunways::runwayName(runway) << endl;
        }

        // Update the status of the airport to indicate that the landing is complete
        AirportRunways::finishedWithRunway(runway);

        /**
         *  ***** Add your synchronization here! *****
         */

        //#####################################################################################################

        //******************************RUNWAY 14******************************
        if(AirportRunways::runwayName(runway) == "14")
        {
            unique_lock<mutex> Runway_14(lock_14);
            //AirportRunways::decNumLandingRequests();
            _14_occupied = false;
            Runway_14.unlock();
            _14.notify_one();
        }

        //******************************RUNWAY 4L******************************
        if(AirportRunways::runwayName(runway) == "4L" && _4L_occupied == true && _4R_occupied == false)
        {
            unique_lock<mutex> Runway_4L(lock_4L);
            _4L_occupied = false;
            _15L_occupied = false;
            _15R_occupied = false;

            Runway_4L.unlock();
            _4L.notify_one();
        }
        else if(AirportRunways::runwayName(runway) == "4L" && _4L_occupied == true && _4R_occupied == true)
        {
            unique_lock<mutex> Runway_4L(lock_4L);
            _4L_occupied = false;

            Runway_4L.unlock();
            _4L.notify_one();
        }

        //******************************RUNWAY 4R******************************
        if(AirportRunways::runwayName(runway) == "4R" && _4R_occupied == true && _4L_occupied == false)
        {
            unique_lock<mutex> Runway_4R(lock_4R);
            _4R_occupied = false;
            _15L_occupied = false;
            _15R_occupied = false;
            _9_occupied = false;

            Runway_4R.unlock();
            _4R.notify_one();
        }
        else if(AirportRunways::runwayName(runway) == "4L" && _4L_occupied == true && _4R_occupied == true)
        {
            unique_lock<mutex> Runway_4L(lock_4L);

            _4L_occupied = false;
            _9_occupied = false;

            Runway_4L.unlock();
            _4L.notify_one();
        }

        //******************************RUNWAY 15L******************************
        if(AirportRunways::runwayName(runway) == "15L" && _15L_occupied == true
            && _15R_occupied == false && _9_occupied == false)
        {
            unique_lock<mutex> Runway_15L(lock_15L);
            _15L_occupied = false;
            _4L_occupied = false;
            _4R_occupied = false;

            Runway_15L.unlock();
            _15L.notify_one();
        }
        else if(AirportRunways::runwayName(runway) == "15L" && _15L_occupied == true
                 && _15R_occupied == true && _9_occupied == false)
        {
            unique_lock<mutex> Runway_15L(lock_15L);
            _15L_occupied = false;

            Runway_15L.unlock();
            _15L.notify_one();
        }
        else if(AirportRunways::runwayName(runway) == "15L" && _15L_occupied == true
                 && _15R_occupied == false && _9_occupied == true)
        {
            unique_lock<mutex> Runway_15L(lock_15L);
            _15L_occupied = false;
            _4L_occupied = false;

            Runway_15L.unlock();
            _15L.notify_one();
        }

        //******************************RUNWAY 15R******************************
        if(AirportRunways::runwayName(runway) == "15R" && _15R_occupied == true && _15L_occupied == false)
        {
            unique_lock<mutex> Runway_15R(lock_15R);
            _15L_occupied = false;
            _4L_occupied = false;
            _4R_occupied = false;
            _9_occupied = false;

            Runway_15R.unlock();
            _15R.notify_one();
        }
        else if(AirportRunways::runwayName(runway) == "15R" && _15R_occupied == true && _15L_occupied == true)
        {
            unique_lock<mutex> Runway_15R(lock_15R);
            _15R_occupied = false;
            _9_occupied = false;

            Runway_15R.unlock();
            _15R.notify_one();
        }

        //******************************RUNWAY 9******************************
        if(AirportRunways::runwayName(runway) == "9" && _9_occupied == true && _15L_occupied == false)
        {
            unique_lock<mutex> Runway_9(lock_9);
            _9_occupied = false;
            _15R_occupied = false;
            _4R_occupied = false;

            Runway_9.unlock();
            _9.notify_one();
        }
        else if(AirportRunways::runwayName(runway) == "9" && _9_occupied == true && _15L_occupied == true)
        {
            unique_lock<mutex> Runway_9(lock_9);
            _9_occupied = false;
            _15R_occupied = false;

            Runway_9.unlock();
            _9.notify_one();
        }

        //#####################################################################################################

        //runwaysLock.unlock();

    } // End critical region

    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Wait for a random number of milliseconds before requesting the next landing for this Airplane
    std::uniform_int_distribution<int> waitTimeDistribution(1, MAX_WAIT_TIME);
    int waitTime = waitTimeDistribution(generator);

    {
        lock_guard<mutex> lk(AirportRunways::checkMutex);

        cout << "Airplane #" << airplaneNum << " is waiting for " << waitTime << " milliseconds before landing again\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

} // end AirportServer::releaseRunway()
