#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Vampire.h"

struct Particle {
    sf::Vector2f    pos;
    sf::Vector2f    velocity;
    sf::Color       particleColor;
    float           particleLifeSpan;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable 
{
    public:
        ParticleSystem() : m_particles(0) {};
        ParticleSystem(int amount, sf::Vector2f start) :
            m_particles(amount) {}
        ~ParticleSystem() = default;
        
        /* Class functions */
        void    sprayParticles(int particleAmount, sf::Vector2f pos);
        void    update(float dt, sf::Vector2f pos);
        bool    particleCollision(Vampire &vampire);
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private: 
        std::vector<Particle>   m_particles;
};
