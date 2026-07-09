/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 1/28/19
 Problem Set 0
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
// For std and text output
#include <iostream>

using namespace sf;
using namespace std;  

int main()
{
    // Create the main window
    RenderWindow window(VideoMode(800, 800), "SFML works!");
    
    window.setVerticalSyncEnabled(true);
    
    // Change the framerate to make it easier to see the image moving.
    // window.setFramerateLimit(1);
    
    // Key press event will only happen once
    window.setKeyRepeatEnabled(false);
    
    // sf::CircleShape shape(50.f);
    // shape.setFillColor(sf::Color::Blue);
    
    Event event;
    
    Texture texture;
    
    texture.setSmooth(true);
    
    texture.loadFromFile("sprite.png");
    
    if(!texture.loadFromFile("sprite.png"))
    {
        cout << "Failed to load texture image" << endl;
    }
    
    Sprite sprite(texture);
    
    sprite.setScale(Vector2f(0.7f, 0.7f));
    sprite.setTextureRect(IntRect(0,0, 150, 160));
    sprite.setPosition(Vector2f(300, 300));
    sprite.setOrigin(70,80);
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        
        while (window.pollEvent(event))
        {
            
            // Close window: exit
            if (event.type == Event::Closed)
            {
                window.close();
            }
            
            else if (event.type == Event::KeyPressed)
            {
                
                if (event.key.code == Keyboard::Right)
                {
                    sprite.move(5,0);
                }
                
                if (event.key.code == Keyboard::Left)
                {
                    sprite.move(-5,0);
                }
                
                if (event.key.code == Keyboard::Up)
                {
                    sprite.move(0,-5);
                }
                
                if (event.key.code == Keyboard::Down)
                {
                    sprite.move(0,5);
                }
                
                if (event.key.code == Keyboard::Tab)
                {
                    sprite.rotate(5);
                }
                
                if (event.key.code == Keyboard::LBracket)
                {
                    sprite.scale(.9,.9);
                }
                
                if (event.key.code == Keyboard::RBracket)
                {
                    sprite.scale(1.1,1.1);
                }
            }
        }
        
        // Clear screen
        window.clear();
        
        //-------------------Draw anything here-------------------------
        
        // window.draw(shape);
        window.draw(sprite);
        
        // Update the window
        window.display();
    }
    
    return 0;
}
