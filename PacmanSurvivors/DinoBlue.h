#pragma once
#include <SFML/Graphics.hpp>
#include "IEnemy.h"

class DinoBlue : public IEnemy
{
private:

    std::unique_ptr<Animator> m_animator;
    sf::Vector2f m_velocity;
    sf::Sprite m_sprite;

    float m_speed;
    float m_health; // để dùng với TakeDamage và IsDead

    sf::Vector2f m_knockbackVelocity;
    bool m_isKnockBack;

    bool m_isHurt;
    float m_hurtTimer;

    sf::Sprite m_shadowSprite;
    //sf::RectangleShape m_hitboxDebug;
public:
    DinoBlue(sf::Vector2f spawnPos);

    void update(float dt, sf::Vector2f playerPos) override;

    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const override;

    void takeDamage(int damage) override;

    bool isDead() const override;

    int getCollisionDamage() const override;

    sf::Vector2f getPosition() const override;

    void setPosition(sf::Vector2f pos);

    void applySeparation(const std::vector<std::unique_ptr<IEnemy>>& others);

    int getXPReward() const override;

    void applyKnockback(sf::Vector2f direction, float force) override;
};

