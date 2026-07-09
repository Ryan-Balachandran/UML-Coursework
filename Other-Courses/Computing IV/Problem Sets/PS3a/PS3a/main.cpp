/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 3/1/19
 Problem Set 3a
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <new>
#include <memory>
#include <cstdlib>
#include "NBody.hpp"

using namespace sf; 
using namespace std;

int main()
{
    Vector2u window_size(1000, 600);
    
    int N;          // Number of particles in the universe
    double R;       // Radius of the universe
    Vector2f P;     // XY position of a planet/particle
    Vector2f V;     // XY velocity of a planet/particle
    double M;       // Mass of a planet/particle
    string F;       // filename for the image of a planet/particle
    
    cin >> N;
    cin >> R;
    
    cout << "Number of Particles: " << N << endl;
    cout << "Radius of universe: " << R << endl;
    
    // Creating a vector a pointers to Body object
    vector<Body*> bodies;
    
    for (int i = 0; i < N; i++)
    {
        cin >> P.x >> P.y >> V.x >> V.y >> M >> F;
        Body* planet = new Body(P, V, M, F);
        planet->determine_position(R, window_size);
        bodies.push_back(planet);
    }
    
    RenderWindow window(VideoMode(window_size.x, window_size.y), "NBody Simulation");
    
    // Creating background
    Texture texture_background;
    Sprite background;
    
    Vector2u texture_size;
    
    if (!texture_background.loadFromFile("nbody/starfield.jpg"))
    {
        return -1;
    }
    
    texture_size = texture_background.getSize();
    float scaleX = (float) window_size.x/texture_size.x;
    float scaleY = (float) window_size.y/texture_size.y;
    background.setTexture(texture_background);
    background.setScale(scaleX, scaleY);
    
    while (window.isOpen())
    {
        Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }
        
        window.clear();
        window.draw(background);
        
        for (vector<Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it)
        {
            window.draw((*it)->getSprite());
        }
        
        window.display();
    }
    
    return 0;
}
