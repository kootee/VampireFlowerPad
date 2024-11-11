#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

/* Move to own folder */
#include <vector>
#include <cmath>

struct Particle {
    sf::Vector2f    pos;
    sf::Vector2f    velocity;
    sf::Color       particleColor;
    float           time;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable 
{
    ParticleSystem(int amount, sf::Vector2f start) :
        m_particles(amount), m_start(start) {}
    ~ParticleSystem() = default;
    
    /* Class functions */
    void    setStart(sf::Vector2f start) { m_start = start; }
    void    sprayParticles(int particleAmount);
    void    update(float dt);

    private: 
        std::vector<Particle>   m_particles;
        sf::Vector2f            m_start;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

void    ParticleSystem::sprayParticles(int particleAmount) 
{
    for (int i = 0; i < particleAmount; i++)
    {
        Particle& p = m_particles[i];
        p.pos = m_start;
        p.velocity = sf::Vector2f(
            (std::rand() % 100 -50) * 0.1f, 
            (std::rand() % 100 -50) * 0.1f);
        p.particleColor = sf::Color::Cyan;
        p.time = particleLife;
    }
}

void    ParticleSystem::update(float dt)
{
    for (auto& p : m_particles) // update all particles
    {
        p.time -= dt;
        if (p.time <= 0)
        {
            p.pos = m_start;
            p.time = particleLife;
        }
        p.pos += p.velocity * dt;
        p.velocity.y += gravity * dt;
        float alpha = static_cast<sf::Uint8>(255 * (p.time / 1.0f));
        p.particleColor.a = alpha; // set alphachannel
    }
}

void    ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (const auto& p : m_particles)
    {
        sf::CircleShape drop(2);
        drop.setFillColor(p.particleColor);
        drop.setPosition(p.pos);
        target.draw(drop, states);
    }
}
/* MOVE TO OWN FOLDER */

class Rectangle : public sf::Drawable, public sf::Transformable
{
public:
    Rectangle(sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
    virtual ~Rectangle() {}
    
    bool collidesWith(Rectangle* pOther);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getCenter();

    void setSize(sf::Vector2f size) { m_size = size; }
    sf::Vector2f getSize() const { return m_size; }

    void setColor(sf::Color color) { m_color = color; }
    sf::Color getColor() const { return m_color; }

protected:
    sf::Sprite m_sprite;

private:
    sf::Color m_color = sf::Color::White;
    sf::Vector2f m_size;
};
