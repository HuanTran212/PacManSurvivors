#pragma once
#include "IWeapon.h"
#include "Animator.h"
#include "AssetManager.h"
#include <vector>
#include <memory>

class OrbitalWeapon : public IWeapon
{
public:
    OrbitalWeapon();

    void update(float dt,
        sf::Vector2f playerPos,
        std::vector<Projectile>& projectiles,
        const std::vector<std::unique_ptr<IEnemy>>& enemies) override;

    void draw(sf::RenderWindow& window) override;
private:
    std::vector<std::unique_ptr<Animator>> m_orbs;
    std::vector<sf::Sprite> m_orbSprites;
    // Thông số quỹ đạo
    float m_angle;       // Góc quay (sẽ tăng liên tục)
    float m_radius;      // Bán kính quỹ đạo
    int m_orbCount;      // Số lượng quả cầu
    // Logic sát thương
    int m_damage;
    float m_damageCooldown; // Thời gian giãn cách giữa các lần gây sát thương
    float m_damageTimer;
};