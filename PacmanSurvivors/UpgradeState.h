#pragma once
#include "IGameState.h"
#include "Game.h"
#include "IUpgrade.h"
#include <SFML/Graphics.hpp>
#include <vector>

class UpgradeState : public IGameState
{
public:
	UpgradeState(Game& game, Player& player);
	// Xử lý sự kiện đầu vào
	void processInput() override;
	// Cập nhật trạng thái game
	void update(float dt) override;
	// Vẽ nội dung lên cửa sổ
	void drawUI() override;
	void drawWorld() override;
private:
	Game& m_game;
	sf::Font m_font;
	sf::Text m_titleText;
	sf::RectangleShape m_overlay;
	Player& m_player;
	std::vector<IUpgrade*> m_currentUpgrades;
	sf::Text m_optionText1;
	sf::Text m_optionText2;
	sf::Text m_optionText3;
};