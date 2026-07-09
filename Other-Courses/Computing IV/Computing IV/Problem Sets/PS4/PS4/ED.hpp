/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 3/25/19
 Problem Set 4
 */

#ifndef ED_HPP
#define ED_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class ED
{
public:
    ~ED();     // delete dynamic 2d matrix
    ED(string string1, string string2);     // construct dynamic 2d matrix
    
    int penalty(char a, char b);
    int min(int a, int b, int c);
    int OptDistance();
    string Alignment();
    
    void draw_matrix();
    
private:
    string X;     // string 1
    string Y;     // string 2
    
    int N;        // size of string 1
    int M;        // size of string 2
    int **matrix;      // NxM matrix
    int edit_distance;
};

#endif
