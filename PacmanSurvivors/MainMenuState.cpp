#pragma once
#include "MainMenuState.h"
#include "PlayingState.h"
#include <iostream>

MainMenuState::MainMenuState(Game& game)
	:m_game(game),
    m_font(AssetManager::getInstance().getFont("pixel.ttf")),
    m_titleText(m_font),
	m_pressStartText(m_font),
	m_exitText(m_font),
    m_backgroundSprite(AssetManager::getInstance().getTexture("main_BG.png"))
{
	SoundManager::getInstance().playMusic("Background_Music.ogg");
	sf::Vector2u windowSize = m_game.getWindow().getSize();

    m_titleText.setFont(m_font);
    m_titleText.setString("PacManSurvivors");
    m_titleText.setCharacterSize(60);
    m_titleText.setFillColor(sf::Color::Yellow);
    m_titleText.setStyle(sf::Text::Bold);
    m_titleText.setPosition({ 180.f, 180.f });

    m_pressStartText.setFont(m_font);
    m_pressStartText.setString("Start");
    m_pressStartText.setCharacterSize(28);
    m_pressStartText.setFillColor(sf::Color::White);
    m_pressStartText.setPosition({ 230.f, 320.f });

    sf::Vector2u textureSize = m_backgroundSprite.getTexture().getSize();

    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;
    m_backgroundSprite.setScale({ scaleX, scaleY });

    m_exitText.setFont(m_font);
    m_exitText.setString("Exit");
    m_exitText.setCharacterSize(28);
    m_exitText.setFillColor(sf::Color::White);
    m_exitText.setPosition({ 230.f, 400.f });
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

        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseEvent->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePos(static_cast<float>(mouseEvent->position.x),
                    static_cast<float>(mouseEvent->position.y));
                if (m_pressStartText.getGlobalBounds().contains(mousePos))
                {
                    m_game.replaceAllStates(std::make_unique<PlayingState>(m_game));
                    return;
                }
                if (m_exitText.getGlobalBounds().contains(mousePos))
                {
                    window.close();
                    return;
                }
            }
        }
    }
}

void MainMenuState::update(float dt)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(m_game.getWindow());
    sf::Vector2f mousePos(static_cast<float>(pixelPos.x), static_cast<float>(pixelPos.y));

    if (m_pressStartText.getGlobalBounds().contains(mousePos))
    {
        m_pressStartText.setFillColor(sf::Color::Yellow);
        m_pressStartText.setScale({ 1.1f, 1.1f });
    }
    else
    {
        m_pressStartText.setFillColor(sf::Color::White);
        m_pressStartText.setScale({ 1.0f, 1.0f });
    }

    if (m_exitText.getGlobalBounds().contains(mousePos))
    {
        m_exitText.setFillColor(sf::Color::Red); 
    }
    else
    {
        m_exitText.setFillColor(sf::Color(200, 200, 200));
    }  
}

void MainMenuState::drawUI()
{
	m_game.getWindow().draw(m_backgroundSprite);
    m_game.getWindow().draw(m_titleText);
    m_game.getWindow().draw(m_pressStartText);
	m_game.getWindow().draw(m_exitText);
}

void MainMenuState::drawWorld()
{
}
