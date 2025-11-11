#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EnemySpawner.h"
#include "Projectile.h"
#include "IGameState.h"
#include "IEnemy.h"
#include <vector>
class Game;

class PlayingState : public IGameState
{
public:
	PlayingState(Game& game);
	void processInput() override;
	void update(float dt) override;
	void drawUI() override;
	void drawWorld() override;
private:
	void checkCollisions();
	Game& m_game;
	sf::RenderWindow& m_window;	//cửa sổ game
	Player m_player; //đối tượng người chơi
	EnemySpawner m_enemySpawner; //đối tượng tạo kẻ địch
	std::vector<Projectile> m_Projectiles; //danh sách đạn bắn ra
	sf::Sprite m_backgroundSprite; //nền game
	float m_totalTime; //thời gian chơi
};