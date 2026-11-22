#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cmath>

class Map
{
private:
    static constexpr int TILE_SIZE = 32;    // une constante partagée par toute la classe, connue à la compilation.
    // Elle évite d'écrire 32 partout dans le code (on parle de « nombre magique »).
    int m_width = 0;
    int m_height = 0;
    std::vector<int> m_tiles;
    std::vector<bool> m_solid;
    sf::Texture m_tileset;
    static constexpr int TILESET_COLUMNS = 58;
    static constexpr int TILESET_SPACING = 2;

public:
    Map(/* args */);
    void draw(sf::RenderWindow& window);
    bool loadFromFile(const std::string& path);
    bool isSolid(int x, int y) const;
    bool isSolidAt(sf::Vector2f worldPos) const;
};
