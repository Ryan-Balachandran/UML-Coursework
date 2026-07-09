/*
 Copyright [2019] <Ryan Balachandran>"  [legal/copyright]
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 4/24/19
 Problem Set X
 */

#ifndef PTREE_HPP
#define PTREE_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace sf;
using namespace std;

class PTree: public Drawable, public Transformable
{
public:
    ~PTree() {cout << "**************DESTRUCTOR***************" << endl << endl;}
    PTree(double size, int depth);
    void drawtree();
    void pTree(RenderTarget& target, Vector2f& P1, Vector2f& P2,
               double L, int N, ConvexShape& parent);
    
private:
    ConvexShape base;     // base square shape
    
    double L;             // size of base square
    int N;                // depth of recursion
    const int angle;      // angle to rotate shape
    const double R;       // factor to shrink shape by
    
    Vector2f direction;
    Vector2f A, B;        // A: bottom left coordinate; B: bottom right coordinate
    Vector2f Window;      // dimensions of window
    
    virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif
