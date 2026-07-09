/*******************************************************************
* Linear Feedback Shift Register (Part B) PS1b-readme.txt
********************************************************************/

Name: Ryan Balachandran
OS: Virtual Box, Ubuntu
Machine: MacBook Air
Text Editor: GNU Emacs 25 (GUI)
Hours to complete assignment: 40+ 

/*******************************************************************
* Briefly discuss the assignment itself and what you accomplished
********************************************************************/

For the Linear Feedback Shift Register, part B, the goal was to use
the LFSR code from part one to take a PNG image, scramble/encode it,
then using the same LFSR seed and tap on the encoded image, decode it
to get back to the original image. I started with the Pixels.cpp file
the professor gave as an example and started with changing it to produce
two windows, one with the original cat picture, and the other with
the negative image. Soon after I found out how to change it into 
one window that was extended to twice the horizontal length of the
image to fit both the original on the left, and the negative image
immedietly to the right. I then added variables for the input image,
output image, lfsr seed and tap along with the essential components
to taken from the first assignment in SFML. After getting the input
set up, I then proceeded to work on encoding the image. With some
thought, I found I could replace the code that made the image negative
in the upper 200x200 pixels of the image and modify it to work with
the lfsr function. Shortly after linking the appropiate files and editing
the make file, I was able to take a PNG image (not jpg because I wouldnt
be able to decode it), and encode it.

/*******************************************************************
* List whatever help (if any) you received from the instructor,
* classmates, or anyone else
********************************************************************/

I had help from Aditi Charora as a tutor

/*******************************************************************
* Describe any serious problems you encountered
********************************************************************/

On Saturday, after I was able to encode the PNG image, but I was not able 
to decode it. After encoding, when I tried to decode the encoded image,
it just scrambled the already scrambled picture. On sunday and monday,
I wasn't even able to display the window. 

After class on Monday, I found the problem to be in my LFSR.cpp file where
I was doing the copying loop from the string seed to the boolean vector

for(int i = N - 1; i >= 10; i++)

I also changed how I copied the seed which made it easier for me to understand
what was going on. After that, I was able to encode a picture, and decode 
with the same seed and tap position.






