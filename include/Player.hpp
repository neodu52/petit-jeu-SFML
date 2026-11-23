# pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Player
{
private:
    sf::RectangleShape m_shape;
    float m_speed;
    sf::Texture m_texture;
    sf::Sprite  m_sprite;

public:
    Player();

    void update(float dt, const Map& map);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;

};