#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "IWeapon.h"
#include "Animator.h"

class Player {
private:
    sf::Sprite m_sprite;
    float m_speed;
    int m_hp;
    int m_xp;

	std::unique_ptr<Animator> m_animator;
	sf::Vector2f m_lastDirection;
    std::vector<std::unique_ptr<IWeapon>> m_weapons;
    void handleInput(float dt);

public:
    Player();
	~Player();

    void update(float dt, std::vector<Projectile>& projectiles);
    void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;

    int getHP();
    void takeDamage(int damage);

};