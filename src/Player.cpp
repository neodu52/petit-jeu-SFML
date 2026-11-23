#include "Player.hpp"

Player::Player() : m_shape({40.f, 40.f}), m_speed(300.f)
{
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOrigin({20.f, 20.f});
    m_shape.setPosition({400.f, 300.f});
}

void Player::update(float dt, const Map& map)
{
    sf::Vector2f direction{0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    // scancode = position physique sur le clavier
    {
        direction.y -= 1.f;    // changement de la norme du vecteur sur l'axe y (deuxime valeur), servira de coefficient pour calculer la vitesse plus tard cf player.move
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))  // pas de elif ici sinon le joueur ne peut plus se déplacer en diagonal
    {
        direction.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        direction.x += 1.f;
    }
    if (direction != sf::Vector2f(0.f, 0.f))    // normalisation du vecteur pour evité les déplacement plus rapide en diagonal
        direction = direction.normalized();      
    
    sf::Vector2f movement = direction * m_speed * dt;
    sf::Vector2f half = m_shape.getSize() / 2.f;

    // axe X
    m_shape.move({movement.x, 0.f});
    if (map.isSolidRect(m_shape.getPosition(), half))
        m_shape.move({-movement.x, 0.f});   // on annule

    // axe Y
    m_shape.move({0.f, movement.y});
    if (map.isSolidRect(m_shape.getPosition(), half))
        m_shape.move({0.f, -movement.y});
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
}

sf::Vector2f Player::getPosition() const
{
    return m_shape.getPosition();
}