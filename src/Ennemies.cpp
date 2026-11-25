#include "Ennemies.hpp"

Ennemies::Ennemies(const sf::Texture& texture, sf::Vector2f position,
                   float vie, float vitesse, float degat)
    : m_sprite(texture), m_vie(vie), m_vitesse(vitesse), m_degat(degat)
{
    sf::Vector2u t = texture.getSize();
    m_sprite.setOrigin({t.x / 2.f, t.y / 2.f});
    m_sprite.setPosition(position);
}

void Ennemies::update(float dt, sf::Vector2f playerPos, const Map& map)
{
    sf::Vector2f vers_joueur = playerPos - m_sprite.getPosition();
    if (vers_joueur.length() <= 1.f)
        return;                         // arrivé : on ne bouge plus

    sf::Vector2f direction = vers_joueur.normalized();
    sf::Vector2f movement  = direction * m_vitesse * dt;

    // à toi : déplacement axe par axe avec map.isSolidRect,
    // exactement comme dans Player::update

    m_sprite.move({movement.x, 0.f});
    if (map.isSolidRect(m_sprite.getPosition(), m_halfSize))
        m_sprite.move({-movement.x, 0.f});   // on annule

    // axe Y
    m_sprite.move({0.f, movement.y});
    if (map.isSolidRect(m_sprite.getPosition(), m_halfSize))
    {
        m_sprite.move({0.f, -movement.y});
    }

    m_sprite.setRotation(movement.angle() + sf::degrees(90));
}

void Ennemies::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
