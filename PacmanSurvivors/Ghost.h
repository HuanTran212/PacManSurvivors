#include <SFML/Graphics.hpp>

class Ghost
{
private:
    sf::Sprite m_sprite;       // Hình ảnh con ma
    float m_speed;             // Tốc độ di chuyển
    sf::Vector2f velocity;   // Hướng di chuyển hiện tại

public:
    Ghost(sf::Texture& texture, sf::Vector2f startPos, float moveSpeed = 100.f);

    void update(float dt, sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);

    // Có thể thêm getter nếu cần
    sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
    void setPosition(sf::Vector2f pos) { m_sprite.setPosition(pos); }
};