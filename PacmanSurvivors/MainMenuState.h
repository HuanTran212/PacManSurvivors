#pragma once
#include "IGameState.h"
#include "AssetManager.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenuState : public IGameState
{
private:
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_pressStartText;
    Game& m_game;
	bool m_startGame = false;
public:
    MainMenuState(Game& game);
    void processInput() override;
    void update(float dt);
	void draw() override;
};