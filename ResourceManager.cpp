#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	//Tanks
		// Red
	LoadTexture("../PNG/Tanks/tankRed.png", "Tank_", "Red");
	LoadTexture("../PNG/Tanks/barrelRed.png", "Barrel_", "Red");
	LoadTexture("../PNG/Bullets/bulletRed.png", "Bullet_", "Red");
	// Blue
	LoadTexture("../PNG/Tanks/tankBlue.png", "Tank_", "Blue");
	LoadTexture("../PNG/Tanks/barrelBlue.png", "Barrel_", "Blue");
	LoadTexture("../PNG/Bullets/bulletBlue.png", "Bullet_", "Blue");
	// Green
	LoadTexture("../PNG/Tanks/tankGreen.png", "Tank_", "Green");
	LoadTexture("../PNG/Tanks/barrelGreen.png", "Barrel_", "Green");
	LoadTexture("../PNG/Bullets/bulletGreen.png", "Bullet_", "Green");
	// Beige
	LoadTexture("../PNG/Tanks/tankBeige.png", "Tank_", "Beige");
	LoadTexture("../PNG/Tanks/barrelBeige.png", "Barrel_", "Beige");
	LoadTexture("../PNG/Bullets/bulletBeige.png", "Bullet_", "Beige");

	// Wall
	LoadTexture("../PNG/Obstacles/barrelGreen_side.png", "Wall", "Green");
	LoadTexture("../PNG/Obstacles/barrelGrey_rust.png", "Wall", "Grey");

}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::LoadTexture(std::string path, std::string type, std::string color)
{
	sf::Texture* t = new sf::Texture();

	std::string Combine(type + color);

	t->loadFromFile(path);
	m_Textures.emplace(Combine, t);
}

void ResourceManager::CleanUp() {
	for (auto item : m_Textures) {
		delete item.second;
		item.second = nullptr;
	}
}

sf::Texture* ResourceManager::RequestTexture(std::string name, std::string type)
{
	std::string combine(name + type);

	if (m_Textures[combine])
	{
		return m_Textures[combine];
	}
	else return nullptr;
}


