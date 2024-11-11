#include "ParticleSystem.h"
#include "Constants.h"

void    ParticleSystem::sprayParticles(int particleAmount, sf::Vector2f position) 
{
    for (int i = 0; i < particleAmount; i++)
    {
        Particle& p = m_particles[i];
        p.pos = position; // should be the end of the sword
        p.velocity = sf::Vector2f(
            (std::rand() % 100 -50) * 0.1f, 
            (std::rand() % 100 -50) * 0.1f);
        p.particleColor = sf::Color::Cyan;
        p.particleLifeSpan = particleLife;
    }
}

void    ParticleSystem::update(float dt, sf::Vector2f position)
{
    for (auto& p : m_particles) // update all particles
    {
        p.particleLifeSpan -= dt;
        if (p.particleLifeSpan <= 0)
        {
            p.pos = position;
            p.particleLifeSpan = particleLife;
        }
        p.pos += p.velocity * dt;
        p.velocity.y += gravity * dt;
        float alpha = static_cast<sf::Uint8>(255 * (p.particleLifeSpan / 1.0f));
        p.particleColor.a = alpha; // set alphachannel
    }

    m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(),
                    [](const Particle& p) { return p.particleLifeSpan <= 0; }),
                      m_particles.end());
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