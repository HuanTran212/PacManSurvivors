#include <SFML/Graphics.hpp>

// Đây là "Interface" (lớp trừu tượng) cho TẤT CẢ kẻ thù
// Nó định nghĩa các hàm "ảo" (virtual) mà mọi kẻ thù BẮT BUỘC phải có.

class IEnemy
{
public:
	// Hàm hủy ảo
	virtual ~IEnemy() {}

	// Hàm cập nhật logic (nhận vị trí Player để tính AI)
	virtual void update(float dt, sf::Vector2f playerPosition) = 0;

	// Hàm vẽ
	virtual void draw(sf::RenderWindow& window) = 0;

	// Hàm lấy vùng va chạm
	virtual sf::FloatRect getBounds() const = 0;
};