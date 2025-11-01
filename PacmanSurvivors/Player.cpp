#include "Player.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player() :m_sprite(AssetManager::getInstance().getTexture("pacman.png")), m_hp(3) {
    m_sprite.setPosition({ 400, 300 });
    m_speed = 200.0f;
}

void Player::handleInput(float dt) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= m_speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += m_speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= m_speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += m_speed * dt;

    m_sprite.move(movement);
}

void Player::update(float dt) {
	handleInput(dt);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}