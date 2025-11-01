#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class AssetManager {
public:
	// Lấy instance duy nhất của AssetManager
    static AssetManager& getInstance();
	// Tải texture nếu chưa có, sau đó trả về reference
    const sf::Texture& getTexture(const std::string& filename);
	// Tải font nếu chưa có, sau đó trả về reference
    const sf::Font& getFont(const std::string& filename);

private:
	AssetManager() = default; // Constructor riêng tư để ngăn chặn tạo instance bên ngoài
	AssetManager(const AssetManager&) = delete; // Xoá copy constructor
	AssetManager& operator=(const AssetManager&) = delete; // Xoá copy assignment operator

	std::unordered_map<std::string, sf::Texture> m_textures; // Bản đồ lưu trữ textures
	std::unordered_map<std::string, sf::Font> m_fonts; // Bản đồ lưu trữ fonts
};

