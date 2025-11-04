#pragma once
#include "IGameState.h"
#include <SFML/Graphics.hpp>

class MainMenuState : public IGameState
{
private:
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_pressStartText;

public:
    MainMenuState();
    void HandleInput(Game& game, sf::Event& event) override;
    void Update(Game& game, float dt) override;
    void Draw(Game& game, sf::RenderWindow& window) override;
};
#pragma once
