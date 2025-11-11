#include "EnemySpawner.h"
#include <cmath>
EnemySpawner::EnemySpawner()
    : spawnInterval(3.5f), spawnTimer(0.f), spawnMin({ 0.f, 0.f }), spawnMax({ 1280.f, 720.f })
{
}

EnemySpawner::EnemySpawner(float interval, sf::Vector2f areaMin, sf::Vector2f areaMax)
    : spawnInterval(interval), spawnTimer(0.f), spawnMin(areaMin), spawnMax(areaMax)
{
}

int EnemySpawner::update(float dt, sf::Vector2f playerPosition)
{
    spawnTimer += dt;

    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.f;

        const float PI = 3.14159265f;
        float angle = static_cast<float>(rand()) / RAND_MAX * (2.f * PI);
        float distance = 800.f + static_cast<float>(rand()) / RAND_MAX * 200.f;
        float x = playerPosition.x + std::cos(angle) * distance;
        float y = playerPosition.y + std::sin(angle) * distance;
        m_enemies.push_back(std::make_unique<Ghost>(sf::Vector2f(x, y)));
    }
    
	int totalXP = 0;
    for (auto it = m_enemies.begin(); it != m_enemies.end(); )
    {
        (*it)->update(dt, playerPosition);

        if ((*it)->isDead())
        {
            totalXP += (*it)->getXPReward();
            it = m_enemies.erase(it);
        }
        else
            ++it;
    }
    for (auto& e : m_enemies)
        e->applySeparation(m_enemies);

	return totalXP;
}

void EnemySpawner::draw(sf::RenderWindow& window)
{
    for (auto& e : m_enemies)
        e->draw(window);
}

const std::vector<std::unique_ptr<IEnemy>>& EnemySpawner::getEnemies() const
{
    return m_enemies;
}
