#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
    sf::View m_view;
public:
    Camera(sf::Vector2f size);
    void follow(sf::Vector2f target);   //follow : place le centre de la vue sur la cible
    void apply(sf::RenderWindow& window);   // apply : appelle window.setView(m_view)
};
