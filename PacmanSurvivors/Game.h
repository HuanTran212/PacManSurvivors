#pragma once
#include <SFML/Graphics.hpp>
#include "IGameState.h"
#include "UIManager.h"
#include <memory>
#include <string>
#include <map>

class IGameState;
class UIManager;

class Game
{
public:
    // Hàm dựng (Constructor)
    Game();
    // Hàm chạy chính
    void run();
    // Hàm public để các State (như MainMenuState) gọi và đổi trạng thái
	void changeState(std::unique_ptr<IGameState> newState);
	//std::unique_ptr<IGameState>& getStatePtr();
    sf::RenderWindow& getWindow();
    UIManager& getUIManager();

private:
    // Các hàm vòng lặp game 
    void processInput(); // (Sẽ được state xử lý)
    void update(float dt);
    void draw();
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    // Con trỏ thông minh quản lý trạng thái hiện tại
    std::unique_ptr<IGameState> m_currentState;
    // Con trỏ thông minh quản lý UIManager
    std::unique_ptr<UIManager> m_uiManager;
};