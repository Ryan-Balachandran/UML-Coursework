/*
 Copyright [2019] <Ryan Balachandran>"  [legal/copyright]
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 2/19/19
 Problem Set 2
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "PTree.hpp"

using namespace sf;
using namespace std;  

void PTree::drawtree()
{
    RenderWindow window(VideoMode(Window.x, Window.y), "Pythagoras Tree");
    window.setFramerateLimit(60);

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

        window.clear(Color::White);
        pTree(window, A, B, L, N, base);
        window.display();
    }
}

PTree::PTree(double size, int depth): angle{45}, R{sqrt(2)/2}
{
    cout << endl << "**************CONSTRUCTOR**************" << endl;
    L = size;
    N = depth;
    Window.x = 6*L;
    Window.y = 4*L;

    A.x = ((Window.x)/2)-L/2;
    A.y = Window.y;

    B.x = A.x + L;
    B.y = A.y;

    cout << "Dimensions of window: (" << Window.x << "," << Window.y << ")" << endl;

    cout << "Size of base square: " << L << endl;
    cout << "Depth of recursion: " << N << endl;

    cout << "Angle to rotate: " << angle << endl;
    cout << "Factor to shrink square: " << R << endl;

    cout << "Point A Coordinates: (" << A.x << ", " << A.y << ")" << endl;
    cout << "Point B Coordinates: (" << B.x << ", " << B.y << ")" << endl;

    base.setPointCount(4);
    base.setPoint(0, Vector2f(0, 0));
    base.setPoint(1, Vector2f(L, 0));
    base.setPoint(2, Vector2f(L, -L));
    base.setPoint(3, Vector2f(0, -L));
    base.setFillColor(Color(rand()%255, rand()%255, rand()%255));
    base.setOutlineThickness(-1);
    base.setOutlineColor(Color::Black);
    base.setPosition(A.x, A.y);
}

void PTree::pTree(RenderTarget& target, Vector2f& P1, Vector2f& P2, double L, int N, ConvexShape& parent)
{
    if (N == 0)
    {
        base.setFillColor(Color(rand()%255, rand()%255, rand()%255));
        target.draw(parent);
    }
    else
    {
        srand(time(NULL));
    
        Vector2f C(0,0);     //top left coordinate
        Vector2f D(0,0);     //top right coordinate
        Vector2f E(0,0);     //top of triangle coordinate
        Vector2f Z(0,0);     //intermediate step to calculate top of triangle

        base.setFillColor(Color(rand()%255, rand()%255, rand()%255));
        target.draw(parent);
    
        direction.x = P2.x - P1.x;
        direction.y = P1.y - P2.y;

        C.x = P1.x - direction.y;
        C.y = P1.y - direction.x;

        D.x = P2.x - direction.y;
        D.y = P2.y - direction.x;

        Z.x = (C.x + D.x)/2;
        Z.y = (C.y + D.y)/2;

        E.x = Z.x - (direction.y/2);
        E.y = Z.y - (direction.x/2);

        L = L*R;

        ConvexShape left = parent;
        left.setPoint(0, Vector2f(0, 0));
        left.setPoint(1, Vector2f(L, 0));
        left.setPoint(2, Vector2f(L, -L));
        left.setPoint(3, Vector2f(0, -L));
        left.setFillColor(Color(rand()%255, rand()%255, rand()%255));
        left.setOutlineThickness(-1);
        left.setOutlineColor(Color::Black);
        left.setPosition(C.x, C.y);
        left.rotate(-angle);

        ConvexShape right = parent;
        right.setPoint(0, Vector2f(0, 0));
        right.setPoint(1, Vector2f(-L, 0));
        right.setPoint(2, Vector2f(-L, -L));
        right.setPoint(3, Vector2f(0, -L));
        right.setFillColor(Color(rand()%255, rand()%255, rand()%255));
        right.setOutlineThickness(-1);
        right.setOutlineColor(Color::Black);
        right.setPosition(D.x, D.y);
        right.rotate(angle);

        pTree(target, C, E, L, N-1, left);
        pTree(target, E, D, L, N-1, right);
    }
}

void PTree::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(base);
}
