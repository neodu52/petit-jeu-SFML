#include "Camera.hpp"

Camera::Camera(sf::Vector2f size) : m_view(sf::Vector2f{size.x / 2.f, size.y / 2.f}, size)
{
}

void Camera::follow(sf::Vector2f target)
{
    m_view.setCenter(target);
}

void Camera::apply(sf::RenderWindow& window)
{
    window.setView(m_view); 
}