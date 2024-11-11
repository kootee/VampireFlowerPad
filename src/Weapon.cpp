#include "Weapon.h"
#include "Constants.h"
#include "ParticleSystem.h"

Weapon::Weapon() : Rectangle(sf::Vector2f(0, 0))
{
    setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setColor(sf::Color::Blue);
    m_particleSystem = ParticleSystem(100, sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
}

void Weapon::setActive(bool isActive)
{
    m_isActive = isActive;

    if (isActive)
    {
        setSize(sf::Vector2f(WeaponWidth, WeaponHeight));
        
        m_particleSystem.sprayParticles(50, this->getPosition()); // fix
        m_particleSystem.update(50.0f, this->getPosition());
        m_timer = WeaponActiveTime;
    }
    else
    {
        setSize(sf::Vector2f(0.0f, 0.0f));
        m_timer = 0.0f;
    }
}

void Weapon::update(float deltaTime)
{
    if (m_isActive)
    {
        m_timer -= deltaTime;
        if (m_timer <= 0.0f)
        {
            setActive(false);
        }
    }
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape graphicsRect(getSize());
    graphicsRect.setFillColor(getColor());
    graphicsRect.setPosition(getPosition());
    target.draw(graphicsRect);
    m_particleSystem.draw(target, states);   
}