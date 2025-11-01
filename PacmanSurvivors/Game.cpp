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
	m_Player.update(dt);
	m_Player.getPosition();

	sf::Vector2f playerPos = m_Player.getPosition();

}

//Hàm vẽ nội dung lên cửa sổ
void Game::render()
{
	m_Window.clear(sf::Color::Black);

	m_Player.draw(m_Window);
	m_Ghost.draw(m_Window);
	   
	m_Window.display();
}