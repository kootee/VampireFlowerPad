#pragma once

/* Move FUNCTIONS to own folder */
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

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
        // void    setStart(sf::Vector2f start) { m_start = start; }
        void    sprayParticles(int particleAmount, sf::Vector2f pos);
        void    update(float dt, sf::Vector2f pos);
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private: 
        std::vector<Particle>   m_particles;
        // sf::Vector2f            m_start;

};
