#include "Ennemies.hpp"

Ennemies::Ennemies(sf::Vector2f position, float vie, float vitesse, float degat)
    : m_sprite(m_texture), m_vie(vie), m_vitesse(vitesse), m_degat(degat)
{
    if (!m_texture.loadFromFile("assets/textures/gobelin.png"))
        std::cerr << "Texture gobelin introuvable\n";

    m_sprite.setTexture(m_texture, true);
    sf::Vector2u t = m_texture.getSize();
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
}

void Ennemies::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
}
