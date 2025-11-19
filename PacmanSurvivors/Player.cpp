#include "Player.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PelletShooter.h"

Player::Player()
	: m_sprite(AssetManager::getInstance().getTexture("Idle.png")),
	m_speed(70.f),
    m_hp(100),
	m_maxHP(100),
	m_xp(0),
    m_level(1)
{
	m_animator = std::make_unique<Animator>(m_sprite);
    // Kích thước của MỘT frame
    int frameWidth = 128;
    int frameHeight = 128;
    std::vector<sf::IntRect> idleFrames;
    for (int i = 0; i < 6; ++i) // Lặp qua 6 frame
    {
        // (i * 128, 0)
        idleFrames.emplace_back(sf::IntRect({ frameWidth * i, 0 }, { frameWidth, frameHeight }));
    }
	std::vector<sf::IntRect> hurtFrames;
    for (int i = 0; i < 4; ++i) // Lặp qua 4 frame
    {
        // (i * 128, 128)
        hurtFrames.emplace_back(sf::IntRect({ frameWidth * i, frameHeight }, { frameWidth, frameHeight }));
    }
    
    // Thêm các animation vào Animator
    m_animator->addAnimation("WALK_DOWN", idleFrames, 0.1f);
    m_animator->addAnimation("WALK_UP", idleFrames, 0.1f);
    m_animator->addAnimation("WALK_LEFT", idleFrames, 0.1f);
    m_animator->addAnimation("WALK_RIGHT", idleFrames, 0.1f);
    m_animator->addAnimation("IDLE", idleFrames, 0.25f);
	m_animator->addAnimation("HURT", hurtFrames, 0.1f);
    m_animator->play("IDLE"); // Ban đầu đứng yên
	m_sprite.setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    m_sprite.setPosition({ 100000, 100000 });
	m_sprite.setScale({ 1.5f, 1.5f });
    m_weapons.push_back(std::make_unique<PelletShooter>());

    /*m_hitboxDebug.setFillColor(sf::Color::Transparent);
    m_hitboxDebug.setOutlineColor(sf::Color::Red);
    m_hitboxDebug.setOutlineThickness(1.f);*/
}

Player::~Player() {};

void Player::processInput(float dt) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= m_speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += m_speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= m_speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += m_speed * dt;

    if(!m_isHurt)
    {
        // Cập nhật animation dựa trên hướng di chuyển
        if (movement.x > 0.f)
        {
            m_animator->play("WALK_RIGHT");
            m_sprite.setScale({ 1.5f, 1.5f });
        }
        else if (movement.x < 0.f)
        {
            m_animator->play("WALK_LEFT");
            m_sprite.setScale({ -1.5f, 1.5f });
        }
        else if (movement.y > 0.f)
        {
            m_animator->play("WALK_DOWN");
        }
        else if (movement.y < 0.f)
        {
            m_animator->play("WALK_UP");
        }
        else
        {
            m_animator->play("IDLE");
        }
    }
	

    m_sprite.move(movement);
}

void Player::update(float dt, std::vector<Projectile>& projectiles, const std::vector<std::unique_ptr<IEnemy>>& enemies)
{
    if (m_isHurt)
    {
        m_hurtTimer -= dt;
        if (m_hurtTimer <= 0.f)
        {
            m_isHurt = false;
        }
    }
	processInput(dt);
    m_animator->update(dt);

	// Cập nhật vũ khí
    for (auto& weapon : m_weapons) {
        weapon->update(dt, m_sprite.getPosition(), projectiles, enemies);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
    //sf::FloatRect bounds = this->getBounds();

    // 3. Cập nhật hình chữ nhật debug
   /* m_hitboxDebug.setPosition(bounds.position);
    m_hitboxDebug.setSize(bounds.size);*/

    for(auto& weapon : m_weapons) {
        weapon->draw(window);
	}
    // 4. Vẽ hitbox đè lên trên
    //window.draw(m_hitboxDebug);
}

sf::Vector2f Player::getPosition() const {
    return m_sprite.getPosition();
}

sf::FloatRect Player::getBounds() const
{
    sf::Vector2f pos = m_sprite.getPosition();
    float left = pos.x - 20;
    float top = pos.y - 50;
    sf::FloatRect bounds({left, top} , { 43.f, 70.f});
    return bounds;
}

int Player::getHP() const
{
    return m_hp;
}

int Player::getMaxHP() const
{
    return m_maxHP;
}

int Player::getLevel() const
{
	return m_level;
}

int Player::getXP() const
{
	return m_xp;
}

void Player::takeDamage(int damage) {
    if(m_animator->play("HURT"), m_isHurt)
		return; // Đang trong trạng thái bị thương, không nhận thêm sát thương
	m_isHurt = true;
	m_hurtTimer = 0.4f; // Thời gian bất tử sau khi bị thương
	m_animator->play("HURT");
    m_hp -= damage;
    if(m_hp < 0)
		m_hp = 0;
}

void Player::addWeapon(std::unique_ptr<IWeapon> weapon)
{
	m_weapons.push_back(std::move(weapon));
}

int Player::getXPToNextLevel() const
{
    int xpToNextLevel = m_level * 20;
    return xpToNextLevel;
}

int Player::addXP(int xpGained)
{
	int leveledUp = 0;
	int xpToNextLevel = getXPToNextLevel();
	m_xp += xpGained;

    while(m_xp >= xpToNextLevel)
    {
		leveledUp++;
        m_xp -= xpToNextLevel;
        xpToNextLevel = getXPToNextLevel();
        m_level++;
        std::cout << "Level Up! New Level: " << m_level << std::endl;
	}
	return leveledUp;
}

void Player::heal(int amount)
{
    m_hp += amount;
    if(m_hp > m_maxHP)
		m_hp = m_maxHP;
}

void Player::addmaxHP(int amount)
{
    m_maxHP += amount;
	m_hp += amount; // Cũng hồi phục thêm tương ứng
}

void Player::addMoveSpeed(float amount)
{
	m_speed += amount;
}

float Player::getMoveSpeed() const
{
	return m_speed;
}
