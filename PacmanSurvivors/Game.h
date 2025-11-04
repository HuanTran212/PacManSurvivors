#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EnemySpawner.h"
#include "Projectile.h"

class Game
{
public:
	Game();	//hàm dựng
	void Run();	//hàm chạy game
private:
	//các hàm bên trong Game
	void processInput(); //xử lý sự kiện đầu vào
	void update(float dt);	//cập nhật trạng thái game
	void render(); //vẽ nội dung lên cửa sổ

	sf::RenderWindow m_Window;	//cửa sổ game
	sf::Clock m_Clock;	//đồng hồ để tính delta time

	Player m_Player; //đối tượng người chơi
	EnemySpawner m_enemySpawner; //đối tượng tạo kẻ địch
	
	std::vector<Projectile> m_Projectiles;
	std::vector<std::unique_ptr<IEnemy>> m_enemies; //danh sách kẻ địch
};