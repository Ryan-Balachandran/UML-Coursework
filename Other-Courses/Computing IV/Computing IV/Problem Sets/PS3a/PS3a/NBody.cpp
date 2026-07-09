/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 3/1/19
 Problem Set 3a
 */

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "NBody.hpp"

using namespace sf;  
using namespace std;

Body::~Body() {cout << endl << "--------------------DESTROYING PLANET!--------------------" << endl;}

Body::Body() {cout << "--------------------DEFAULT CONSTRUCTOR--------------------" << endl;}

Body::Body(Vector2f P, Vector2f V, double M, string F)
{
    cout << "--------------------CONSTRUCTING PLANET!--------------------" << endl;
    
    position = P;
    velocity = V;
    mass = M;
    filename = F;
    this->setSprite();
    
    cout << "-------------------------------------" << endl;
    cout << "Radius of Universe: " << universe_radius << endl;
    cout << "Position: (" << position.x << ", " << position.y << ")"  << endl;
    cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")"<< endl;
    cout << "Mass: " << mass << endl;
    cout << "Filename: " << filename << endl;
    cout << "-------------------------------------" << endl << endl;
}

void Body::determine_position(double& radius, Vector2u wSize)
{
    cout << "--------------------DETERMINING POSITION--------------------" << endl;
    Vector2f r;
    r.x = ((wSize.x/2) + ((this->position.x/radius) * (wSize.x/2)));
    r.y = ((wSize.y/2) - ((this->position.y/radius) * (wSize.y/2)));
    
    this->setRenderPos(r);
    object.setPosition(this->render_position.x, this->render_position.y);
}

void Body::setPosition(Vector2f coordinates)
{
    this->position = coordinates;
}

Vector2f Body::getPosition() const
{
    return this->position;
}

void Body::setVelocity(Vector2f V)
{
    this->velocity = V;
}

Vector2f Body::getVelocity() const
{
    return this->velocity;
}

void Body::setMass(double M)
{
    this->mass = M;
}

double Body::getMass()
{
    return this->mass;
}

void Body::setSprite()
{
    cout << "--------------------SETTING SPRITE--------------------" << endl;
    if (!(planet.loadFromFile("nbody/" + filename)))
    {
        cout << "ERROR! Unable to find Image!" << endl;
        exit(EXIT_FAILURE);
    }
    
    texture.loadFromImage(planet);
    this->object.setTexture(texture);
    this->object.setPosition(getRenderPos().x, getRenderPos().y);
}

Sprite Body::getSprite()
{
    return this->object;
}

void Body::setRenderPos(Vector2f renderPos)
{
    this->render_position = renderPos;
}

Vector2f Body::getRenderPos() const
{
    return this->render_position;
}

string Body::getFile()
{
    return filename;
}

istream& operator>>(istream& input, Body& body)
{
    cout << endl << "--------------------INPUT STREAM OVERLOAD--------------------" << endl;
    
    input >> body.position.x >> body.position.y >> body.velocity.x >> body.velocity.y >> body.mass >> body.filename;
    
    return input;
}

void Body::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(this->object);
}
