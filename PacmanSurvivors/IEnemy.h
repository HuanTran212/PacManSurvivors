#pragma once
#include <SFML/Graphics.hpp>

class IEnemy
{
public:
    virtual ~IEnemy() {}

    // Cập nhật logic (AI)
    virtual void update(float dt, sf::Vector2f playerPosition) = 0;

    // Vẽ kẻ địch
    virtual void draw(sf::RenderWindow& window) = 0;

    // Lấy vùng va chạm
    virtual sf::FloatRect getBounds() const = 0;

    // Nhận sát thương
    virtual void takeDamage(float damage) = 0;

    // Kiểm tra còn sống không
    virtual bool isDead() const = 0;

	// Lấy vị trí hiện tại
	virtual sf::Vector2f getPosition() const = 0;

    //
	virtual void applySeparation(const std::vector<std::unique_ptr<IEnemy>>& others) = 0;
};
