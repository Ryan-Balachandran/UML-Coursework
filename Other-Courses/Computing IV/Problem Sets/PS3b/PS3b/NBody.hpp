/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 2/25/19
 Problem Set 3a
 */

#ifndef NBODY_HPP
#define NBODY_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <new>
#include <memory>

#define UGRAV -6.67*1e-11

using namespace sf;
using namespace std;

class Body: public Drawable
{
public:
    ~Body();
    Body();
    Body(Vector2f P, Vector2f V, double M, string F);
    
    void determine_position(double& radius, Vector2u wSize);
    
    void setPosition(Vector2f P);
    void setVelocity(Vector2f V);
    void setAcceleration(Vector2f accel);
    void setNetForce(Vector2f fnet);
    void setMass(double M);
    void setSprite();
    void setRenderPos(Vector2f renderPos);
    
    Vector2f getPosition() const;
    Vector2f getVelocity() const;
    Vector2f getAcceleration();
    Vector2f getNetForce();
    double getMass();
    Sprite getSprite();
    Vector2f getRenderPos() const;
    string getFile();
    
    friend istream &operator>>(istream &input, Body& body);
    friend ostream &operator<<(ostream &output, Body& body);
    
private:
    Vector2u window;            //size of the window
    double universe_radius;     //Radius of the universe
    Vector2f render_position;   //position of sprite
    
    Vector2f position;          //XY position of a planet/particle
    Vector2f velocity;          //XY velocity of a planet/particle
    Vector2f acceleration;      //acceleration of a planet
    Vector2f net_force;         //net force acting on a planet
    double mass;                //Mass of a planet/particle
    string filename;            //filename for the image of a planet/particle
    
    Image planet;
    Texture texture;
    Sprite object;
    
    virtual void draw(RenderTarget& target, RenderStates states) const;
};

void setBodyVelocity(double time, Body* body);
void setBodyPosition(double time, Body* body);
void setBodyAcceleration(Body* body);

Vector2f Force(Body* body1, Body* body2);
void step(double seconds, double radius, Vector2u wSize, Body* body);

void printVariables(vector<Body*> body);

#endif
