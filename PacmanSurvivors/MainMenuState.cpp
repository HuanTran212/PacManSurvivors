#pragma once
#include "MainMenuState.h"
#include "PlayingState.h"
#include <iostream>

MainMenuState::MainMenuState(Game& game)
	:m_game(game),
    m_font(AssetManager::getInstance().getFont("pixel.ttf")),
    m_titleText(m_font),
	m_pressStartText(m_font)
{
	sf::Vector2u windowSize = m_game.getWindow().getSize();

    m_titleText.setFont(m_font);
    m_titleText.setString("PacManSurvivors");
    m_titleText.setCharacterSize(60);
    m_titleText.setFillColor(sf::Color::Yellow);
    m_titleText.setStyle(sf::Text::Bold);
    m_titleText.setPosition({ 180.f, 180.f });

    m_pressStartText.setFont(m_font);
    m_pressStartText.setString("Press ENTER to Start");
    m_pressStartText.setCharacterSize(28);
    m_pressStartText.setFillColor(sf::Color::White);
    m_pressStartText.setPosition({ 230.f, 320.f });
}


void MainMenuState::processInput()
{
    sf::RenderWindow& window = m_game.getWindow();
    while (auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (event->is<sf::Event::KeyPressed>())
        {
            auto keyEvent = event->getIf<sf::Event::KeyPressed>();
            if (keyEvent)
            {
                if (keyEvent->code == sf::Keyboard::Key::Enter)
                {
					m_startGame = true;
                     m_game.changeState(std::make_unique<PlayingState>(m_game));
                    return;
                }
            }
        }
    }
}

void MainMenuState::update(float dt)
{
    // Có thể thêm hiệu ứng nhấp nháy text sau
}

void MainMenuState::draw()
{
	m_game.getWindow().clear(sf::Color::Black);
    m_game.getWindow().draw(m_titleText);
    m_game.getWindow().draw(m_pressStartText);
}
