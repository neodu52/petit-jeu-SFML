# pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <iostream>

class Player
{
private:
    sf::Vector2f m_facing{0.f, -1.f};
    sf::Vector2f m_halfSize{16.f, 16.f};
    float m_speed;
    sf::Texture m_texture;
    sf::Sprite  m_sprite;

public:
    Player();

    void update(float dt, const Map& map);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;

};