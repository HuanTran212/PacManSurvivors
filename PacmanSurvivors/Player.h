#include <SFML/Graphics.hpp>

class Player {
private:
	sf::Sprite m_sprite; // Hình ảnh đại diện cho người chơi
    float m_speed;
	int m_hp;

public:
	Player(); //Hàm khởi tạo
	void handleInput(float dt); // Xử lý đầu vào người chơi
	void update(float dt); // Cập nhật trạng thái người chơi
	void draw(sf::RenderWindow& window); // Vẽ người chơi lên cửa sổ

	sf::Vector2f getPosition() const; // Lấy vị trí hiện tại của người chơi
	int getHP() const; // Lấy điểm HP hiện tại của người chơi

};
