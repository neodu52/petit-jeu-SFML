#include "Player.hpp"

Player::Player() : m_shape({40.f, 40.f}), m_speed(300.f)
{
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOrigin({20.f, 20.f});
    m_shape.setPosition({400.f, 300.f});
}

void Player::update(float dt)
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
    
    m_shape.move(direction * m_speed * dt);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
}

sf::Vector2f Player::getPosition() const
{
    return m_shape.getPosition();
}