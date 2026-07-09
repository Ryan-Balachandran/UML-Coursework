/*********************************************************************
 * PSX
 * Resubmitting PS2
 *********************************************************************/

/**********************************************************************
 *  PS2-readme template                                                   
 *  Recursive Graphics (Pythagoras tree)                       
 **********************************************************************/

Your name: Ryan Balachandran

Hours to complete assignment: ~10

/**********************************************************************
 *  Changes I made in PS2                                                                     
 **********************************************************************/

 In my original submission, I was not able to recursively draw the pythagoras tree,
 only the starting square.

 In the PTree header file, I removed the arguments from the void drawTree function
 I had declared in the public section of the class.

 I also changed the recursive pTree function from having the following parameters:
	void pTree(Vector2f baseP1, Vector2f baseP2, int size, int depth)

 to these parameters:
	void pTree(RenderTarget& target, Vector2f& P1, Vector2f& P2, double L, int N, ConvexShape& parent);

 I also removed the vectors for the top two corners of the square and both the
 convexshape for the left and right child.
 Instead, I added a vector for direction in which to move the square, a vector
 A and B for the bottom left coordinate and bottom right coordinate of the square,
 and a vector for the window size.

 In the Main file of the program I kept the initialization of the size of the base 
 square and the depth of the recursion as well as the input, but I moved
 the actual drawing of the squares to a different function called void draw(),
 the function where I removed the parameters from the last submission of this assignment.

 Instead I called the constructor for PTree and made an object called MakeTree,
 passed the L and N parameters taking from the user, and then called the drawtree()
 function.

 Now in the PTree implementation file and in the drawtree function, I moved the window from the main file to 
 this function so that the recursive pTree function could call it to draw the squares. 
 
 The initialization of the PTree class is different for the most part.
 The things I changed is having initialized the size of the window, having passed the
 size of the base square and depth of recursion from Main.

 I then calculated the coordinates of the bottom left and right corners of the base square.
 From there I created the base square and added random colors to it every time the program is executed.

 Now, instead of calculating the points of the top left and right corners
 of the base square and creating the left and right child before passng
 them into the recursive funtion twice, I dont pass anything in from the constructor,
 doing so from the drawtree function, one iteration. 
	pTree(window, A, B, L, N, base);
 

 Now in the recursive function pTree, I pass the paramets of target, which is the window 
 so I can draw the squares to the window. I overrode the draw function to simply draw the 
 base square, but since I passed a reference to the parent, or the square that was passed 
 last, I just have to call target.draw(parent). 

 Here, the implementation is similar as to how I shrink the square, calculate the new 
 coordinates before moving them.

 The one difference is that for the left child, the origin is the left bottom corner,
 but for the right child, its the  right bottom corner.

 I also added random colors, which I believe because of how I have the window and draw function set up,
 the colors change randomly every few seconds.





