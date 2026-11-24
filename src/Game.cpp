#include "Game.hpp"


Game::Game() : m_window(sf::VideoMode({1920, 1080}), "mon jeu"), m_camera(sf::Vector2f(m_window.getSize()))
{
    m_window.setFramerateLimit(120);
    m_marker.setPosition({100.f, 100.f});
}


void Game::run()
{
    sf::Clock clock;    // avant la boucle while
    while (m_window.isOpen())
    {
        float dt = clock.restart().asSeconds();   // au début de chaque tour
        // restart() remet le chrono à zéro et renvoie le temps écoulé depuis le dernier appel, ce qui est exactement ce qu’on veut.

        processEvents();
        update(dt);
        render();

    }
}

void Game::update(float dt)
{
    m_player.update(dt, m_map);
    m_camera.follow(m_player.getPosition());

}

void Game::processEvents()
{
    while(const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_window.close();

        else if (const auto* keyPresse = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPresse->code == sf::Keyboard::Key::Escape)
                m_window.close();
        }
        
    }
}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_camera.apply(m_window);
    m_map.draw(m_window);
    m_player.draw(m_window);
    m_window.display();
}
