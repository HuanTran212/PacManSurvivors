#include "AssetManager.h"
#include <iostream>

AssetManager& AssetManager::GetInstance() {
    static AssetManager instance;
    return instance;
}

const sf::Texture& AssetManager::GetTexture(const std::string& filename) {
    auto it = m_textures.find(filename);
    if (it != m_textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "?? [AssetManager] Failed to load texture: " << filename << std::endl;
    } else {
        std::cout << "? [AssetManager] Loaded texture: " << filename << std::endl;
    }

    m_textures[filename] = std::move(texture);
    return m_textures[filename];
}

const sf::Font& AssetManager::GetFont(const std::string& filename) {
    auto it = m_fonts.find(filename);
    if (it != m_fonts.end()) {
        return it->second;
    }

    sf::Font font;
    if (!font.loadFromFile(filename)) {
        std::cerr << "?? [AssetManager] Failed to load font: " << filename << std::endl;
    } else {
        std::cout << "? [AssetManager] Loaded font: " << filename << std::endl;
    }

    m_fonts[filename] = std::move(font);
    return m_fonts[filename];
}

