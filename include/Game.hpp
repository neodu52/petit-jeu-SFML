#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Camera.hpp"
#include "Map.hpp"
#include "Ennemies.hpp"
#include <iostream>

class Game
{
private:
    void processEvents();
    void update(float dt);
    void render();
    sf::RenderWindow m_window;
    Player m_player;
    Camera m_camera;
    sf::RectangleShape m_marker;
    Map m_map;
    sf::Texture m_goblinTexture;
    std::vector<Ennemies> m_ennemies;

public:
    Game();
    void run();
};