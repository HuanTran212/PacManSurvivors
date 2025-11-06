#include "PlayingState.h"
#include "MainMenuState.h"
#include "Game.h"

PlayingState::PlayingState(Game& game):
	m_game(game),
	m_window(game.getWindow()),
	m_player(),
	m_enemySpawner(2.0f, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(1230.0f, 670.0f))
{
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
	m_enemySpawner.update(dt, m_player.getPosition());
	for (auto& proj : m_Projectiles)
	{
		if (!proj.isDestroyed())
		proj.update(dt);
	}

	m_Projectiles.erase(
		std::remove_if(m_Projectiles.begin(), m_Projectiles.end(),
			[](const Projectile& proj) {
				sf::Vector2f pos = proj.getPosition();
				return proj.isDestroyed() ||
					(pos.x < 0 || pos.x > 1280 || pos.y < 0 || pos.y > 720);
			}),
		m_Projectiles.end());

	checkCollisions();
	m_game.getUIManager().update(m_player);
}

void PlayingState::draw()
{
	m_game.getWindow().clear(sf::Color::Black);
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
