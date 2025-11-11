#pragma once
#include <SFML/Graphics.hpp>
class IGameState
{
public:
	virtual ~IGameState() = default;
	// Xử lý sự kiện đầu vào
	virtual void processInput() = 0;
	// Cập nhật trạng thái game
	virtual void update(float dt) = 0;
	// Vẽ nội dung lên cửa sổ
	virtual void drawWorld() = 0;
	virtual void drawUI() = 0;
protected:
	IGameState() = default;
};