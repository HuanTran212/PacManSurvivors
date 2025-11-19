#include "DinoBlue.h"
#include "AssetManager.h"
#include <cmath>

DinoBlue::DinoBlue(sf::Vector2f spawnPos)
    : m_sprite(AssetManager::getInstance().getTexture("DinoBlue.png")),
    m_speed(60.0f),
    m_velocity(0.f, 0.f),
    m_health(200.f),
    m_knockbackVelocity(0.f, 0.f),
    m_isKnockBack(false),
    m_isHurt(false),
    m_hurtTimer(0.f),
    m_shadowSprite(AssetManager::getInstance().getTexture("shadow_Dino.png"))
{
    m_animator = std::make_unique<Animator>(m_sprite);

    int frameWidth = 24;
    int frameHeight = 24;

    std::vector<sf::IntRect> walk;

    for (int i = 0; i < 7; ++i)
    {
        walk.emplace_back(sf::IntRect({ frameWidth * i, frameHeight * 3 }, { frameWidth, frameHeight }));
    }

    std::vector<sf::IntRect> run;

    for (int i = 0; i < 7; ++i)
    {
        run.emplace_back(sf::IntRect({ frameWidth * i, frameHeight * 1 }, { frameWidth, frameHeight }));
    }

    std::vector<sf::IntRect> hurt;

    for (int i = 0; i < 3; ++i)
    {
        hurt.emplace_back(sf::IntRect({ frameWidth * i, frameHeight * 2 }, { frameWidth, frameHeight }));
    }


    m_animator->addAnimation("WALK", walk, 0.1f);
    m_animator->addAnimation("RUN", run, 0.1f);
    m_animator->addAnimation("HURT", hurt, 0.1f);
    m_animator->play("WALK");

    m_sprite.setOrigin({ frameWidth / 2.f, frameHeight / 2.f });
    m_sprite.setPosition(spawnPos);
    m_sprite.setScale({ 2.f, 2.f });

    m_shadowSprite.setScale({ 2.f, 2.f });
    m_shadowSprite.setOrigin({ 12.f, 12.f });

    /*m_hitboxDebug.setFillColor(sf::Color::Transparent);
    m_hitboxDebug.setOutlineColor(sf::Color::Red);
    m_hitboxDebug.setOutlineThickness(1.f);*/
}

void DinoBlue::update(float dt, sf::Vector2f playerPos)
{
    m_animator->update(dt);

    if (m_isHurt)
    {
        m_hurtTimer -= dt;

        if (m_hurtTimer <= 0.f)
        {
            m_isHurt = false;
        }
    }

    if (m_isKnockBack)
    {

        if (m_animator) m_animator->play("HURT");
        m_sprite.move(m_knockbackVelocity * dt);

        m_knockbackVelocity *= 0.5f; // Giảm dần knockback theo thời gian

        if (std::abs(m_knockbackVelocity.x) < 0.1f && std::abs(m_knockbackVelocity.y) < 0.1f)
        {
            m_knockbackVelocity = sf::Vector2f(0.f, 0.f);
            m_isKnockBack = false;
        }
    }
    else
    {

        sf::Vector2f ghostPos = m_sprite.getPosition();
        sf::Vector2f direction = playerPos - ghostPos;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        float desiredDistance = 150.f;
        float runSpeed = m_speed;

        if (m_isHurt)
        {

            if (m_animator) m_animator->play("RUN");

            runSpeed *= 1.5f;
        }
        else
        {
            if (length > desiredDistance)
            {
                if (m_animator) m_animator->play("WALK");
            }
            else
            {
                if (m_animator) m_animator->play("RUN");
                runSpeed *= 1.5f;
            }
        }

        if (length != 0)
        {
            direction /= length; // Chuẩn hóa vector hướng
            m_velocity = direction * runSpeed;

            if (m_velocity.x > 0.f)
            {
                m_sprite.setScale({ 5.f, 5.f });
            }
            else if (m_velocity.x < 0.f)
            {
                m_sprite.setScale({ -5.f, 5.f });
            }
            m_sprite.move((m_velocity)*dt);
            m_shadowSprite.setPosition(m_sprite.getPosition());
        }
    }

}

void DinoBlue::draw(sf::RenderWindow& window)
{
    window.draw(m_shadowSprite);
    window.draw(m_sprite);

    /*sf::FloatRect bounds = this->getBounds();
    m_hitboxDebug.setPosition(bounds.position);
    m_hitboxDebug.setSize(bounds.size);
    window.draw(m_hitboxDebug);*/
}

sf::FloatRect DinoBlue::getBounds() const
{
    return m_sprite.getGlobalBounds();
}
void DinoBlue::takeDamage(int damage)
{
    m_isHurt = true;
    m_hurtTimer = 3.f;
    m_health -= damage;

    if (m_health < 0.f)
        m_health = 0.f;
}

bool DinoBlue::isDead() const
{
    return m_health <= 0.f;
}

int DinoBlue::getCollisionDamage() const
{
    return 20;
}

sf::Vector2f DinoBlue::getPosition() const
{
    return m_sprite.getPosition();
}

void DinoBlue::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}

void DinoBlue::applySeparation(const std::vector<std::unique_ptr<IEnemy>>& others)
{
    sf::Vector2f repel(0.f, 0.f);
    float desiredDistance = 40.f; // khoảng cách tối thiểu giữa quái

    for (auto& other : others)
    {
        if (other.get() == this) continue;

        sf::Vector2f diff = m_sprite.getPosition() - other->getPosition();
        float len = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (len > 0 && len < desiredDistance)
        {
            diff /= len; // hướng đẩy
            repel += diff * (desiredDistance - len);
        }
    }

    m_sprite.move(repel * 0.2f); // đẩy nhẹ ra
}

int DinoBlue::getXPReward() const
{
    return 20;
}

void DinoBlue::applyKnockback(sf::Vector2f direction, float force)
{
    m_knockbackVelocity += direction * force;
    m_isKnockBack = true;
}