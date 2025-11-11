#include "Game.h"
#include "MainMenuState.h"
#include "AssetManager.h"

Game::Game()
    : m_window(sf::VideoMode({ 1280, 720 }), "PacMan Survivors")
{
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    m_uiManager = std::make_unique<UIManager>();
    pushStates(std::make_unique<MainMenuState>(*this));
    m_worldView.setSize(sf::Vector2f(1280.f, 720.f));
}
// Vòng lặp game chính
void Game::run()
{
    while (m_window.isOpen())
    {
		IGameState* currentState = getCurrentState();
        if(currentState == nullptr)
        {
            m_window.close();
            break;
		}
        currentState->processInput(); // State tự xử lý input
        currentState = getCurrentState();
        if (currentState == nullptr)
        {
            m_window.close();
            return;
        }

        if (currentState == nullptr)
        {
            m_window.close();
            break;
        }
        float dt = m_clock.restart().asSeconds();
        currentState->update(dt);
		m_window.clear(sf::Color::Black);
		m_window.setView(m_worldView);
        for(auto& states : m_currentState)
        {
            currentState->drawWorld(); // State tự vẽ
		}

		m_window.setView(m_window.getDefaultView());
        for(auto& states : m_currentState)
        {
            currentState->drawUI(); // State tự vẽ
        }
        m_window.display();
    }
}


sf::RenderWindow& Game::getWindow()
{
    return m_window;
}

UIManager& Game::getUIManager()
{
    return *m_uiManager;
}

void Game::pushStates(std::unique_ptr<IGameState> newState)
{
    m_currentState.push_back(std::move(newState));
}

void Game::popStates()
{
    if (!m_currentState.empty())
    {
        m_currentState.pop_back();
    }
}

IGameState* Game::getCurrentState()
{
    if (m_currentState.empty()) return nullptr;
    return m_currentState.back().get();
}

sf::View& Game::getWorldView()
{
	return m_worldView;
}

void Game::processInput() { /* Logic đã được chuyển sang State */ }
void Game::update(float dt) { /* Logic đã được chuyển sang State */ }
void Game::draw() { /* Logic đã được chuyển sang State */ }