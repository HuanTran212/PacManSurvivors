#include "EnemySpawner.h"
#include "DinoGreen.h"
#include "DinoBlue.h"
#include "DinoYellow.h"
#include "Pinky.h"
#include "Boss.h"
#include "BossGreen.h"
#include "BossDinoBlue.h"
#include "BossDinoYellow.h"
#include <cmath>

std::unique_ptr<IEnemy> EnemySpawner::createEnemy(EnemyType type, sf::Vector2f spawnPos)
{
    switch (type)
    {
    case EnemyType::Pinky:
        return std::make_unique<Pinky>(spawnPos); // Tạo Pinky
    case EnemyType::Boss:
		return std::make_unique<Boss>(spawnPos);
    case EnemyType::DinoBlue:
		return std::make_unique<DinoBlue>(spawnPos);
	case EnemyType::DinoGreen:
		return std::make_unique<DinoGreen>(spawnPos);
	case EnemyType::DinoYellow:
		return std::make_unique<DinoYellow>(spawnPos);
	case EnemyType::BossGreen:
		return std::make_unique<BossGreen>(spawnPos);
	case EnemyType::BossDinoBlue:
		return std::make_unique<BossDinoBlue>(spawnPos);
	case EnemyType::BossDinoYellow:
		return std::make_unique<BossDinoYellow>(spawnPos);

    default:
        // Mặc định an toàn
        return std::make_unique<DinoGreen>(spawnPos);
    }
}
EnemySpawner::EnemySpawner()
	:m_timeLine()
{
    // Giai đoạn 1: 0 - 60 giây
    GameWave wave1;
    wave1.startTime = 0.f;
    wave1.endTime = 60.f;
    wave1.rules.push_back(SpawnRule(EnemyType::DinoGreen, 2.0f, 1));
		wave1.rules.push_back(SpawnRule(EnemyType::Pinky, 3.0f, 1));
	m_timeLine.push_back(wave1);

    // Giai đoạn 2: 60 - 120 giây
    GameWave wave2;
    wave2.startTime = 60.f;
    wave2.endTime = 120.f;
    wave2.rules.push_back(SpawnRule(EnemyType::DinoBlue, 3.0f, 2)); 
    wave2.rules.push_back(SpawnRule(EnemyType::Pinky, 2.0f, 1));
	m_timeLine.push_back(wave2);

    // Giai đoạn 3: 120 giây trở đi
    GameWave wave3;
    wave3.startTime = 120.f;
    wave3.endTime = 180.f;
    wave3.rules.push_back(SpawnRule(EnemyType::DinoYellow, 1.f, 1));
	wave3.rules.push_back(SpawnRule(EnemyType::Pinky, 1.5f, 2)); 
	m_timeLine.push_back(wave3);

    GameWave waveBoss;
    waveBoss.startTime = 180.f;
    waveBoss.endTime = 9999.f;
    waveBoss.events.push_back(SpawnEvent(EnemyType::Boss, 1));
    waveBoss.events.push_back(SpawnEvent(EnemyType::BossGreen, 1));
    waveBoss.events.push_back(SpawnEvent(EnemyType::BossDinoBlue, 1));
    waveBoss.events.push_back(SpawnEvent(EnemyType::BossDinoYellow, 1));
	waveBoss.rules.push_back(SpawnRule(EnemyType::Pinky, 2.0f, 2));
	waveBoss.rules.push_back(SpawnRule(EnemyType::DinoBlue, 1.5f, 1));
	waveBoss.rules.push_back(SpawnRule(EnemyType::DinoGreen, 2.5f, 2));
	waveBoss.rules.push_back(SpawnRule(EnemyType::DinoYellow, 3.5f, 3));
    m_timeLine.push_back(waveBoss);
}


int EnemySpawner::update(float dt, sf::Vector2f playerPosition, float totalGameTime)
{
    GameWave* activeWave = nullptr;
    for (auto& wave : m_timeLine) // Lặp từ đầu
    {
        if (totalGameTime >= wave.startTime && totalGameTime < wave.endTime)
        {
            activeWave = &wave; // Ghi đè liên tục, chỉ giữ cái cuối
        }
    }
    if(activeWave != nullptr)
    {
        for (auto& rule : activeWave->rules)
        {
            rule.timer += dt;
            if (rule.timer >= rule.interval)
            {
                rule.timer -= rule.interval; // Reset timer của rule
                for (int i = 0; i < rule.count; ++i)
                {
                    const float PI = 3.14159265f;
                    float angle = static_cast<float>(rand()) / RAND_MAX * (2.f * PI);
                    float distance = 650.f + static_cast<float>(rand()) / RAND_MAX * 200.f;
                    float x = playerPosition.x + std::cos(angle) * distance;
                    float y = playerPosition.y + std::sin(angle) * distance;

                    m_enemies.push_back(createEnemy(rule.type, sf::Vector2f(x, y)));
                }
            }
        }
        for (auto& event : activeWave->events)
        {
            if (!event.hasSpawned)
            {
                event.hasSpawned = true; // Đánh dấu là đã chạy

                for (int i = 0; i < event.count; ++i)
                {
                    const float PI = 3.14159265f;
                    float angle = static_cast<float>(rand()) / RAND_MAX * (2.f * PI);
                    float distance = 800.f + static_cast<float>(rand()) / RAND_MAX * 200.f;
                    float x = playerPosition.x + std::cos(angle) * distance;
                    float y = playerPosition.y + std::sin(angle) * distance;

                    m_enemies.push_back(createEnemy(event.type, { x, y }));
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
