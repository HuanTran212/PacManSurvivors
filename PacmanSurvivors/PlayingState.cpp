#include "PlayingState.h"
#include "UpgradeState.h"
#include "MainMenuState.h"
#include "Game.h"

PlayingState::PlayingState(Game& game) :
	m_game(game),
	m_window(game.getWindow()),
	m_player(),
	m_enemySpawner(),
	m_totalTime(0.f),
	m_backgroundSprite(AssetManager::getInstance().getTexture("map.png"))
{
	const sf::Texture& bgTex = AssetManager::getInstance().getTexture("map.png");
	const_cast<sf::Texture&>(bgTex).setRepeated(true);
	m_backgroundSprite.setTexture(bgTex);
	m_backgroundSprite.setTextureRect(sf::IntRect({ -10000, -10000 }, { 20000, 20000 }));
}

void PlayingState::processInput()
{
	sf::RenderWindow& window = m_game.getWindow();
	while (auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}
}

void PlayingState::update(float dt)
{
	m_player.update(dt, m_Projectiles, m_enemySpawner.getEnemies());
	int xpGained = m_enemySpawner.update(dt, m_player.getPosition(), m_totalTime);
	if (xpGained > 0)
	{
		bool flap = m_player.addXP(xpGained);
		if (flap)
		{
			m_game.pushStates(std::make_unique<UpgradeState>(m_game, m_player));
		}
	}

	for (auto& proj : m_Projectiles)
	{
		if (!proj.isDestroyed())
		proj.update(dt);
	}
	sf::Vector2f playerPos = m_player.getPosition();
	m_Projectiles.erase(
		std::remove_if(m_Projectiles.begin(), m_Projectiles.end(),
			[playerPos](const Projectile& proj) {
				if (proj.isDestroyed()) {
					return true;
				}
				sf::Vector2f pos = proj.getPosition();
				const float despawnDistance = 1000.f;
				bool isTooFarX = std::abs(pos.x - playerPos.x) > despawnDistance;
				bool isTooFarY = std::abs(pos.y - playerPos.y) > despawnDistance;
				return isTooFarX || isTooFarY;
			}),
		m_Projectiles.end());

	checkCollisions();
	m_game.getUIManager().update(m_player);
	m_game.getWorldView().setCenter(m_player.getPosition());
}

void PlayingState::drawWorld()
{
	m_window.draw(m_backgroundSprite);
	m_player.draw(m_window);
	for(auto& enemy : m_enemySpawner.getEnemies())
	{
		enemy->draw(m_window);
	}
	for (auto& proj : m_Projectiles)
	{
		if (!proj.isDestroyed())
		proj.draw(m_window);
	}
}
void PlayingState::drawUI()
{
	m_game.getUIManager().draw(m_game.getWindow());
}

void PlayingState::checkCollisions()
{
	 for (auto& enemy : m_enemySpawner.getEnemies())
	 {
	     // 1. Va chạm Ma - Player
	    if (m_player.getBounds().findIntersection(enemy->getBounds()))
	    {
	        m_player.takeDamage(enemy->getCollisionDamage());
	        enemy->takeDamage(1000); // Ma chết khi chạm vào Player
	    }
		if (enemy->isDead()) continue;
	     // 2. Va chạm Đạn - Ma
	    for (auto& proj : m_Projectiles)
	    {
	        if (proj.getBounds().findIntersection(enemy->getBounds()))
	        {
	            enemy->takeDamage(proj.getDamage());
	            proj.destroy(); // Đánh dấu đạn bị "hủy"
	        }
	    }
	 }
}
