#include "Game.h"
#include "MainMenuState.h"
#include "AssetManager.h"

Game::Game()
    : m_window(sf::VideoMode({ 1280, 720 }), "PacMan Survivors")
{
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    m_uiManager = std::make_unique<UIManager>();
    m_currentState = std::make_unique<MainMenuState>(*this);
}
// Vòng lặp game chính
void Game::run()
{
    while (m_window.isOpen())
    {
        if(m_currentState)
        {
            m_currentState->processInput(); // State tự xử lý input
		}
        float dt = m_clock.restart().asSeconds();
        if (m_currentState)
        {
            m_currentState->update(dt);
        }

        if (m_currentState)
        {
           m_currentState->draw(); // State tự vẽ
        }
        m_window.display();
    }
}

// Hàm thay đổi trạng thái
void Game::changeState(std::unique_ptr<IGameState> newState)
{
    if (m_currentState)
        std::cout << typeid(*m_currentState).name();
    else
        std::cout << "None";
    std::cout << " -> To: " << typeid(*newState).name() << std::endl;
    m_currentState = std::move(newState);
}

//std::unique_ptr<IGameState>& Game::getStatePtr()
//{
//	return m_currentState;
//}

sf::RenderWindow& Game::getWindow()
{
    return m_window;
}

UIManager& Game::getUIManager()
{
    return *m_uiManager;
}

void Game::processInput() { /* Logic đã được chuyển sang State */ }
void Game::update(float dt) { /* Logic đã được chuyển sang State */ }
void Game::draw() { /* Logic đã được chuyển sang State */ }