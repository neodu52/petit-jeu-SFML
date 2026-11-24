#include "Player.hpp"

Player::Player() : m_sprite(m_texture), m_speed(300.f) {
    // 1. On charge d'abord la texture
    if (!m_texture.loadFromFile("assets/textures/chevalier.png")) {
        std::cerr << "Texture joueur introuvable\n";
    }

    // 2. On met à jour le sprite avec la nouvelle texture
    m_sprite.setTexture(m_texture, true);

    // 3. Maintenant que la texture a une vraie taille, on calcule le centre
    sf::Vector2u texture_taille = m_texture.getSize();
    m_sprite.setOrigin({texture_taille.x / 2.f, texture_taille.y / 2.f});
    
    // 4. On positionne le sprite
    m_sprite.setPosition({400.f, 300.f});
}

void Player::update(float dt, const Map& map)
{
    sf::Vector2f direction{0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    // scancode = position physique sur le clavier
    {
        direction.y -= 1.f;    // changement de la norme du vecteur sur l'axe y (deuxime valeur), servira de coefficient pour calculer la vitesse plus tard cf player.move
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))  // pas de elif ici sinon le joueur ne peut plus se déplacer en diagonal
    {
        direction.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        direction.x += 1.f;
    }

    sf::Vector2f aim{0.f, 0.f};

    if (sf::Joystick::isConnected(0))
    {
        // stick gauche : déplacement
        float jx = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
        float jy = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
        sf::Vector2f stick(jx / 100.f, jy / 100.f);
        if (stick.length() > 0.2f)
            direction += stick;

        // stick droit : visée
        float ax = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z);
        float ay = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R);
        sf::Vector2f stickDroit(ax / 100.f, ay / 100.f);
        if (stickDroit.length() > 0.3f)
            aim = stickDroit;

    }

    // 2. normalisation unique, une fois tout lu
    if (direction.lengthSquared() > 1.f)
        direction = direction.normalized();

    // 3. orientation : stick droit prioritaire, sinon la marche
    if (aim != sf::Vector2f(0.f, 0.f))
        m_facing = aim.normalized();
    else if (direction != sf::Vector2f(0.f, 0.f))
        m_facing = direction.normalized();

    m_sprite.setRotation(m_facing.angle() + sf::degrees(90.f));

    
    sf::Vector2f movement = direction * m_speed * dt;
    // axe X
    m_sprite.move({movement.x, 0.f});
    if (map.isSolidRect(m_sprite.getPosition(), m_halfSize))
        m_sprite.move({-movement.x, 0.f});   // on annule

    // axe Y
    m_sprite.move({0.f, movement.y});
    if (map.isSolidRect(m_sprite.getPosition(), m_halfSize))
        m_sprite.move({0.f, -movement.y});
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}