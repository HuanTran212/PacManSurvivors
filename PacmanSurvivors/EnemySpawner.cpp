#include "EnemySpawner.h"
#include "Ghost.h"
#include <cmath>
EnemySpawner::EnemySpawner()
	:m_timeLine()
{
    // Giai đoạn 1: 0 - 30 giây
    GameWave wave1;
    wave1.startTime = 0.f;
    wave1.endTime = 30.f;
    wave1.rules.push_back(SpawnRule(2.0f, 1)); // 1 Ghost mỗi 2 giây
	m_timeLine.push_back(wave1);

    // Giai đoạn 2: 30 - 60 giây
    GameWave wave2;
    wave2.startTime = 30.f;
    wave2.endTime = 60.f;
    wave2.rules.push_back(SpawnRule(1.0f, 1)); // 1 Ghost mỗi 1 giây
    wave2.rules.push_back(SpawnRule(5.0f, 3)); // 3 Ghost mỗi 5 giây
	m_timeLine.push_back(wave2);

    // Giai đoạn 3: 60 giây trở đi
    GameWave wave3;
    wave3.startTime = 60.f;
    wave3.endTime = 9999.f;
    wave3.rules.push_back(SpawnRule(0.5f, 2)); // 2 Ghost mỗi 0.5 giây
	m_timeLine.push_back(wave3);
}


int EnemySpawner::update(float dt, sf::Vector2f playerPosition, float totalGameTime)
{
    int totalXPDropped = 0;
    for (auto& wave : m_timeLine)
    {
        // Kiểm tra xem wave này có đang hoạt động không
        if (totalGameTime >= wave.startTime && totalGameTime < wave.endTime)
        {
            // Chạy tất cả các quy tắc (rules) trong wave này
            for (auto& rule : wave.rules)
            {
                rule.timer += dt;
                if (rule.timer >= rule.interval)
                {
                    rule.timer -= rule.interval; // Reset timer của rule
                    for (int i = 0; i < rule.count; ++i)
                    {
                        const float PI = 3.14159265f;
                        float angle = static_cast<float>(rand()) / RAND_MAX * (2.f * PI);
                        float distance = 800.f + static_cast<float>(rand()) / RAND_MAX * 200.f;
                        float x = playerPosition.x + std::cos(angle) * distance;
                        float y = playerPosition.y + std::sin(angle) * distance;

                        m_enemies.push_back(std::make_unique<Ghost>(sf::Vector2f(x, y)));
                    }
                }
            }
        }
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
