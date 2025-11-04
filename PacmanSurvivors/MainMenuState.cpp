#include "MainMenuState.h"
#include "Game.h"
#include <iostream>

MainMenuState::MainMenuState()
{
    if (!m_font.loadFromFile("assets/fonts/arial.ttf"))
        std::cerr << "Error loading font\n";

    m_titleText.setFont(m_font);
    m_titleText.setString("PACMAN SURVIVAL 2D");
    m_titleText.setCharacterSize(48);
    m_titleText.setFillColor(sf::Color::Yellow);
    m_titleText.setStyle(sf::Text::Bold);
    m_titleText.setPosition(180.f, 180.f);

    m_pressStartText.setFont(m_font);
    m_pressStartText.setString("Press ENTER to Start");
    m_pressStartText.setCharacterSize(28);
    m_pressStartText.setFillColor(sf::Color::White);
    m_pressStartText.setPosition(230.f, 320.f);
}

void MainMenuState::HandleInput(Game& game, sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        game.ChangeState("PlayingState"); // Tạm placeholder
}

void MainMenuState::Update(Game& game, float dt)
{
    // Có thể thêm hiệu ứng nhấp nháy text sau
}

void MainMenuState::Draw(Game& game, sf::RenderWindow& window)
{
    window.draw(m_titleText);
    window.draw(m_pressStartText);
}
