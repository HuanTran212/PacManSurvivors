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
		ProcessInput();
		float dt = m_Clock.restart().asSeconds();
		Update(dt);
		Render();
	}
}

//Hàm xử lý sự kiện đầu vào
void Game::ProcessInput()
{
	while(auto event = m_Window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_Window.close();
	}
}

//Hàm cập nhật trạng thái game
void Game::Update(float dt)
{
	
}

//Hàm vẽ nội dung lên cửa sổ
void Game::Render()
{
	m_Window.clear(sf::Color::Black);
	
	m_Window.display();
}