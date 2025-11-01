#include "Ghost.h"
#include <cmath>

Ghost::Ghost(sf::Texture& texture, sf::Vector2f startPos, float moveSpeed)
    : m_sprite(texture),  // khởi tạo sprite bằng texture
    m_speed(moveSpeed),
    velocity(0.f, 0.f)
{
    m_sprite.setPosition(startPos);
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
    // Tạm thời chưa code gì ở đây
    // window.draw(sprite);
}