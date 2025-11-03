#include "Game.h"

//Hàm tạo cửa sổ Game
Game::Game()
	: m_Window(sf::VideoMode({ 1280, 720 }), "Pacman Survivors")
{
	m_Window.setFramerateLimit(60);
}

//Hàm vòng lặp chính của game
void Game::Run()
{
	while (m_Window.isOpen())
	{
		processInput();
		float dt = m_Clock.restart().asSeconds();
		update(dt);
		render();
	}
}

//Hàm xử lý sự kiện đầu vào
void Game::processInput()
{
	while(auto event = m_Window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_Window.close();
	}
}

//Hàm cập nhật trạng thái game
void Game::update(float dt)
{
	m_Player.update(dt, m_Projectiles);
	m_Ghost.update(dt, m_Player.getPosition());

	for (auto& proj : m_Projectiles)
	{
		proj.update(dt);
	}
	
	m_Projectiles.erase(
		std::remove_if(m_Projectiles.begin(), m_Projectiles.end(),
			[](const Projectile& proj) {
				sf::Vector2f pos = proj.getPosition();
				return (pos.x < 0 || pos.x > 1280 || pos.y < 0 || pos.y > 720);
			}),
		m_Projectiles.end());
}

//Hàm vẽ nội dung lên cửa sổ
void Game::render()
{
	m_Window.clear(sf::Color::Black);

	m_Player.draw(m_Window);
	m_Ghost.draw(m_Window);

	// Vẽ tất cả các đạn
	for (auto& proj : m_Projectiles)
	{
		proj.draw(m_Window);
	}
	   
	m_Window.display();
}