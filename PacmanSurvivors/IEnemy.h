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
    virtual sf::FloatRect getBounds() const {return sf::FloatRect();};

    // Nhận sát thương
	virtual void takeDamage(int damage) = 0;

    // Kiểm tra còn sống không
    virtual bool isDead() const = 0;

	// Lấy vị trí hiện tại
	virtual sf::Vector2f getPosition() const = 0;

	// Đặt vị trí
	virtual void applySeparation(const std::vector<std::unique_ptr<IEnemy>>& others) = 0;

	// Lấy sát thương khi va chạm với người chơi
	virtual int getCollisionDamage() const = 0;

	// Lấy điểm kinh nghiệm thưởng khi bị tiêu diệt
	virtual int getXPReward() const = 0;
};
