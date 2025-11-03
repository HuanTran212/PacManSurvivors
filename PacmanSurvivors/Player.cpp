#include "Player.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PelletShooter.h"

Player::Player()
	: m_sprite(AssetManager::getInstance().getTexture("Player.png")),
	m_speed(200.f),
    m_hp(100),
	m_xp(0)
{
	m_animator = std::make_unique<Animator>(m_sprite);

    // Kích thước của MỘT frame
    int frameWidth = 256;
    int frameHeight = 256;

    // Hàng 1: Đi xuống (Y = 0)
    std::vector<sf::IntRect> walkDownFrames = {
        sf::IntRect({0, 0}, {frameWidth, frameHeight}),
        sf::IntRect({frameWidth * 1, 0}, {frameWidth, frameHeight}), // (256, 0)
        sf::IntRect({frameWidth * 2, 0}, {frameWidth, frameHeight}), // (512, 0)
        //sf::IntRect({frameWidth * 3, 0}, {frameWidth, frameHeight})  // (768, 0)
    };

    // Hàng 2: Đi lên (Y = 256)
    std::vector<sf::IntRect> walkUpFrames = {
        sf::IntRect({0, frameHeight * 1}, {frameWidth, frameHeight}), // (0, 256)
        sf::IntRect({frameWidth * 1, frameHeight * 1}, {frameWidth, frameHeight}), // (256, 256)
        sf::IntRect({frameWidth * 2, frameHeight * 1}, {frameWidth, frameHeight}), // (512, 256)
        sf::IntRect({frameWidth * 3, frameHeight * 1}, {frameWidth, frameHeight})  // (768, 256)
    };

    // Hàng 3: Đi trái (Y = 512)
    std::vector<sf::IntRect> walkLeftFrames = {
        sf::IntRect({0, frameHeight * 2}, {frameWidth, frameHeight}), // (0, 512)
        sf::IntRect({frameWidth * 1, frameHeight * 2}, {frameWidth, frameHeight}), // (256, 512)
        sf::IntRect({frameWidth * 2, frameHeight * 2}, {frameWidth, frameHeight}), // (512, 512)
        sf::IntRect({frameWidth * 3, frameHeight * 2}, {frameWidth, frameHeight})  // (768, 512)
    };

    // Hàng 4: Đi phải (Y = 768)
    std::vector<sf::IntRect> walkRightFrames = {
        sf::IntRect({0, frameHeight * 3}, {frameWidth, frameHeight}), // (0, 768)
        sf::IntRect({frameWidth * 1, frameHeight * 3}, {frameWidth, frameHeight}), // (256, 768)
        sf::IntRect({frameWidth * 2, frameHeight * 3}, {frameWidth, frameHeight}), // (512, 768)
        sf::IntRect({frameWidth * 3, frameHeight * 3}, {frameWidth, frameHeight})  // (768, 768)
    };

    std::vector<sf::IntRect> idleFrames = {
        sf::IntRect({0,0}, {frameWidth, frameHeight}),
        sf::IntRect({frameWidth * 1, 0}, {frameWidth, frameHeight}),
        sf::IntRect({frameWidth * 2, 0}, {frameWidth, frameHeight}),
        //sf::IntRect({frameWidth * 3, 0}, {frameWidth, frameHeight})
    }; // Thêm idle (đứng yên)

    // Thêm các animation vào Animator
    m_animator->addAnimation("WALK_DOWN", walkDownFrames, 0.1f);
    m_animator->addAnimation("WALK_UP", walkUpFrames, 0.1f);
    m_animator->addAnimation("WALK_LEFT", walkLeftFrames, 0.1f);
    m_animator->addAnimation("WALK_RIGHT", walkRightFrames, 0.1f);
    m_animator->addAnimation("IDLE", idleFrames, 0.15f);

    m_animator->play("IDLE"); // Ban đầu đứng yên
    m_sprite.setPosition({ 640, 360 });
    m_weapons.push_back(std::make_unique<PelletShooter>());
}

Player::~Player() {};

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

	// Cập nhật animation dựa trên hướng di chuyển
    if (movement.x > 0.f) m_animator->play("WALK_RIGHT");
    else if (movement.x < 0.f) m_animator->play("WALK_LEFT");
    else if (movement.y > 0.f) m_animator->play("WALK_DOWN");
    else if (movement.y < 0.f) m_animator->play("WALK_UP");
    else m_animator->play("IDLE");

    m_sprite.move(movement);
}

void Player::update(float dt, std::vector<Projectile>& projectiles) {
	handleInput(dt);
    m_animator->update(dt);

	// Cập nhật vũ khí
    for (auto& weapon : m_weapons) {
        weapon->update(dt, m_sprite.getPosition(), projectiles);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const {
    return m_sprite.getPosition();
}

int Player::getHP() {
    return m_hp;
}

void Player::takeDamage(int damage) {
    m_hp -= damage;
    std::cout << "Player took " << damage << " damage! HP = " << m_hp << std::endl;
}