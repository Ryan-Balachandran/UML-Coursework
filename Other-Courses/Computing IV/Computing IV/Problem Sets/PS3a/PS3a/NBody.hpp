/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 3/1/19
 Problem Set 3a
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;  

class Body: public Drawable
{
public:
    ~Body();
    Body();
    Body(Vector2f P, Vector2f V, double M, string F);
    
    void determine_position(double& radius, Vector2u wSize);
    
    void setPosition(Vector2f P);
    void setVelocity(Vector2f V);
    void setMass(double M);
    void setSprite();
    void setRenderPos(Vector2f renderPos);
    
    Vector2f getPosition() const;
    Vector2f getVelocity() const;
    double getMass();
    Sprite getSprite();
    Vector2f getRenderPos() const;
    string getFile();
    
    friend istream &operator>>(istream &input, Body& body);
    
private:
    Vector2u window;            // size of the window
    double universe_radius;     // Radius of the universe
    Vector2f render_position;   // position of sprite
    Vector2f position;          // XY position of a planet/particle
    Vector2f velocity;          // XY velocity of a planet/particle
    double mass;                // Mass of a planet/particle
    string filename;            // filename for the image of a planet/particle
    
    Image planet;
    Texture texture;
    Sprite object;
    
    virtual void draw(RenderTarget& target, RenderStates states) const;
};
