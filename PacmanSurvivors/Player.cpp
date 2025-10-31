#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player() :m_texture(), m_sprite(m_texture) {
    if (!m_texture.loadFromFile("pacman.png")) {
        std::cerr << "⚠️ Không thể tải ảnh pacman.png\n";
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition({ 400, 300 });
    m_speed = 200.0f;
}

void Player::handleInput(float dt) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= m_speed * dt;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += m_speed * dt;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= m_speed * dt;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += m_speed * dt;

    m_sprite.move(movement);
}

void Player::update(float dt) {
    // Hiện chưa có gì
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}