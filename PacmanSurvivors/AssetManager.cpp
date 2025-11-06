#include "AssetManager.h"
#include <iostream>

// Lấy instance duy nhất của AssetManager
AssetManager& AssetManager::getInstance() {
    static AssetManager instance;
    return instance;
}

// Tải texture nếu chưa có, sau đó trả về reference
const sf::Texture& AssetManager::getTexture(const std::string& filename) {
    auto it = m_textures.find(filename);
    if (it != m_textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "?? [AssetManager] Failed to load texture: " << filename << std::endl;
    } else {
        std::cout << "? [AssetManager] Loaded texture: " << filename << std::endl;
        m_textures[filename] = std::move(texture);
    }
    return m_textures[filename];
}

// Tải font nếu chưa có, sau đó trả về reference
const sf::Font& AssetManager::getFont(const std::string& filename) {
    auto it = m_fonts.find(filename);
    if (it != m_fonts.end()) {
        return it->second;
    }

    sf::Font font;
    if (!font.openFromFile(filename)) {
        std::cerr << "?? [AssetManager] Failed to load font: " << filename << std::endl;
    } else {
        std::cout << "? [AssetManager] Loaded font: " << filename << std::endl;
    }

    m_fonts[filename] = std::move(font);
    return m_fonts[filename];
}

