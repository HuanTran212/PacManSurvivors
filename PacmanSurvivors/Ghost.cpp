#include "Ghost.h"
#include "AssetManager.h"
#include <cmath>

Ghost::Ghost()
    : m_sprite(AssetManager::getInstance().getTexture("Ghost.png")),
	velocity(0.f, 0.f), m_speed(100.0f)
{
    m_sprite.setPosition({300, 400});
}


void Ghost::update(float dt, sf::Vector2f playerPos)
{
    // Lấy vị trí hiện tại của ghost
    sf::Vector2f ghostPos = m_sprite.getPosition();

    // Tính vector hướng đến người chơi
    sf::Vector2f direction = playerPos - ghostPos;

    // Chuẩn hóa vector (đưa về độ dài 1)
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    // Cập nhật vận tốc
    velocity = direction * m_speed;

    // Cập nhật vị trí theo thời gian dt
    m_sprite.move(velocity * dt);
}

void Ghost::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::Vector2f Ghost::getPosition() const
{
    return m_sprite.getPosition();
}

void Ghost::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}