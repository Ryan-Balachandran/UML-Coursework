/**********************************************************************
 *  Airport-readme template                                                   
 *  Airport Simulation (C++11 Concurrency)                       
 **********************************************************************/

Your name: Ryan Balachandran 

Operating system you're using (Linux, OS X, or Windows): OS X

Text editor or IDE you're using: GNU Emacs 25 (GUI)

Hours to complete assignment: 50+

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
				
 In this assignment we have 7 airplanes that are trying to land simultaneously
 on random runways at logan airport. For this simulation, the planes are
 only going to come from the West or South.

 The goal was to run the simulation forever (or 15 minutes) without any of
 the planes crashing due to a violation of a set of rules.

 One of the rules was:
	1) Runway 4L can be used simultaneously with runway 4R
	2) Runway 9 can be used simultaneously with runway 15L
	3) Runway 14 can be used with any runway
	4) Runway 15L can be used simultaneously with runway 15R
 
 The second set of rules was:
	1) Runway 9 cannot be used with runway 4R or 15R simultaneously
	2) Runway 15L or 15R cannot be used with runway 4L or 4R simultaneously
	3) There can only be one plane on a runway
	4) There can only be six requests for landing at one time

 Implementing the rules for runway 14 was easy, as that one could be used
 simultaneously with any runway.

 However, runways 4L, 4R, 15L, and 15R were harder to do. The beginning of
 their implementation is the same as runway 14's, but if either runway 15L 
 or 15R (for runway 4L and 4R) is being occupied by a plane, then you have
 to implement a way for the plane that is requesting runway 4L or 4R to wait
 until both runway 15L and 15R are not occupied anymore. The same goes for the
 reverse. 

 Then for runways 4R and 15R, I had to implement rules that included runway 9 as well.
 And for runway 9 itself, I had to implement a way for the plane that is requesting 
 runway 9 to wait until runway 4R and runway 15R are not occupied.


 /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/

 The most important data structure was implementing the rules in such a
 way that none of the rules were violated. Runway 14 was easy to implement.
 Runways 4L and 15L took more time to implement because I had to take into
 account if either runway 15L or 15R  (or 4L and 4R) was occupied. Then
 runway 15R and 4R took a bit more time than 4L and 15L because I had to
 include runway 9 as well. 


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/

 I first started with one mutex, condition variable, and boolean to figure
 out how they work. Once I got that working, with one plane landing on any
 runway, while the rest had to wait, reguardless of which runway they had
 requested until the first one left, I began with runway 14, as that one
 could run simultaneously with any other runway. 

 In the reserveRunway function, the general implementation I did for runway 14
 would be copied by the other runways (albiet more complicated). 

		if (AirportRunways::runwayName(runway) == "14")
		{
		  unique_lock<mutex> Runway_14(lock_14);

		  while (_14_occupied == true)
		    _14.wait(Runway_14, [this](){ return _14_occupied == false; });

		  _14_occupied = true; 
		}

 In the releaseRunway function, again, the general implementation I did for runway 14
 would be copied by the other runways, with alot of alterations. 

		if (AirportRunways::runwayName(runway) == "14")
		{
		  unique_lock<mutex> Runway_14(lock_14);
		  _14_occupied = false;
		  Runway_14.unlock();
		  _14.notify_one();
		}

 As for the other runways, after an if statement to find what runway was requested,
 I also included else if statements if other runways were occupied that would violate
 the rules if the plane landed on their requested runway.
 
 For example: 

		if (AirportRunways::runwayName(runway) == "4L" && (_15L_occupied == false && _15R_occupied == false))
		{
		  unique_lock<mutex> Runway_4L(lock_4L);

		  // planes have to wait if runway 4L is occupied
		  while (_4L_occupied == true)
		    _4L.wait(Runway_4L, [this](){ return _4L_occupied == false; });

		  _4L_occupied = true;
		}

 After this I had an else if statement if the requested runway was 4L, but either runway 15L or 
 15R were occupied. Then within the else if statement, I sent the plane that had requested
 runway 4L to the runway's waiting queue that was being occupied, or if both runways were occupied,
 I sent it to the runway with the same letter. 

 Example:

	1) if requested runway is 4L and neither 15L and 15R are occupied, lock runway 4L as well as
	   runway 15L and 15R.
	2) else if requested runway is 4L and either 15L or 15R are occupied
		a) if 15L is occupied but 15R is not, send the plane to 15L's waiting queue
		b) else if 15R is occupied but 15L is not, send the plane to 15R's waiting queue
		c) else if both runways are occupied, send the plane to runway 15L's waiting queue by default

 /**********************************************************************
 *  Briefly explain what you learned in the assignment.
 **********************************************************************/

 Before this, I did not know what a mutex or a condition variable was.
 A week into the assignment, I had learned from looking online and practical
 real world examples of what each of them were and an idea of how I could
 use them in the assignment. 

 A mutex allows only one thread to access a specified block of code that is 
 surrounded by the mutex with mutex.lock() and mutex.unlock(). 

 A condition variable uses a unique_lock with a mutex to block other threads
 from accessing the information the first thread is using until it sends
 a signal to wake up one or all the other threads from a waiting queue

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
	
 I got help from Professor Adams

/**********************************************************************
 *  Describe any serious problems you encountered.  
 *  If you didn't complete any part of any assignment, 
 *  the things that you didn't do, or didn't get working.                  
 **********************************************************************/

 I most serious problem I encountered was not knowing what a mutex and 
 condition variable were before the assignment. It also didn't help that
 the teacher didn't talk about mutex's or condition variables's until
 the wednesday it was suppose to be due, as well as friday. 

 Another problem I encountered was not being to implement the rules
 correctly, but it was only from forgetting to comment out the lines
 that were mentioned in the powerpoint.

 I have finally been able to make serious progress on this assignment
 on friday, the day its due. I know I won't be able to get everything done,
 but I will at least have been able to implement the basic synchronization
 rules for each runway (though they would still crash). I will resubmit
 the assignment saturday once I have completed the synchronization and
 mutual exclusion. 
