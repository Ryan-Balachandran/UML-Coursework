/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 2/25/19
 Problem Set 3a
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <new>
#include <memory>
#include <iostream>
#include "NBody.hpp"

using namespace sf;
using namespace std;

int main(int argc, char* argv[])
{
    Vector2u window_size(600, 600);
    
    int N;           //Number of particles in the universe
    double R;        //Radius of the universe
    Vector2f P;      //XY position of a planet/particle
    Vector2f V;      //XY velocity of a planet/particle
    double M;        //Mass of a planet/particle
    string F;        //filename for the image of a planet/particle
    Vector2f net_force(0, 0);
    
    double T = atof(argv[1]);       //max time simulation
    double dt = atof(argv[2]);      //change in time
    double t = 0.0;                 //end simulation when t = T
    
    cin >> N;
    cin >> R;
    
    //cout << endl << "Time: " << T << endl;
    //cout << "Change in time: " << dt << endl;
    
    Font font;
    if(!font.loadFromFile("DejaVuSans-Bold.ttf"))
    {
        cout << "Error! COuldn't load Font" << endl;
        exit(EXIT_FAILURE);
    }
    
    Text timer;
    timer.setFont(font);
    timer.setPosition(135, 0);
    timer.setScale(.5, .5);
    
    Text text;
    text.setFont(font);
    text.setPosition(10, 0);
    text.setScale(.5, .5);
    text.setString("Elapsed Time: ");
    
    //Creating a vector a pointers to Body object
    vector<Body*> particles;
    
    for(int i = 0; i < N; i++)
    {
        cin >> P.x >> P.y >> V.x >> V.y >> M >> F;
        Body* planet = new Body(P, V, M, F);
        planet->determine_position(R, window_size);
        //cout << *planet << endl;
        particles.push_back(planet);
    }
    
    //Creating background
    Texture texture_background;
    Sprite background;
    
    Vector2u texture_size;
    
    if(!texture_background.loadFromFile("starfield.jpg"))
    {
        cout << "Couldn't load the background!" << endl;
    }
    
    texture_size = texture_background.getSize();
    float scaleX = (float) window_size.x/texture_size.x;
    float scaleY = (float) window_size.y/texture_size.y;
    background.setTexture(texture_background);
    background.setScale(scaleX, scaleY);
    
    RenderWindow window(VideoMode(window_size.x, window_size.y), "NBody Simulation");
    
    Music music;
    
    if(!music.openFromFile("2001.wav"))
    {
        cout << "ERROR!" << endl;
    }
    else
    {
        music.play();
    }
    
    while(window.isOpen())
    {
        Event event;
        
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                cout << endl << "Number of Particles: " << N << endl;
                cout << "Radius of universe: " << R << endl;
                printVariables(particles);
                window.close();
            }
            
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                cout <<  endl << "Number of Particles: " << N << endl;
                cout << "Radius of universe: " << R << endl;
                printVariables(particles);
                window.close();
            }
        }
        
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
            
            for(vector<Body*>::iterator it = particles.begin(); it != particles.end(); ++it)
            {
                step(dt, R, window_size, (*it));
                (*it)->determine_position(R, window_size);
            }
            
            window.clear();
            window.draw(background);
            
            for(vector<Body*>::iterator it = particles.begin(); it != particles.end(); ++it)
            {
                window.draw((*it)->getSprite());
                sleep(seconds(.010));    //remove to make animation go faster
            }
            
            timer.setString(to_string(t));
            t += dt;
        }
        
        window.draw(timer);
        window.draw(text);
        window.display();
    }
    
    return 0;
}


