/**********************************************************************
 *  N-Body Simulation ps3a-readme.txt template
 **********************************************************************/

Name: Ryan Balachandran
OS: MacBook Air
Text editor: GNU Emacs 25 (GUI)
Hours to complete assignment: 25+

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/

The NBody simulation assignment goal is to simulate a universe with N
number of planets and/or particles. The first part was setting up the class
and displaying the planets statically on the screen.

I started with setting up the Body class and making the variables
that each instance of the class would need: X and Y position/velocity,
mass, and filename, along with SFML attributes like Image, Texture,
and Sprite to create and hold the image of the Body(planet).

I then overrided the virtual draw function to draw the sprite for each
instance of the body class that was made along with scaling the size of
the universe given in the text file to fit the size of the window.

In the constructor of the class with the parameters of X,Y position,
X,Y velocity, mass and filename, I initialized the variables and setup
the sprite. I then made two variables, N and R in the main file to get
the first two numbers in the text file, N: for the number of particles
in the system; R: for the radius of the universe. With that I would set 
up a for loop after making a vector of pointers to the Body class in order
to take in the remaining information in the text file of X,Y position and 
velocity, mass, and image name to create the vector of bodies.

After overloading the stream input operator, I made get and set functions
for position, velocity, mass, sprite, renderposition, and file. I also
made a determine position function which scales the size of the radius
of the universe in proportion to the window size while also setting
the position of the sprite object.


/**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/

One of the key data structures is the class itself, making sure it had
the neccessary variables for each instantiation of the class when
creating a new object. 

One of the algorithms that was important was scaling the size of the universe
taken from the text file to fit the window. If that wasn't implemented right it 
would not be possible to see the planets as they would be positions relative to the
given radius of the universe and not scaled down to fit inside the window.
Another important algorithm was modifying the position of the sprite along
with scaling the size of the universe to fit the window so that each
planet would be in its correct position. 

The most important design was creating the vector of pointers to the body
class, making the same number of instances that were given in the text file
so that each one had a X,Y position, velocity, mass, and image.


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/

The first feature I implemented was the constructor, assigning the variables
of the class the variables given in the parameters of the constructor. 

I also made sure to load the image file for each planet and create the sprite 
associated with it so it could be drawn corrected and in the right position. 

  if(!(planet.loadFromFile("nbody/" + filename)))
  {
    cout << "ERROR! Unable to find Image!" << endl;
    exit(EXIT_FAILURE);
  }

  texture.loadFromImage(planet);
  this->object.setTexture(texture);
  this->object.setPosition(getRenderPos().x, getRenderPos().y);

I then scaled the universe to fit within the size of the window along with adjusting 
the position of the sprites so that they would appear in their correct position. 

  Vector2f r;
  r.x = ((wSize.x/2) + ((this->position.x/radius) * (wSize.x/2)));
  r.y = ((wSize.y/2) - ((this->position.y/radius) * (wSize.y/2)));

  this->setRenderPos(r);
  object.setPosition(this->render_position.x, this->render_position.y);

When creating the vector of pointers of body objects, I used a for loop with
the previous variable N that was used to obtain the number of objects to create.

  vector<Body*> bodies;

  for(int i = 0; i < N; i++)
  {
    cin >> P.x >> P.y >> V.x >> V.y >> M >> F;
    Body* planet = new Body(P, V, M, F);
    planet->determine_position(R, window_size);
    bodies.push_back(planet);
  }


/**********************************************************************
 * I also managed to set a background for the window. 
 *
 * Texture texture_background;
 * Sprite background;
 * 
 * Vector2u texture_size;
 * 
 * if(!texture_background.loadFromFile("nbody/starfield.jpg"))
 * {
 *   return -1;
 * }
 *
 * texture_size = texture_background.getSize();
 * float scaleX = (float) window_size.x/texture_size.x;
 * float scaleY = (float) window_size.y/texture_size.y;
 * background.setTexture(texture_background);
 * background.setScale(scaleX, scaleY);
 **********************************************************************/


 /**********************************************************************
  * Other Comments
  **********************************************************************/

  Submitted folder has planets.txt and images in seperate folder. I did ./NBody < nbody/planets.txt
  to access the text and images.





