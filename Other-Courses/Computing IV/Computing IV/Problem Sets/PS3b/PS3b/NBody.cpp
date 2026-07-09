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
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <new>
#include <memory>
#include "NBody.hpp"

using namespace sf;
using namespace std;

Body::~Body() {}

Body::Body() {}

Body::Body(Vector2f P, Vector2f V, double M, string F)
{
    position = P;
    velocity = V;
    mass = M;
    filename = F;
    this->setSprite();

    //cout << "Position: (" << position.x << ", " << position.y << ")"  << endl;
    //cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")"<< endl;
    //cout << "Mass: " << mass << endl;
    //cout << "Filename: " << filename << endl;
}

void Body::determine_position(double& radius, Vector2u wSize)
{
    Vector2f r;
    r.x = ((wSize.x/2) + ((this->position.x/radius) * (wSize.x/2)));
    r.y = ((wSize.y/2) - ((this->position.y/radius) * (wSize.y/2)));

    FloatRect sprite_dimensions = object.getGlobalBounds();
    r.x -= (sprite_dimensions.width/2);
    r.y -= (sprite_dimensions.height/2);

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

void Body::setAcceleration(Vector2f accel)
{
    this->acceleration = accel;
}

Vector2f Body::getAcceleration()
{
    return this->acceleration;
}

void Body::setNetForce(Vector2f fnet)
{
    this->net_force = fnet;
}

Vector2f Body::getNetForce()
{
    return this->net_force;
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
    if(!(planet.loadFromFile(filename)))
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
    input >> body.position.x >> body.position.y >> body.velocity.x >> body.velocity.y >> body.mass >> body.filename;

    return input;
}

ostream& operator<<(ostream &output, Body& body)
{
    output << "Window Dimension: (" << body.window.x << ", " << body.window.y << ")" << endl;
    output << "Radius of Universe: " << body.universe_radius << endl;
    output << "Position: (" << body.position.x << ", " << body.position.y << ")" << endl;
    output << "Velocity: (" << body.velocity.x << ", " << body.velocity.y << ")" << endl;
    output << "Mass: " << body.mass << endl;
    output << "File name: " << body.filename << endl;
    cout << "--------------------------------------------------------------" << endl;

    return output;
}

void Body::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(this->object);
}

//calculate and set body velocity
void setBodyVelocity(double time, Body* body)
{
    Vector2f vel;

    vel.x = body->getVelocity().x + (time*body->getAcceleration().x);
    vel.y = body->getVelocity().y + (time*body->getAcceleration().y);
    body->setVelocity(vel);
}

void setBodyPosition(double time, Body* body)
{
    Vector2f pos;

    pos.x = body->getPosition().x + (time*body->getVelocity().x);
    pos.y = body->getPosition().y + (time*body->getVelocity().y);
    body->setPosition(pos);
}

void setBodyAcceleration(Body* body)
{
    Vector2f accel;

    accel.x = body->getNetForce().x/body->getMass();
    accel.y = body->getNetForce().y/body->getMass();
    body->setAcceleration(accel);
}

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

void step(double seconds, double radius, Vector2u wSize, Body* body)
{
    setBodyAcceleration(body);
    setBodyVelocity(seconds, body);
    setBodyPosition(seconds, body);
    body->determine_position(radius, wSize);
}

void printVariables(vector<Body*> body)
{
    for(vector<Body*>::iterator it = body.begin(); it !=body.end(); ++it)
    {
        cout << scientific << (*it)->getPosition().x << "\t" << (*it)->getPosition().y;
        cout << scientific << "\t" << (*it)->getVelocity().x << "\t" << (*it)->getVelocity().y;
        cout << "\t" << (*it)->getMass() << "\t";
        cout.width(11);
        cout << right << (*it)->getFile() << endl;
    }
}



