#pragma once
#include <SFML/Graphics.hpp>
#include "IEnemy.h"

class Ghost : public IEnemy
{
private:
    sf::Sprite m_sprite;
    float m_speed;
    sf::Vector2f m_velocity;
    float m_health; // để dùng với TakeDamage và IsDead

public:
    Ghost(sf::Vector2f spawnPos = { 300.f, 400.f });

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
};
