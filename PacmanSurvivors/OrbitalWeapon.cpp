#include "OrbitalWeapon.h"
#include <sfml/Graphics.hpp>
#include <cmath>

OrbitalWeapon::OrbitalWeapon()
    : m_angle(0.f),
    m_radius(150.f), // Quay ở bán kính 100 pixel
    m_orbCount(3),     // Bắt đầu với 3 quả cầu
    m_damage(25),
    m_damageCooldown(1.0f), // Mỗi quả cầu chỉ gây sát thương 1 lần/giây
    m_damageTimer(0.f)
{
    const sf::Texture& tex = AssetManager::getInstance().getTexture("Suriken.png");
    m_orbSprites.reserve(m_orbCount);
    // Khởi tạo các quả cầu
    for (int i = 0; i < m_orbCount; ++i)
    {
        m_orbSprites.emplace_back(tex);

        sf::Sprite& newSprite = m_orbSprites.back();

        newSprite.setOrigin({ 8.f, 8.f });
		newSprite.setScale({ 2.f, 2.f });

        auto animator = std::make_unique<Animator>(newSprite);

        int frameWidth = 16;
        int frameHeight = 16;
        int numFrames = 4;
        std::vector<sf::IntRect> animFrames;
        for (int j = 0; j < numFrames; ++j) {
            animFrames.push_back(sf::IntRect({ frameWidth * j, 0 }, { frameWidth, frameHeight }));
        }
        animator->addAnimation("SPIN", animFrames, 0.1f);
        animator->play("SPIN");

        m_orbs.push_back(std::move(animator));
    }
}
void OrbitalWeapon::update(float dt,
    sf::Vector2f playerPos,
    std::vector<Projectile>& projectiles,
    const std::vector<std::unique_ptr<IEnemy>>& enemies)
{
    // Tốc độ quay (radian/giây)
    const float PI = 3.14159265f;
    float spinSpeed = 2.0f;
    m_angle += spinSpeed * dt;
    // Cập nhật cooldown sát thương
    m_damageTimer += dt;
    bool canDealDamage = (m_damageTimer >= m_damageCooldown);
    // Di chuyển và cập nhật từng quả cầu
    for (int i = 0; i < m_orbCount; ++i)
    {
        // Tính toán vị trí (chia đều các quả cầu trên vòng tròn)
        float currentAngle = m_angle + (i * (2.f * PI / m_orbCount));

        sf::Vector2f offset = { std::cos(currentAngle) * m_radius, std::sin(currentAngle) * m_radius };
        sf::Vector2f orbPos = playerPos + offset;

        // Di chuyển quả cầu
        m_orbs[i]->getSprite().setPosition(orbPos);

        // Chạy animation của quả cầu
        m_orbs[i]->update(dt);

        //TỰ KIỂM TRA VA CHẠM (Nếu cooldown đã sẵn sàng)
        if (canDealDamage)
        {
            sf::FloatRect orbBounds = m_orbs[i]->getSprite().getGlobalBounds();

            for (auto& enemy : enemies)
            {
                if (orbBounds.findIntersection(enemy->getBounds()))
                {
                    enemy->takeDamage(m_damage);
                }
            }
        }
    }

    // Reset cooldown nếu đã gây sát thương
    if (canDealDamage)
    {
        m_damageTimer = 0.f;
    }
}
void OrbitalWeapon::draw(sf::RenderWindow& window)
{
    // Vẽ từng quả cầu
    for (auto& orb : m_orbs)
    {
        window.draw(orb->getSprite());
    }
}