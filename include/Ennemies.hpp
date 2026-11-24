#pragma once
#include <SFML/Graphics.hpp>

class Ennemies
{
private:
    sf::Vector2f deplacement;
    void cherche_joueur(sf::Vector2f position_joueur) const;

public:
    float vitesse_deplacement;
    float vie;
    float degat;
    float shield;
    char nom;
};