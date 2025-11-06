#include "PelletShooter.h"
#include <iostream>

PelletShooter::PelletShooter()
    : m_fireRate(1.2f), m_fireTimer(0.0f)
{
}

void PelletShooter::update(float dt,
    sf::Vector2f playerPos,
    std::vector<Projectile>& projectiles,
    const std::vector<std::unique_ptr<IEnemy>>& enemies)
{
    m_fireTimer += dt;
    // Kiểm tra nếu đã đến lúc bắn
    if (m_fireTimer >= m_fireRate)
    {
        m_fireTimer = 0.f;

        // --- GIẢI THUẬT TÌM KẺ THÙ GẦN NHẤT (DSA) ---
        IEnemy* nearestEnemy = nullptr;
        float minDistanceSq = std::numeric_limits<float>::max(); // Gán bằng vô cực

        for (auto& enemy : enemies)
        {
            sf::Vector2f enemyPos = enemy->getPosition(); // (Bạn cần thêm getPosition() vào IEnemy)
            sf::Vector2f toEnemy = enemyPos - playerPos;
            float distSq = toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y; // (Không cần Sqrt, nhanh hơn)

            if (distSq < minDistanceSq)
            {
                minDistanceSq = distSq;
                nearestEnemy = enemy.get(); // Lấy con trỏ thô
            }
        }

        // Nếu tìm thấy kẻ thù
        if (nearestEnemy)
        {
            // Bắn đạn về phía con ma GẦN NHẤT
            const sf::Texture& bulletTex = AssetManager::getInstance().getTexture("pellet.png");

            sf::Vector2f direction = nearestEnemy->getPosition() - playerPos;

            // Chuẩn hóa (Normalize) vector
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0) direction /= length;

            projectiles.push_back(Projectile(bulletTex, playerPos, direction, 400.f));
        }
        // (Nếu không có kẻ thù, súng sẽ không bắn)
    }
}

void PelletShooter::draw(sf::RenderWindow& window) {
    // Vũ khí này không có hình riêng nên không cần vẽ gì
}