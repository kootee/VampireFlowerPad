#pragma once

#include "Rectangle.h"

#define WATERLIMIT 10 // change to adjust how many drops has to hit

class Game;

class Vampire : public Rectangle
{
public:
    Vampire(Game* game, sf::Vector2f position);
    virtual ~Vampire() {}
    
    void update(float deltaTime);

    void setIsKilled(bool isKilled) { m_isKilled = isKilled; } // not killed, turned into a flower
    bool isKilled() { return m_isKilled; } // not killed, turned into a flower

    // get hit by water
    void getWatered();

private:
    Game* m_pGame;
    bool m_isKilled = false;

    // counter to stop the vampire
    int m_dropCounter;
};
