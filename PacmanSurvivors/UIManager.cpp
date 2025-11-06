#include "UIManager.h"
#include "AssetManager.h"
#include <string>

UIManager::UIManager()
	: m_font(AssetManager::getInstance().getFont("pixel.ttf")),
    m_hpText(m_font),
    m_xpText(m_font),
	m_levelText(m_font)
{
    // Cài đặt cho HP Text
    m_hpText.setFont(m_font);
    m_hpText.setCharacterSize(24);
    m_hpText.setFillColor(sf::Color::Red);
    m_hpText.setPosition({ 20.f, 10.f }); // Vị trí ở góc trên bên trái
    m_hpText.setString("HP: 100"); // Giá trị mặc định

    // Cài đặt cho Level Text
    m_levelText.setFont(m_font);
    m_levelText.setCharacterSize(24);
    m_levelText.setFillColor(sf::Color::White);
    m_levelText.setPosition({ 20.f, 40.f }); // Vị trí ở dưới HP
    m_levelText.setString("LVL: 1"); // Giá trị mặc định

    // Cài đặt cho XP Text
    m_xpText.setFont(m_font);
    m_xpText.setCharacterSize(24);
    m_xpText.setFillColor(sf::Color::Cyan);
    m_xpText.setPosition({ 20.f, 70.f }); // Vị trí ở dưới Level
    m_xpText.setString("XP: 0 / 100"); // Giá trị mặc định
}

void UIManager::update(const Player& player)
{
	int xpToNextLevel = player.getXPToNextLevel();
	int playerHP = player.getHP();
	int playerLevel = player.getLevel();
	int playerXP = player.getXP();
    // Dùng std::to_string để chuyển số (int) thành chữ (string)
    m_hpText.setString("HP: " + std::to_string(playerHP));
    m_levelText.setString("LVL: " + std::to_string(playerLevel));
    m_xpText.setString("XP: " + std::to_string(playerXP) + " / " + std::to_string(xpToNextLevel));
}

void UIManager::draw(sf::RenderWindow& window)
{
    window.draw(m_hpText);
    window.draw(m_levelText);
    window.draw(m_xpText);
}