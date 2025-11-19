#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "IWeapon.h"
#include "Animator.h"

class Player {
private:
	sf::Sprite m_sprite;
    float m_speed;
	int m_level;
    int m_hp;
	int m_maxHP;
    int m_xp;
	bool m_isHurt = false;
	float m_hurtTimer = 0;

	std::unique_ptr<Animator> m_animator;
	sf::Vector2f m_lastDirection;
    std::vector<std::unique_ptr<IWeapon>> m_weapons;
    void processInput(float dt);
	sf::RectangleShape m_hitboxDebug;
public:
    Player();
	~Player();

    void update(float dt, std::vector<Projectile>& projectiles,const std::vector<std::unique_ptr<IEnemy>>& enemies);
    void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
    int getHP() const;
	int getMaxHP() const;
    int getLevel() const;
    int getXP() const;
    void takeDamage(int damage);
	void addWeapon(std::unique_ptr<IWeapon> weapon);
	int getXPToNextLevel() const;
	int addXP(int xpGainned);
	void heal(int amount);
	void addmaxHP(int amount);

	template <typename T>
		T* getWeapon()
		{
			for (auto& weapon : m_weapons) {
				// Kiểm tra xem vũ khí này có phải là kiểu T không
				T* specificWeapon = dynamic_cast<T*>(weapon.get());
				if (specificWeapon != nullptr) {
					return specificWeapon; // Tìm thấy! Trả về con trỏ.
				}
			}
			return nullptr;
		}

	void addMoveSpeed(float amount);
	float getMoveSpeed() const;
};