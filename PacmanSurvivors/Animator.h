#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

class Animator
{
public:
    // Hàm dựng: nhận Sprite và Texture
    Animator(sf::Sprite& sprite);

    // Thêm một chuỗi animation (ví dụ: "WALK_DOWN", "WALK_UP")
    // Frames là 1 vector các hình chữ nhật (IntRect)
    void addAnimation(const std::string& name,
       const std::vector<sf::IntRect>& frames,
       float frameTime);

    // Kích hoạt 1 animation
    void play(const std::string& name);

    // Cập nhật logic animation (đây là phần DSA)
    void update(float dt);

private:
    sf::Sprite& m_sprite; // Tham chiếu đến sprite của Player
    float m_frameTime;
    float m_timer;
    int m_currentFrame;
    std::string m_currentAnimation;

    // Cấu trúc dữ liệu (DSA): Dùng Map để lưu các animation
    // Key: "WALK_DOWN", Value: Vector các khung hình IntRect
    std::map<std::string, std::vector<sf::IntRect>> m_animations;
};