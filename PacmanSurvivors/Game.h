#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ghost.h"


class Game
{
public:
	Game();	//hàm dựng
	void Run();	//hàm chạy game
private:
	//các hàm bên trong Game
	void processInput(); //xử lý sự kiện đầu vào
	void update(float dt);	//cập nhật trạng thái game
	void render(); //vẽ nội dung lên cửa sổ

	sf::RenderWindow m_Window;	//cửa sổ game
	sf::Clock m_Clock;	//đồng hồ để tính delta time

	Player m_Player; //đối tượng người chơi

	Ghost m_Ghost; //đối tượng con ma
};