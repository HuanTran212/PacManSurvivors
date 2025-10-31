#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    float m_speed;

public:
    Player();
    void handleInput(float dt);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};
