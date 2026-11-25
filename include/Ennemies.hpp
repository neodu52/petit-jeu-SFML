#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <iostream>

class Ennemies
{
public:
    Ennemies(const sf::Texture& texture, sf::Vector2f position,
         float vie, float vitesse, float degat);
    void update(float dt, sf::Vector2f playerPos, const Map& map);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture  m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_halfSize{14.f, 14.f};
    float m_vie;
    float m_vitesse;
    float m_degat;
};