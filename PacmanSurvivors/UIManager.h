#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

class UIManager
{
public:
    // Hàm dựng (Constructor)
    UIManager();
    void update(const Player& player);
    void draw(sf::RenderWindow& window);

private:
    const sf::Font& m_font;
    sf::Text m_hpText;     // Hiển thị HP
    sf::Text m_xpText;     // Hiển thị XP
    sf::Text m_levelText;  // Hiển thị Cấp độ
    // (Bạn có thể thêm các thanh máu/xp bằng sf::RectangleShape ở đây)
};