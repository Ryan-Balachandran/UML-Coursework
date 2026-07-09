#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

#include "RingBuffer.hpp"
#include "GuitarString.hpp"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100
/*
 change the SAMPLES_PER_SEC from 44100 to 9100
 and the SAMPLING_RATE in GuitarString.cpp to 82000 for a different sound
 */

using namespace sf;
using namespace std;

vector<int16_t> makeSamplesFromString(GuitarString& gs)
{
    vector<int16_t> samples;
    gs.pluck();
    
    int duration = 8;  // seconds
    
    for (int i = 0; i < SAMPLES_PER_SEC * duration; i++)
    {
        gs.tic();
        samples.push_back(gs.sample());
    }
    
    return samples;
}

int main()
{    
    RenderWindow window(VideoMode(300, 200), "SFML Guitar Hero");
    window.setKeyRepeatEnabled(false);
    
    double freq = CONCERT_A;
    int size = 37;
    
    vector<vector<int16_t> > samples(size);
    vector<SoundBuffer> buffers(size);
    vector<Sound> sounds(size);
    
    string key = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
    
    for (int i = 0; i < size; i++)
    {
        freq = 100 + (i*20);
        
        GuitarString gstring = GuitarString(freq);
        
        samples[i] = makeSamplesFromString(gstring);
        buffers[i].loadFromSamples(&samples[i][0], samples[i].size(), 2, SAMPLES_PER_SEC);
        sounds[i].setBuffer(buffers[i]);
    }
    
    int count = 0;
    
    while (window.isOpen())
    {
        Event event;
        
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }
            
            if (event.type == Event::TextEntered)
            {
                count = 0;
                
                for (string::iterator it = key.begin(); it != key.end(); ++it)
                {
                    if (*it == static_cast<char>(event.text.unicode))
                    {
                        sounds[count].play();
                    }
                    
                    count++;
                }
            }
            
            window.clear();
            window.display();
        }
    }
    
    return 0;
}


