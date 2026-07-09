/**********************************************************************
 *  readme.txt template                                                   
 *  Guitar Hero: GuitarString implementation and SFML audio output 
 **********************************************************************/

Name: Ryan Balachandran

Hours to complete assignment : 20+

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

 I did complete the whole assignment successfully. 
 In the implementation of the GuitarString, I believe the constructor 
 given a frequency is working as it divides the SAMPLING_RATE of 44100 
 by the frequency rounded up before creating a new ringBuffer from the calculation. 

 It will then fill up the buffer with 0's until its full.

 For the constructor with a vector given as a parameter, I made a new ringbuffer
 from the size of the vector before going through the vector and 
 enqueueing the values into the ringbuffer
 
 In the main function of GuitarHero, I made the three vectors for the 
 samples, sound, and soundbuffers, each of size 37.

 I then made a string that held the 37 keys before making a for loop 
 that would create the GuitarString from the frequency, send it to the 
 makeSamplesFromString function given at the top of the file before 
 storing it in its correct spot in the samples vector. After that, 
 I loaded the sample into the buffer, and then the buffer into the sound.


/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  As a pair, or individually?
 *  If you completed the AutoGuitar, what does it play?
 **********************************************************************/

 I did the extra credit for changing the tone of the sound.
 In GuitarHero.cpp:
 	change the SAMPLES_PER_SEC from 44100 to 9100
 	and the SAMPLING_RATE in GuitarString.cpp to 82000 for a different sound


/**********************************************************************
 *  Does your GuitarString implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/

 My GuitarString implementation passes the unit tests.
 I created a print function in the RingBuffer class to print out the vector
 after each step of the algorithm to make sure that the calculations were correct



