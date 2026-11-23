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
    if (direction != sf::Vector2f(0.f, 0.f))    // normalisation du vecteur pour evité les déplacement plus rapide en diagonal
        direction = direction.normalized();  
    if (direction != sf::Vector2f(0.f, 0.f))
        m_sprite.setRotation(direction.angle() + sf::degrees(90.f));

    if (sf::Joystick::isConnected(0))
    {
        float jx = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
        float jy = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
        // valeurs entre -100 et +100
        sf::Vector2f stick(jx / 100.f, jy / 100.f);   // ramené entre -1 et 1
        if (stick.length() > 0.2f)
            direction += stick;
        if (direction.lengthSquared() > 1.f)
            direction = direction.normalized();
        if (direction != sf::Vector2f(0.f, 0.f))
            m_sprite.setRotation(direction.angle() + sf::degrees(90.f));
    }

    
    sf::Vector2f movement = direction * m_speed * dt;
    sf::Vector2f m_halfSize{16.f, 16.f};

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