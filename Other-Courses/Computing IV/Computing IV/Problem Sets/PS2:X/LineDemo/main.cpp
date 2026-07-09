/*
 * main.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: jon
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Line.hpp"

using namespace sf;
RenderWindow app(VideoMode(800, 600, 32), "Line Demo");

int main(void) {
	app.setFramerateLimit(60);

	/* Constructing a line segment from two points */
	LineSegment line1(Vector2f(0.0f, 0.0f), Vector2f(800.0f, 600.0f));

	/* Constructing a line segment from a point, length and angle */
	LineSegment line2(Vector2f(0.0f, 600.0f), -45, 128);


	Event event;
	while(app.isOpen()) {
		while(app.pollEvent(event)) {
			if(event.type == Event::Closed) {
				app.close();
				break;
			}
		}
		app.clear(Color::Black);
		app.draw(line1);
		app.draw(line2);
		//line2.rotate(1.0f);
		//line2.move(1.6f, 1.2f);
		//line2.scale(1.01f);
		app.display();
	}
}
