#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cstdlib>
#include "IEnemy.h"
#include "Ghost.h"

class EnemySpawner
{
private:
    std::vector<std::unique_ptr<IEnemy>> m_enemies;
    float spawnTimer;
    float spawnInterval;
    sf::Vector2f spawnMin;
    sf::Vector2f spawnMax;

public:
    EnemySpawner();
    EnemySpawner(float interval, sf::Vector2f areaMin, sf::Vector2f areaMax);

    void update(float dt, sf::Vector2f playerPosition);
    void draw(sf::RenderWindow& window);
    const std::vector<std::unique_ptr<IEnemy>>& getEnemies() const;
};
