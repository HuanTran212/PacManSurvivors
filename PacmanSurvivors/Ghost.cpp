#include "Ghost.h"
#include "AssetManager.h"
#include <cmath>

Ghost::Ghost(sf::Vector2f spawnPos)
    : m_sprite(AssetManager::getInstance().getTexture("Ghost.png")),
    m_speed(100.0f),
    m_velocity(0.f, 0.f),
    m_health(100.f)
{
    m_sprite.setPosition(spawnPos);
}

void Ghost::update(float dt, sf::Vector2f playerPos)
{
    sf::Vector2f ghostPos = m_sprite.getPosition();
    sf::Vector2f direction = playerPos - ghostPos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
		direction /= length; // Chuẩn hóa vector hướng
        m_velocity = direction * m_speed;
		m_sprite.move(m_velocity * dt);
    }
    else
    {
        m_velocity = sf::Vector2f(0.f, 0.f);
    }
}

void Ghost::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Ghost::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Ghost::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health < 0.f)
        m_health = 0.f;
}

bool Ghost::isDead() const
{
    return m_health <= 0.f;
}

int Ghost::getCollisionDamage() const
{
    return 5;
}

sf::Vector2f Ghost::getPosition() const
{
    return m_sprite.getPosition();
}

void Ghost::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}

void Ghost::applySeparation(const std::vector<std::unique_ptr<IEnemy>>& others)
{
    sf::Vector2f repel(0.f, 0.f);
    float desiredDistance = 40.f; // khoảng cách tối thiểu giữa quái

    for (auto& other : others)
    {
        if (other.get() == this) continue;

        sf::Vector2f diff = m_sprite.getPosition() - other->getPosition();
        float len = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (len > 0 && len < desiredDistance)
        {
            diff /= len; // hướng đẩy
            repel += diff * (desiredDistance - len);
        }
    }

    m_sprite.move(repel * 0.1f); // đẩy nhẹ ra
}

int Ghost::getXPReward() const
{
    return 10;
}
