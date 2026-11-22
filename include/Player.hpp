# pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape m_shape;
    float m_speed;


public:
    Player();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
};