/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 3/25/19
 Problem Set 4
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

#include "ED.hpp"

using namespace sf;
using namespace std;

int main()
{
    Clock clock;
    Time time;
    
    string X;
    string Y;
    string result;
    int edit_distance;
    
    cin >> X >> Y;
    
    ED *test = new ED(X, Y);
    time = clock.getElapsedTime();
    edit_distance = test->OptDistance();
    cout << endl << "Edit distance: " << edit_distance << endl;
    result = test->Alignment();
    
    int size = result.size();
    
    cout << endl;
    for (int i = 0; i < size; i += 3)
    {
        cout << result[i] << " " << result[i+1] << " " << result[i+2] << endl;
    }
    cout << endl;
    
    cout << fixed << "Time Elapsed: " << time.asSeconds() << " seconds" << endl;
    
    return 0;
}

