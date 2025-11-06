#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
private:
    sf::Sprite m_sprite;
    sf::Vector2f m_direction;
    sf::Vector2f m_velocity;
    float m_speed;
	int m_damage;
    bool m_isDestroyed;
public:
    Projectile(const sf::Texture& texture, sf::Vector2f playerPos, sf::Vector2f dir, float speed);
	int getDamage() const;
	void setDamage(int damage);
    void update(float dt);
    void draw(sf::RenderWindow& window);
	void destroy();
    bool isDestroyed() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
};
