/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 2/11/19
 Problem Set 1b
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include "LFSR.hpp"

using namespace sf;  
using namespace std;

//--------------------START OF MAIN--------------------------------------------------
int main()
{
    // variables for getting input file, output file, lfsr seed and tap position
    string input_file;
    string output_file;
    string lfsr_seed;
    int lfsr_tap;
    
    // SFML------------------------
    Image input_image;
    Texture input_texture;
    Sprite input_sprite;
    
    Image output_image;
    Texture output_texture;
    Sprite output_sprite;
    
    cout << "Input file name: ";
    cin >> input_file;
    
    cout << "Output file name: ";
    cin >> output_file;
    
    cout << "lfsr seed: ";
    cin >> lfsr_seed;
    
    cout << "lfsr tap: ";
    cin >> lfsr_tap;
    
    cout << endl << "------------------------------------------------" << endl;
    cout << "Input file selected: " << input_file << endl;
    cout << "Output file selected: " << output_file << endl;
    cout << "lfsr seed selected: " << lfsr_seed << endl;
    cout << "lfsr tap selected: " << lfsr_tap << endl;
    cout << endl << "------------------------------------------------" << endl;
    
    if (!input_image.loadFromFile(input_file))
    {
        cout << "Invalid input file name." << endl;
    }
    
    Vector2u size = input_image.getSize();
    Color pixel;
    // Color result;
    
    input_texture.loadFromImage(input_image);
    input_sprite.setTexture(input_texture);
    
    output_image.create(size.x, size.y, Color::White);
    
    LFSR lfsr(lfsr_seed, lfsr_tap);
    
    for (unsigned int w = 0; w < size.x; w++)
    {
        for (unsigned int h = 0; h < size.y; h++)
        {
            pixel = input_image.getPixel(w, h);
            pixel.r = pixel.r ^ lfsr.generate(lfsr_tap);    // changed from 8 to variable
            pixel.g = pixel.g ^ lfsr.generate(lfsr_tap);
            pixel.b = pixel.b ^ lfsr.generate(lfsr_tap);
            output_image.setPixel(w, h, pixel);
        }
    }
    
    RenderWindow window(VideoMode(size.x*2+30, size.y), "Encode/Decode image");
    
    output_texture.loadFromImage(output_image);
    output_sprite.setTexture(output_texture);
    output_sprite.setPosition(size.x+30, 0);
    
    while (window.isOpen())
    {
        Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear(Color::White);
        window.draw(input_sprite);
        window.draw(output_sprite);
        window.display();
    }
    
    
    if (!output_image.saveToFile(output_file))
    {
        cout << "Error saving output image to file." << endl;
    }
    
    return 0;
}
//---------------------END OF MAIN---------------------------------------------------
