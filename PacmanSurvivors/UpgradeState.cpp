#include "UpgradeState.h"
#include "AssetManager.h"
#include "PlayingState.h"
#include "UpgradeManager.h"
#include "Player.h"
#include <iostream>

UpgradeState::UpgradeState(Game& game, Player& player) :
	m_game(game),
	m_player(player),
	m_font(AssetManager::getInstance().getFont("pixel.ttf")),
	m_titleText(m_font),
	m_optionText1(m_font),
	m_optionText2(m_font),
	m_optionText3(m_font)
{
	m_titleText.setFont(m_font);
	m_titleText.setString("Upgrade Your Skills");
	m_titleText.setCharacterSize(48);
	m_titleText.setFillColor(sf::Color::Cyan);
	m_titleText.setStyle(sf::Text::Bold);
	m_titleText.setPosition({ 200.f, 100.f });

	sf::Vector2f windowSize = (sf::Vector2f)m_game.getWindow().getSize();

	m_overlay.setSize(windowSize);
	m_overlay.setPosition({0.f, 0.f});
	m_overlay.setFillColor(sf::Color(0, 0, 0, 55));

	m_currentUpgrades = UpgradeManager::getInstance().getRandomUpgrades(3);

	if (m_currentUpgrades.size() >= 1) 
	{
		m_optionText1.setFont(m_font);
		m_optionText1.setString(m_currentUpgrades[0]->getName());
		m_optionText1.setCharacterSize(28);
		m_optionText1.setFillColor(sf::Color::White);
		m_optionText1.setPosition({ 200.f, 250.f });
	}

	if (m_currentUpgrades.size() >= 2) {
		m_optionText2.setFont(m_font);
		m_optionText2.setString(m_currentUpgrades[1]->getName());
		m_optionText2.setCharacterSize(28);
		m_optionText2.setFillColor(sf::Color::White);
		m_optionText2.setPosition({200.f, 350.f});
	}

	if (m_currentUpgrades.size() >= 3) {
		m_optionText3.setFont(m_font);
		m_optionText3.setString(m_currentUpgrades[2]->getName());
		m_optionText3.setCharacterSize(28);
		m_optionText3.setFillColor(sf::Color::White);
		m_optionText3.setPosition({ 200.f, 450.f });
	}
}

void UpgradeState::processInput()
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
				IUpgrade* selectedUpgrade = nullptr;
				if (keyEvent->code == sf::Keyboard::Key::Num1 && m_currentUpgrades.size() >= 1)
				{
					// Chọn nâng cấp 1
					selectedUpgrade = m_currentUpgrades[0];
				}
				else if (keyEvent->code == sf::Keyboard::Key::Num2 && m_currentUpgrades.size() >= 2)
				{
					// Chọn nâng cấp 2
					selectedUpgrade = m_currentUpgrades[1];
				}
				else if (keyEvent->code == sf::Keyboard::Key::Num3 && m_currentUpgrades.size() >= 3)
				{
					// Chọn nâng cấp 3
					selectedUpgrade = m_currentUpgrades[2];
				}

				if (selectedUpgrade != nullptr)
				{
					selectedUpgrade->applyUpgrade(m_player);
					m_game.popStates();
					return;
				}
			}
		}
	}
}
void UpgradeState::update(float dt)
{

}
void UpgradeState::drawUI()
{
	m_game.getWindow().draw(m_overlay);
	m_game.getWindow().draw(m_titleText);

	m_game.getWindow().draw(m_optionText1);
	m_game.getWindow().draw(m_optionText2);
	m_game.getWindow().draw(m_optionText3);
}

void UpgradeState::drawWorld()
{
}
