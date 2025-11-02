#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(float interval, sf::Vector2f areaMin, sf::Vector2f areaMax)
    : spawnInterval(interval), spawnTimer(0.f), spawnMin(areaMin), spawnMax(areaMax)
{
}

void EnemySpawner::update(float dt, sf::Vector2f playerPosition)
{
    spawnTimer += dt;

    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.f;

        float x = spawnMin.x + static_cast<float>(rand()) / RAND_MAX * (spawnMax.x - spawnMin.x);
        float y = spawnMin.y + static_cast<float>(rand()) / RAND_MAX * (spawnMax.y - spawnMin.y);

        enemies.push_back(std::make_unique<Ghost>(sf::Vector2f(x, y)));
    }

    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        (*it)->update(dt, playerPosition);

        if ((*it)->isDead())
            it = enemies.erase(it);
        else
            ++it;
    }
}

void EnemySpawner::draw(sf::RenderWindow& window)
{
    for (auto& e : enemies)
        e->draw(window);
}

const std::vector<std::unique_ptr<IEnemy>>& EnemySpawner::getEnemies() const
{
    return enemies;
}
