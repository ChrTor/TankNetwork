#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
class ResourceManager
{
public:
	static ResourceManager* GetInstance() {

		static ResourceManager instance;
		return &instance;
	}
	void CleanUp();
	~ResourceManager();

	sf::Texture* RequestTexture(std::string name, std::string color);

private:
	ResourceManager();
	void LoadTexture(std::string path, std::string type, std::string color);

private:
	std::map<std::string, sf::Texture*> m_Textures;


};
