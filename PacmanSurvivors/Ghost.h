#include <SFML/Graphics.hpp>
#include "IEnemy.h"

class Ghost
{
private:
    sf::Sprite m_sprite;       // Hình ảnh con ma
    float m_speed;             // Tốc độ di chuyển
    sf::Vector2f velocity;   // Hướng di chuyển hiện tại

public:
	Ghost(); // Hàm khởi tạo

	void update(float dt, sf::Vector2f playerPos); // Cập nhật vị trí con ma dựa trên vị trí người chơi
	void draw(sf::RenderWindow& window); // Vẽ con ma lên cửa sổ

    // Có thể thêm getter nếu cần
	sf::Vector2f getPosition() const; // Lấy vị trí hiện tại của con ma
	void setPosition(sf::Vector2f pos); // Đặt vị trí của con ma

};