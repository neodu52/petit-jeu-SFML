#include "Map.hpp"

Map::Map()
{
    if (!m_tileset.loadFromFile("assets/textures/MC32pxTextures1.png"))
        std::cerr << "Texture introuvable\n";

    if (!loadFromFile("assets/maps/test.tmj"))
        std::cerr << "Carte introuvable\n";
}


void Map::draw(sf::RenderWindow& window)
{
    sf::Sprite sprite(m_tileset);   // SFML 3 : un Sprite exige une texture à la construction

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int gid = m_tiles[x + y * m_width];
            if (gid == 0)
                continue;           // case vide : on ne dessine rien

            int id = gid - 1;
            int tx = id % TILESET_COLUMNS;
            int ty = id / TILESET_COLUMNS;
            int px = tx * (TILE_SIZE + TILESET_SPACING);
            int py = ty * (TILE_SIZE + TILESET_SPACING);

            sprite.setTextureRect(sf::IntRect({px, py}, {TILE_SIZE, TILE_SIZE}));
            sprite.setPosition({static_cast<float>(x * TILE_SIZE),
                                static_cast<float>(y * TILE_SIZE)});
            window.draw(sprite);
        }
    }


}

bool Map::loadFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    nlohmann::json j = nlohmann::json::parse(file);

    m_width  = j["width"];
    m_height = j["height"];
    m_solid.assign(m_width * m_height, false);

    for (const auto& layer : j["layers"])
    {
        if (layer["type"] != "tilelayer")
            continue;

        if (layer["name"] == "collision")
        {
            // à toi : parcourir layer["data"] et mettre m_solid[i] à true
            // quand la valeur est différente de 0
            auto data = layer["data"].get<std::vector<int>>();
            for (int i = 0; i < data.size() ; i++)
                if (data[i] != 0)
                    m_solid[i] = true;
        }
        else
        {
            m_tiles = layer["data"].get<std::vector<int>>();
        }
    }

    return true;
}

bool Map::isSolid(int x, int y) const
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return true;    // hors de la carte = bloqué

    return m_solid[x + y * m_width];
}

bool Map::isSolidAt(sf::Vector2f worldPos) const
{
    int tx = static_cast<int>(std::floor(worldPos.x / TILE_SIZE));
    int ty = static_cast<int>(std::floor(worldPos.y / TILE_SIZE));
    return isSolid(tx, ty);
}