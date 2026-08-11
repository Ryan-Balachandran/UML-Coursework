/**********************************************************************
 *  N-Body Simulation ps3b-readme.txt template
 **********************************************************************/

 Name: Ryan Balachandran
 Hours to complete assignment:

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/

 For assignment PS3b, we were tasked with taking the code we did in the first
 part and animating it by calculating the distance between every planet, the velocity,
 acceleration, forces, direction, etc. In order for the animation to work, I
 had to know where and when I had to calculate each problem and make sure
 that I did so before I updated th position of the planet. There was also the matter
 of how long the animation would play for, so a variable for time set at 0,
 a maximum time set at 5 years (157788000 seconds), and a change in time set
 for 25000 would be needed.

 /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/

 A few key algorithms that were important to the assignment were calculating
 the velocity, position, and acceleration of each planet relative to every other
 planet before caculating the difference in position on the XY plane, the radius
 between the bodies, then the total force acting on the planet. I then calculated
 the direction of the X force on the planet by taking the total force multiplied 
 by the X position divided by the radius, then doing the same for the Y force on the planet. 

 The most important structure was the step function which would calculate the acceleration 
 of the planet, then the velocity, then the position before determining the position of the planet.

 The other important algorithm was calculating the force on the planet. 


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Describe if and how do you used the smart pointers 
 *  Include code excerpts.
 **********************************************************************/

 To start it off, I added three time variables, one for the start of the simulation, 
 which would be incremented by the change in time given (or 25000 seconds), and the 
 ending time of 5 years. I used a vector of Body* pointers to store the bodies. 
 Within the while loop of the open window and poll event, I set up an if statement to 
 determine if the start time, incremented by 25000 seconds every step, has reached the end time of five years.

 I then did a for looped nested within a for loop to compare two bodies together, 
 but I set an if statement so that a body wouldn't be compared to itself. 
 Within the if statement, I calculated the force in a function, which calculated 
 the X and Y distance between two bodies and the radius before calcuting the 
 total force and then the net force on the planet from all other bodies in the system.

Vector2f Force(Body* body1, Body* body2)
{
  Vector2f force(0,0);
  double dX = 0;
  double dY = 0;
  double radius;
  double total_force;

  //calculate the radius between two bodies
  dX = (body1->getPosition().x) - (body2->getPosition().x);
  dY = (body1->getPosition().y) - (body2->getPosition().y);
  radius = sqrt(pow(dX, 2) + (pow(dY, 2)));

  total_force = (UGRAV * body1->getMass() * body2->getMass())/pow(radius, 2);
  force.x = total_force * (dX/radius);
  force.y = total_force * (dY/radius);

  return force; 
}


(within while loop of window)
if(t < T)
    { 
      for(vector<Body*>::iterator it1 = particles.begin(); it1 != particles.end(); ++it1)
      {
	for(vector<Body*>::iterator it2 = particles.begin(); it2 != particles.end(); ++it2)
	{
	  Vector2f force(0, 0);
	  
	  if((*it1)->getFile() != (*it2)->getFile())
	  {
	    force = Force((*it1), (*it2));
	    net_force.x += force.x;
	    net_force.y += force.y;
	  }
	}

	(*it1)->setNetForce(net_force);
	net_force.x = 0;
	net_force.y = 0;
      }

 Here I did a for loop to implement the step function and determind the position 
 of all the planets. Aftewards i did another for loop to draw the planets and increment the time.

***********************************************************************************************************************************
* I also implemented music into my code, displayed the elapsed time of the simulation, and tested out some other universes that I * liked
***********************************************************************************************************************************


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

 I didn't encounter many problems.

 The ones I did encountered, I was able to fix. 

 One of them was when I was finished of creating the functions and 
 implementing them in the correct order in the time loop, the planets 
 would move straight up. I fixed that by adjusting the gravity as I 
 had defined it in the header function as a global as -6.67E-11 or something 
 before changing it to -6.67*1e-11

 The other problem was getting the music to play, which I figured out 
 by looking at the top of the screen at Virtual Box VM and looking through 
 devices, realizing that audio output was disabled.


