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

int main()
{
    int L;
    int N;
    
    cout << "Enter Size of base square: ";
    cin >> L;
    cout << "Enter depth of the recursion: ";
    cin >> N;
    
    PTree MakeTree(L, N);     // create base square
    MakeTree.drawtree();      // move operations to drawtree function
    return 0;
}

