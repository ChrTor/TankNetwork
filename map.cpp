#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "ResourceManager.h"

Map::Map() {

	const int wallHeight = 62;
	const int heightAmount = 12;
	const int wallWidth = 44;
	const int widthAmount = 25;

	int m_Map[12][25] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	};

	// Outside Walls
		// Letf
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (m_Map[i][j] == 1)
			{

				float x = (float)j;
				float y = (float)i;
				sf::Vector2f newPos((1080.f * (x / 25.f) + 22), (720.f * (y / 12.f)) + 31);
				sf::Vector2f conv((float)newPos.x, (float)newPos.y);
				FillPositionBank(conv);
			}
		}
	}
	// Right

	// Up

	// Bot
}
Map::~Map() {
	for (auto &W : vecWalls) {
		W.~Wall();
	}
	vecWalls.clear();

}
void Map::Init(sf::Texture* text1, sf::Texture* tex2, int type) {


	// For each Wall
	for (auto &W : PositionBank) {
		Wall newWall;
		newWall.Init(W, 1, 0);
		newWall.SetSprite(tex2);
		AddWall(newWall);
	}


}
void Map::Update(float &deltatime) {



}
void Map::Draw(sf::RenderWindow* window) {
	for (auto &W : vecWalls) {
		W.Draw(window);
	}

}

std::vector<Wall>& Map::GetWalls() {
	return vecWalls;
}

void Map::FillPositionBank(sf::Vector2f &position) {
	PositionBank.emplace_back(position);
}

void Map::AddWall(Wall &wall) {
	vecWalls.emplace_back(wall);
}