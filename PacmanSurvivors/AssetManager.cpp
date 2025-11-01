#include "AssetManager.h"
#include <iostream>

AssetManager& AssetManager::GetInstance()
{
	static AssetManager instance;
	return instance;
}

//Hàm Getture: lấy texture từ file
sf::Texture& AssetManager::GetTexture(const std::string& filename)
{
	//Kiểm tra nếu texture đã được tải
	auto it = m_Textures.find(filename);
	if (it != m_Textures.end())
	{
		return it->second; //Trả về texture đã tải
	}
	//Nếu chưa tải, tải texture từ file
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
	{
		std::cerr << "Error loading texture: " << filename << std::endl;
		//Xử lý lỗi tải file (có thể ném ngoại lệ hoặc trả về texture mặc định)
	}
	//Chèn texture vào map và trả về tham chiếu
	m_Textures[filename] = texture;
	return m_Textures[filename];
}

